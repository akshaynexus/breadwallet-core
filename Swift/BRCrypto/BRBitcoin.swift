//
//  BRBitcoin.swift
//  BRCoreX
//
//  Created by Ed Gamble on 11/7/18.
//  Copyright © 2018 breadwallet. All rights reserved.
//

import Foundation // DispatchQueue
import Core

public struct Bitcoin {
    public static let currency = Currency (code: "BTC", symbol:  "₿", name: "Bitcoin", decimals: 8,
                                           baseUnit: (name: "SAT", symbol: "sat"))
    public struct Units {
        public static let SATOSHI = Bitcoin.currency.baseUnit!
        public static let BITCOIN = Bitcoin.currency.defaultUnit!
    }

    public struct Networks {
        public static let mainnet = Network.bitcoin (name: "BTC Mainnet", forkId: 0x00, chainParams: bitcoinParams (1))
        public static let testnet = Network.bitcoin (name: "BTC Testnet", forkId: 0x40, chainParams: bitcoinParams (0))
    }
}

typealias BRCoreWallet = OpaquePointer
typealias BRCorePeerManager = OpaquePointer

public protocol BitcoinListener: WalletManagerListener {}
public protocol BitcoinBackendClient: WalletManagerBackendClient {}
public protocol BitcoinPersistenceClient: WalletManagerPersistenceClient {}

public class BitcoinTransfer: Transfer {
    internal let core: BRTransaction
    
    public unowned let _wallet: BitcoinWallet
    
    public var wallet: Wallet {
        return _wallet
    }

    /// Flag to determine if the wallet's owner sent this transfer
    internal lazy var isSent: Bool = {
        var transaction = core
        let fee = BRWalletFeeForTx (_wallet.core, &transaction)
        return fee != UINT64_MAX && fee != 0
    }()

    public private(set) lazy var source: Address? = {
        // The source address is in a TxInput; if sent it is our address, otherwise anothers
        let inputs = [BRTxInput](UnsafeBufferPointer(start: self.core.inputs, count: self.core.outCount))
        return inputs
            .first { (self.isSent ? 1 : 0) == BRWalletContainsAddress(_wallet.core, UnsafeRawPointer([$0.address]).assumingMemoryBound(to: CChar.self)) }
            .map { Address.bitcoin (BRAddress (s: $0.address))}
    }()

    /// The addresses for all TxInputs
    public var sources: [Address] {
        let inputs = [BRTxInput](UnsafeBufferPointer(start: self.core.inputs, count: self.core.outCount))
        return inputs.map { Address.bitcoin (BRAddress (s: $0.address)) }
    }
    
    public private(set) lazy var target: Address? = {
        // The target address is in a TxOutput; if not sent is it out address, otherwise anothers
        let outputs = [BRTxOutput](UnsafeBufferPointer(start: self.core.outputs, count: self.core.outCount))
        return outputs
            .first { (!self.isSent ? 1 : 0) == BRWalletContainsAddress(_wallet.core, UnsafeRawPointer([$0.address]).assumingMemoryBound(to: CChar.self)) }
            .map { Address.bitcoin (BRAddress (s: $0.address)) }
    }()

    /// The addresses for all TxOutputs
    public var targets: [Address] {
        let outputs = [BRTxOutput](UnsafeBufferPointer(start: self.core.outputs, count: self.core.outCount))
        return outputs.map { Address.bitcoin (BRAddress (s: $0.address)) }
    }

    public var amount: Amount {
        var transaction = core
        let recv = BRWalletAmountReceivedFromTx(_wallet.core, &transaction)
        let send = BRWalletAmountSentByTx (_wallet.core, &transaction)

        var fees = BRWalletFeeForTx (_wallet.core, &transaction)
        if (fees == UINT64_MAX) { fees = 0 }

        return Amount (value: recv + fees - send,  // recv - (fees + send)
                       unit: Bitcoin.Units.SATOSHI)
    }
    
    public var fee: Amount {
        var transaction = core
        let fee = BRWalletFeeForTx (_wallet.core, &transaction)
        return Amount (value: (fee == UINT64_MAX ? 0 : fee),
                       unit: Bitcoin.Units.SATOSHI)
    }
    
