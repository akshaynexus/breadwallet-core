DIR=$(shell pwd)
JAVA_DIR=${JAVA_HOME}
#CINC_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
CINC_DIR=/usr/include

JNI_LIB=libCore.jnilib

JNI_SRCS=co_godlwallet_core_BRCoreAddress.c \
	co_godlwallet_core_BRCoreChainParams.c \
	co_godlwallet_core_BRCoreJniReference.c \
	co_godlwallet_core_BRCoreKey.c \
	co_godlwallet_core_BRCoreMasterPubKey.c \
	co_godlwallet_core_BRCoreMerkleBlock.c \
	co_godlwallet_core_BRCorePaymentProtocol.c \
	co_godlwallet_core_BRCorePeer.c \
	co_godlwallet_core_BRCorePeerManager.c \
	co_godlwallet_core_BRCoreTransaction.c \
	co_godlwallet_core_BRCoreTransactionInput.c \
	co_godlwallet_core_BRCoreTransactionOutput.c \
	co_godlwallet_core_BRCoreWallet.c \
	BRCoreJni.c

JNI_OBJS=$(JNI_SRCS:.c=.o)

# JNI Header Files that we are interest in keeping (that are not empty)
JNI_HDRS=$(JNI_SRCS:.c=.h)

JAVA_SRCS=co/godlwallet/core/BRCoreAddress.java \
	co/godlwallet/core/BRCoreChainParams.java \
	co/godlwallet/core/BRCoreJniReference.java \
	co/godlwallet/core/BRCoreKey.java \
	co/godlwallet/core/BRCoreMasterPubKey.java \
	co/godlwallet/core/BRCoreMerkleBlock.java \
	co/godlwallet/core/BRCorePaymentProtocolEncryptedMessage.java \
	co/godlwallet/core/BRCorePaymentProtocolInvoiceRequest.java \
	co/godlwallet/core/BRCorePaymentProtocolMessage.java \
	co/godlwallet/core/BRCorePaymentProtocolPayment.java \
	co/godlwallet/core/BRCorePaymentProtocolACK.java \
	co/godlwallet/core/BRCorePaymentProtocolRequest.java \
	co/godlwallet/core/BRCorePeer.java \
	co/godlwallet/core/BRCorePeerManager.java \
	co/godlwallet/core/BRCoreTransaction.java \
	co/godlwallet/core/BRCoreTransactionInput.java \
	co/godlwallet/core/BRCoreTransactionOutput.java \
	co/godlwallet/core/BRCoreWallet.java \
	co/godlwallet/core/BRCoreWalletManager.java \
	co/godlwallet/core/test/BRWalletManager.java

JAVA_OBJS=$(JAVA_SRCS:.java=.class)

CORE_SRCS=../BRAddress.c \
	../BRBIP32Sequence.c \
	../BRBIP38Key.c \
	../BRBIP39Mnemonic.c \
	../BRBase58.c \
	../BRBech32.c \
	../BRBloomFilter.c \
	../BRCrypto.c \
	../BRKey.c \
	../BRKeyECIES.c \
	../BRMerkleBlock.c \
	../BRPaymentProtocol.c \
	../BRPeer.c \
	../BRPeerManager.c \
	../BRSet.c \
	../BRTransaction.c \
	../BRWallet.c \
	../bcash/BRBCashAddr.c

CORE_OBJS=$(CORE_SRCS:.c=.o)

CFLAGS=-I$(JAVA_HOME)/include \
	-I$(JAVA_HOME)/include/darwin \
	-I$(CINC_DIR) \
	-I$(CINC_DIR)/malloc \
	-I.. \
	-I../secp256k1 \
	-Wno-nullability-completeness -Wno-format-extra-args -Wno-unknown-warning-option

compile: $(JNI_LIB) java_comp

test: $(JNI_LIB) java_comp
	java -Xss1m -Dwallet.test -classpath build -Djava.library.path=. \
		 co.godlwallet.core.test.BRWalletManager $(ARGS) # -D.

debug: $(JNI_LIB) java_comp
	java -Xss1m -Xdebug -Xrunjdwp:transport=dt_socket,address=8008,server=y,suspend=n \
		 -Dwallet.test -classpath build -Djava.library.path=. \
		 co.godlwallet.core.test.BRWalletManager $(ARGS) # -D.

$(JNI_LIB): $(JNI_OBJS) $(CORE_OBJS)
	cc -dynamiclib -o $(JNI_LIB) $(JNI_OBJS) $(CORE_OBJS)

java_comp:	FORCE
	@mkdir -p build
	javac -d build $(JAVA_SRCS)

jni_hdr: java_comp
	@(cd build/co/godlwallet/core; \
	  for class in BRCore*.class; do \
	      javah -jni -d $(DIR) -classpath $(DIR)/build co.godlwallet.core.$${class%%.class}; \
	  done)
	@rm -f co_godlwallet_core_BRCoreWalletManager.h co_godlwallet_core_BRCore*_*.h .h

#            if [[ "$${class}" != "*\"$\"*" ]]; then
#           fi

clean:
	rm -rf build $(JNI_OBJS) $(CORE_OBJS) $(JAVA_OBJS) $(JNI_LIB)

FORCE:

#	-Wno-nullability-completeness


# Generate Headers:
# 	javac Foo.java
# 	javah -jni -d <location> Foo
# Implement Foo.c
# Generate Foo.so
# 	cc -I<path to jni.h> -I<path to jni_md.h> -I<path to std> -c Foo.c
# 	cc -dynamiclib -o libFoo.jnilib Foo.o Bar.o

# 	<path-to-jni-md>=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include/darwin
# 	<path-to-jni>=/Library/Java/JavaVirtualMachines/jdk1.8.0_151.jdk/Contents/Home/include
# 	<path-to-std>=/…/Xcode.app/Contents/Dev…/Platforms/MacOSX.platform/Dev…/SDKs/MacOSX.sdk/usr/include
# Run Foo
# 	java -Djava.library.path=/Users/ebg Foo
#

# (cd ${APP}/app/build/intermediates/classes/debug/com/hodlallet/core; for class in BRCore*.class; do \
#     javah -jni -d ${APP}/app/src/main/jni/godlwallet-core/Java/ \
#	-classpath ${APP}/app/build/intermediates/classes/debug/ \
#	co.godlwallet.core.${class%%.class}; \
#	done)
# 15RBcXQMTfebbAfUFeBbcDfs1fVvPayWdU
