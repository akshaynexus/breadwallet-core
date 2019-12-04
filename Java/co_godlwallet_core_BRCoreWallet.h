/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class co_godlwallet_core_BRCoreWallet */

#ifndef _Included_co_godlwallet_core_BRCoreWallet
#define _Included_co_godlwallet_core_BRCoreWallet
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    createJniCoreWallet
 * Signature: ([Lco/_godlwallet/core/BRCoreTransaction;Lco/_godlwallet/core/BRCoreMasterPubKey;I)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_createJniCoreWallet
  (JNIEnv *, jclass, jobjectArray, jobject, jint);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    installListener
 * Signature: (Lco/_godlwallet/core/BRCoreWallet/Listener;)V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_installListener
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getReceiveAddress
 * Signature: ()Lco/_godlwallet/core/BRCoreAddress;
 */
JNIEXPORT jobject JNICALL Java_co_godlwallet_core_BRCoreWallet_getReceiveAddress
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getLegacyAddress
 * Signature: ()Lco/_godlwallet/core/BRCoreAddress;
 */
JNIEXPORT jobject JNICALL Java_co_godlwallet_core_BRCoreWallet_getLegacyAddress
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getAllAddresses
 * Signature: ()[Lco/_godlwallet/core/BRCoreAddress;
 */
JNIEXPORT jobjectArray JNICALL Java_co_godlwallet_core_BRCoreWallet_getAllAddresses
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    containsAddress
 * Signature: (Lco/_godlwallet/core/BRCoreAddress;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_containsAddress
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    addressIsUsed
 * Signature: (Lco/_godlwallet/core/BRCoreAddress;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_addressIsUsed
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    jniGetTransactions
 * Signature: ()[Lco/_godlwallet/core/BRCoreTransaction;
 */
JNIEXPORT jobjectArray JNICALL Java_co_godlwallet_core_BRCoreWallet_jniGetTransactions
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTransactionsConfirmedBefore
 * Signature: (J)[Lco/_godlwallet/core/BRCoreTransaction;
 */
JNIEXPORT jobjectArray JNICALL Java_co_godlwallet_core_BRCoreWallet_getTransactionsConfirmedBefore
(JNIEnv *, jobject, jlong);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getBalance
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getBalance
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTotalSent
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getTotalSent
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTotalReceived
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getTotalReceived
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getFeePerKb
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getFeePerKb
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    setFeePerKb
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_setFeePerKb
(JNIEnv *, jobject, jlong);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getMaxFeePerKb
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getMaxFeePerKb
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getDefaultFeePerKb
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getDefaultFeePerKb
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    createTransaction
 * Signature: (JLco/_godlwallet/core/BRCoreAddress;)Lco/_godlwallet/core/BRCoreTransaction;
 */
JNIEXPORT jobject JNICALL Java_co_godlwallet_core_BRCoreWallet_createTransaction
(JNIEnv *, jobject, jlong, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    createTransactionForOutputs
 * Signature: ([Lco/_godlwallet/core/BRCoreTransactionOutput;)Lco/_godlwallet/core/BRCoreTransaction;
 */
JNIEXPORT jobject JNICALL Java_co_godlwallet_core_BRCoreWallet_createTransactionForOutputs
(JNIEnv *, jobject, jobjectArray);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    signTransaction
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;[B)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_signTransaction
  (JNIEnv *, jobject, jobject, jbyteArray);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    containsTransaction
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_containsTransaction
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    jniRegisterTransaction
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_jniRegisterTransaction
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    removeTransaction
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_removeTransaction
(JNIEnv *, jobject, jbyteArray);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    updateTransactions
 * Signature: ([[BJJ)V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_updateTransactions
(JNIEnv *, jobject, jobjectArray, jlong, jlong);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    jniTransactionForHash
 * Signature: ([B)Lco/_godlwallet/core/BRCoreTransaction;
 */
JNIEXPORT jobject JNICALL Java_co_godlwallet_core_BRCoreWallet_jniTransactionForHash
(JNIEnv *, jobject, jbyteArray);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    transactionIsValid
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_transactionIsValid
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    transactionIsPending
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_transactionIsPending
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    transactionIsVerified
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)Z
 */
JNIEXPORT jboolean JNICALL Java_co_godlwallet_core_BRCoreWallet_transactionIsVerified
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTransactionFee
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getTransactionFee
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTransactionAmountSent
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getTransactionAmountSent
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getTransactionAmountReceived
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getTransactionAmountReceived
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getBalanceAfterTransaction
 * Signature: (Lco/_godlwallet/core/BRCoreTransaction;)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getBalanceAfterTransaction
(JNIEnv *, jobject, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getFeeForTransactionSize
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getFeeForTransactionSize
(JNIEnv *, jobject, jlong);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getFeeForTransactionAmount
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getFeeForTransactionAmount
(JNIEnv *, jobject, jlong);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getMinOutputAmount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getMinOutputAmount
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    getMaxOutputAmount
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_co_godlwallet_core_BRCoreWallet_getMaxOutputAmount
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    disposeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_disposeNative
(JNIEnv *, jobject);

/*
 * Class:     co_godlwallet_core_BRCoreWallet
 * Method:    initializeNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_co_godlwallet_core_BRCoreWallet_initializeNative
(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif