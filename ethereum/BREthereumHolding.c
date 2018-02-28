//
//  BREthereumHolding
//  breadwallet-core Ethereum
//
//  Created by Ed Gamble on 2/25/18.
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


#include <string.h>
#include "BREthereumHolding.h"
#include "BREthereum.h"

extern BREthereumToken
tokenCreate (char *address,
              BREthereumGas gasLimit,
              BREthereumGasPrice gasPrice) {
    BREthereumToken token = tokenCreateNone();

    // TODO: Copy address or what (BREthereumToken is a value type....)
    token.address = address;
    token.gasLimit = gasLimit;
    token.gasPrice = gasPrice;

    return token;
}

extern BREthereumToken
tokenCreateNone () {
    BREthereumToken token;
    memset (&token, sizeof (BREthereumToken), 0);
    return token;
}

//
// Holding
//

extern BREthereumHolding
holdingCreate (BREthereumWalletHoldingType type) {
    BREthereumHolding holding;

    holding.type = type;
    switch (type) {
        case WALLET_HOLDING_ETHER:
            holding.holding.ether.amount = etherCreateZero();
            break;
        case WALLET_HOLDING_TOKEN: {
            UInt256 scale = {.u64 = {0, 0, 0, 1}};
            holding.holding.token.scale = scale;
            holding.holding.token.amount = UINT256_ZERO;
            break;
        }
    }
    return holding;
}


extern BREthereumWalletHoldingType
holdingGetType (BREthereumHolding holding) {
    return holding.type;
}

extern BREthereumGas
tokenGetGasLimit (BREthereumToken token) {
    return token.gasLimit;
}


extern BREthereumGasPrice
tokenGetGasPrice (BREthereumToken token) {
    return token.gasPrice;
}