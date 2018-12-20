 //
 //  BRBlocknodeParams.h
 //
 //  Created by Loshan T on 5/18/18.
 //  Copyright (c) 2018 breadwallet LLC
 //
 //  Permission is hereby granted, free of charge, to any person obtaining a copy
 //  of this software and associated documentation files (the "Software"), to deal
 //  in the Software without restriction, including without limitation the rights
 //  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 //  copies of the Software, and to permit persons to whom the Software is
 //  furnished to do so, subject to the following conditions:
 //
 //  The above copyright notice and this permission notice shall be included in
 //  all copies or substantial portions of the Software.
 //
 //  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 //  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 //  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 //  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 //  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 //  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 //  THE SOFTWARE.
 
  #ifndef BRBlocknodeParams_h
 #define BRBlocknodeParams_h
 
  #include "BRChainParams.h"
 #include "BRPeer.h"
 #include "BRInt.h"
 
  static const char *BRBlocknodeDNSSeeds[] = {
     "dnsseed.litecoinpool.org.", "seed-a.litecoin.loshan.co.uk.", "dnsseed.thrasher.io.",
     "dnsseed.koin-project.com.", "dnsseed.litecointools.com.", NULL
 };
 
  static const char *BRBlocknodeTestNetDNSSeeds[] = {
     "testnet-seed.ltc.xurious.com.", "seed-b.litecoin.loshan.co.uk.", "dnsseed-testnet.thrasher.io.", NULL
 };
 
  static const BRCheckPoint BRBlocknodeTestNetCheckpoints[] = {
     {       0, uint256("4966625a4b2851d9fdee139e56211a0d88575f59ed816ff5e6a63deb4e3e29a0"), 1486949366, 0x1e0ffff0 }
 };
 
  static const BRCheckPoint BRBlocknodeCheckpoints[] = {
     {       0, uint256("00000c392c066ec40b4138a3642ac7c7c3a0b157be45553ea1adcce4196c968d"), 1525032500, 0x1e0ffff0 }
 };
 
  static int BRBlocknodeVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
 {
     return 1; // skipping difficulty check
 }
 
  static int BRBlocknodeTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
 {
     return 1; // skipping difficulty check
 }
 
  static const BRChainParams BRBlocknodeParams = {
     BRBlocknodeDNSSeeds,
     37001,
     0xd3701cb1,
     0,
     BRBlocknodeVerifyDifficulty,
     BRBlocknodeCheckpoints,
     sizeof(BRBlocknodeCheckpoints)/sizeof(*BRBlocknodeCheckpoints)
 };
 
  static const BRChainParams BRBlocknodeTestNetParams = {
     BRBlocknodeTestNetDNSSeeds,
     19335,
     0xf1c8d2fd,
     0,
     BRBlocknodeTestNetVerifyDifficulty,
     BRBlocknodeTestNetCheckpoints,
     sizeof(BRBlocknodeTestNetCheckpoints)/sizeof(*BRBlocknodeTestNetCheckpoints)
 };
 
  #endif // BRChainParams_h