    public var feeBasis: TransferFeeBasis {
        get {
            return TransferFeeBasis.bitcoin(feePerKB: BRWalletFeePerKb(_wallet.core))
        }
        set (basis) {
            if case let .bitcoin (feePerKB) = basis {
                BRWalletSetFeePerKb(_wallet.core, feePerKB)
            }
        }
    }
        
    public var hash: TransferHash? {
        return TransferHash.bitcoin (core.txHash)
    }
    
    public var state: TransferState
    
    init (wallet: BitcoinWallet,
          core: BRTransaction) {
        self._wallet = wallet
        self.core = core
        
        // TODO: Should be: included w/ TransferConfirmation
        self.state = TransferState.submitted
    }
    
    init? (wallet: BitcoinWallet,
           target: Address,
           amount: Amount,
           feeBasis: TransferFeeBasis) {
        
        self._wallet = wallet
        
        let addr = target.description
        guard let transaction = BRWalletCreateTransaction (_wallet.core, amount.value.u64.0, addr)?.pointee
            else { return nil}
        
        self.core = transaction
        self.state = TransferState.created
        self.feeBasis = feeBasis
        
    }
}

public class BitcoinTransferFactory: TransferFactory {
    public func createTransfer(wallet: Wallet,
                               target: Address,
                               amount: Amount,
                               feeBasis: TransferFeeBasis) -> Transfer? {
        return BitcoinTransfer (wallet: wallet as! BitcoinWallet,
                                target: target,
                                amount: amount,
                                feeBasis: feeBasis)
    }
}



public class BitcoinWallet: Wallet {
    internal let core: BRCoreWallet
    
    public unowned let _manager: BitcoinWalletManager
    
    public var manager: WalletManager {
        return _manager
    }
    
    public var balance: Amount {
        return Amount (value: BRWalletBalance (core),
                       unit: currency.baseUnit)
        
    }
    
    public var transfers: [Transfer] = []
    
    public func lookup (transfer: TransferHash) -> Transfer? {
        return transfers
            .first  { $0.hash.map { $0 == transfer } ?? false }
    }
    
    public var state: WalletState
    
    public var defaultFeeBasis: TransferFeeBasis {
        get {
            return TransferFeeBasis.bitcoin(feePerKB: BRWalletFeePerKb(core))
        }
        set (basis) {
            if case let .bitcoin (feePerKB) = basis {
                BRWalletSetFeePerKb(core, feePerKB)
            }
        }
    }
    
    public var transferFactory: TransferFactory = BitcoinTransferFactory()
    
    internal let currency: Currency
    
    public var target: Address {
        return Address.bitcoin (BRWalletReceiveAddress(core))
    }
    
    internal init (manager: BitcoinWalletManager,
                   currency: Currency,
                   core:   BRCoreWallet) {
        self._manager = manager
        self.currency = currency
        self.core = core
        
        //        self.currency = Currency.ethereum
        self.state = WalletState.created
    }
}

public class BitcoinWalletManager: WalletManager {

    internal let corePeerManager: BRCorePeerManager
    internal let coreWallet: BRCoreWallet
    
    internal let backendClient: BitcoinBackendClient
    internal let persistenceClient: BitcoinPersistenceClient
    
    public let _listener : BitcoinListener

    public var listener: WalletManagerListener {
        return _listener
    }

    lazy var queue : DispatchQueue = {
        return DispatchQueue (label: "\(network.currency.symbol) WalletManager")
    }()


    public let account: Account
    
    //    public var address: BitcoinAddress {
    //        return BitcoinAddress ("0xb0F225defEc7625C6B5E43126bdDE398bD90eF62")
    //    }
    
    public var network: Network
    
    public private(set) lazy var primaryWallet: Wallet = {
        let wallet = BitcoinWallet (manager: self, currency: network.currency, core: coreWallet)
        self.listener.handleWalletEvent(manager: self, wallet: wallet, event: WalletEvent.created)
        self.listener.handleManagerEvent(manager: self, event: WalletManagerEvent.walletAdded(wallet: wallet))
        return wallet
    }()

    public lazy var wallets: [Wallet] = {
        return [primaryWallet]
    } ()
    
    //    internal func findWallet (identifier: EthereumWalletId) -> EthereumWallet {
    //        return wallets.first { identifier == ($0 as! EthereumWallet).identifier } as! EthereumWallet
    //    }
    
    public var mode: WalletManagerMode
    
    public var path: String
    
    public var state: WalletManagerState
    
    #if false
    public var walletFactory: WalletFactory = EthereumWalletFactory()
    #endif
    
    internal static var managers: [BitcoinWalletManager] = [] // Weak<>
    
    internal static func lookup (wallet: OpaquePointer) -> BitcoinWalletManager? {
        return managers.first { wallet == $0.coreWallet }
    }
    
    internal static func lookup (ptr: UnsafeMutableRawPointer?) -> BitcoinWalletManager? {
        return ptr.map { Unmanaged<BitcoinWalletManager>.fromOpaque($0).takeUnretainedValue() }
    }
    
    public init (listener: BitcoinListener,
                 account: Account,
                 network: Network,
                 mode: WalletManagerMode,
                 timestamp: UInt64,
                 persistenceClient: BitcoinPersistenceClient = DefaultBitcoinPersistenceClient(),
                 backendClient: BitcoinBackendClient = DefaultBitcoinBackendClient()) {
        guard let params = network.bitcoinChainParams else { precondition(false) }
        
        self.backendClient = backendClient
        self.persistenceClient = persistenceClient
        
        self._listener = listener
        self.network = network
        self.account = account
        self.path = ""
        self.mode = mode
        self.state = WalletManagerState.created
        
        self.coreWallet      = BRWalletNew (nil, 0, account.masterPublicKey, 0x00)
        self.corePeerManager = BRPeerManagerNew (params, coreWallet, UInt32(timestamp),
                                                 nil, 0,
                                                 nil, 0)
        
        BRWalletSetCallbacks (
            coreWallet,
            Unmanaged.passUnretained(self).toOpaque(),
            
            // balanceChanged
            { (this, balance) in
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    bwm.queue.async {
                        if let wallet = bwm.primaryWallet as? BitcoinWallet {
                            let amount = Amount (value: balance, unit: Bitcoin.Units.SATOSHI)
                            bwm.listener.handleWalletEvent (manager: bwm,
                                                            wallet: wallet,
                                                            event: WalletEvent.balanceUpdated(amount: amount))
                        }
                    }
                }},
            
            // txAdded
            { (this, tx) in
                if let bwm  = BitcoinWalletManager.lookup (ptr: this), let tx = tx {
                    bwm.queue.async {
                        if let wallet = bwm.primaryWallet as? BitcoinWallet {
                            let transfer = BitcoinTransfer (wallet: wallet,
                                                            core: tx.pointee)
                            wallet.transfers.append(transfer)

                            bwm.listener.handleTransferEvent (manager: bwm,
                                                              wallet: bwm.primaryWallet,
                                                              transfer: transfer,
                                                              event: TransferEvent.created)

                            bwm.listener.handleWalletEvent (manager: bwm,
                                                            wallet: bwm.primaryWallet,
                                                            event: WalletEvent.transferAdded(transfer: transfer))
                        }
                    }
                }},

            // txUpdated
            { (this, txHashes, txCount, blockHeight, timestamp) in
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    // Copy `txHashes`; they'll disappear.
                    let coreHashes = [UInt256](UnsafeBufferPointer(start: txHashes, count: txCount)).map { $0 }
                    bwm.queue.async {
                        if let wallet = bwm.primaryWallet as? BitcoinWallet {
                            for coreHash in coreHashes {
                                if let transfer = wallet.lookup(transfer: TransferHash.bitcoin(coreHash)) as? BitcoinTransfer {
                                    let confirmation =  TransferConfirmation (
                                        blockNumber: UInt64(blockHeight),
                                        transactionIndex: 0,
                                        timestamp: UInt64(timestamp),
                                        fee: transfer.fee)

                                    let oldState = transfer.state
                                    let newState = TransferState.included (confirmation: confirmation)

                                    transfer.state = newState

                                    bwm.listener.handleTransferEvent(manager: bwm,
                                                                     wallet: wallet,
                                                                     transfer: transfer,
                                                                     event: TransferEvent.changed(old: oldState, new: newState))

                                    bwm.listener.handleWalletEvent(manager: bwm,
                                                                   wallet: wallet,
                                                                   event: WalletEvent.transferChanged(transfer: transfer))
                                }
                            }
                        }
                    }
                }},
            
            // txDeleted
            { (this, txHash, notify, rescan) in
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    bwm.queue.async {
                        if let wallet = bwm.primaryWallet as? BitcoinWallet {
                            let hash = TransferHash.bitcoin (txHash)
                            if let transfer = wallet.lookup(transfer: hash),
                                let index = wallet.transfers.firstIndex (where: { $0.hash == hash }) {
                                wallet.transfers.remove(at: index)

                                bwm.listener.handleTransferEvent(manager: bwm,
                                                                 wallet: wallet,
                                                                 transfer: transfer,
                                                                 event: TransferEvent.deleted)

                                bwm.listener.handleWalletEvent(manager: bwm,
                                                               wallet: wallet,
                                                               event: WalletEvent.transferDeleted(transfer: transfer))
                            }
                        }
                    }
                }}
        )
        
        BRPeerManagerSetCallbacks (
            corePeerManager,
            Unmanaged.passUnretained(self).toOpaque(),
            
            { (this) in // syncStarted
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    bwm.listener.handleManagerEvent (manager: bwm,
                                                     event: WalletManagerEvent.syncStarted)
                }},
            
            { (this, error) in // syncStopped
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    let reason = 0 == error ? nil : asUTF8String(strerror(error))
                    bwm.listener.handleManagerEvent (manager: bwm,
                                                     event: WalletManagerEvent.syncEnded(error: reason))
                }},
            
            { (this) in // txStatusUpdate
                if let _  = BitcoinWalletManager.lookup (ptr: this) {
                }},
            
            { (this, replace, blocks, blocksCount) in // saveBlocks
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    // let blockRefs = [BRBlockRef?](UnsafeBufferPointer(start: blocks, count: blocksCount))
                    // replace != 0
                    let blocksDictionary: [String:String] = [:]
                    bwm.persistenceClient.saveBlocks (manager: bwm, data: blocksDictionary)
                }},
            
            
            { (this, replace, peers, peersCount) in // savePeers
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    // let peerList = [BRPeer](UnsafeBufferPointer(start: peers, count: peersCount))
                    // replace != 0
                    let peersDictionary: [String:String] = [:]
                    bwm.persistenceClient.savePeers (manager: bwm, data: peersDictionary)
                }},
            
            { (this) -> Int32 in  // networkIsReachable
                if let bwm  = BitcoinWalletManager.lookup (ptr: this) {
                    return bwm.backendClient.networkIsReachable() ? 1 : 0
                }
                else {
                    return 0
                }},

            { (this) in // threadCleanup
                if let _  = BitcoinWalletManager.lookup (ptr: this) {
                }})


        BitcoinWalletManager.managers.append(self)
        self.listener.handleManagerEvent(manager: self, event: WalletManagerEvent.created)
        let _ = self.primaryWallet
    }
    
    public func connect() {
        BRPeerManagerConnect (self.corePeerManager)
    }
    
    public func disconnect() {
        BRPeerManagerDisconnect (self.corePeerManager)
    }
    
    //hack to keep the swift compiler happy
    let a = BRBCashCheckpoints
    let b = BRBCashDNSSeeds
    let c = BRBCashVerifyDifficulty
    let d = BRBCashTestNetCheckpoints
    let e = BRBCashTestNetDNSSeeds
    let f = BRBCashTestNetVerifyDifficulty
    let g = BRMainNetDNSSeeds
    let h = BRMainNetCheckpoints
    let i = BRMainNetVerifyDifficulty
    let j = BRTestNetDNSSeeds
    let k = BRTestNetCheckpoints
    let l = BRTestNetVerifyDifficulty
}
