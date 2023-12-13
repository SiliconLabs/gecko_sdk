Thread safety of the PSA subsystem
==================================
The PSA API subsystem supports multiple threads to call into the API when `MBEDTLS_PSA_CRYPTO_C` and `MBEDTLS_THREADING_C` are enabled. Concurrent API calls from multiple threads should behave as if they had been executed one at a time, except that the following cases are not supported and have undefined behaviour, that is, the user is responsible for avoiding such situations:

Destroying a key while it's in use. That is the user must make sure the key is not in use before calling psa_destroy_key.
Concurrent calls using the same operation object. (An operation object may not be used by more than one thread at a time. But it can move from one thread to another between calls.)
Overlap of an output buffer with an input or output of a concurrent call.
Modification of an input buffer during a call.
The [PSA Crypto API specification](https://armmbed.github.io/mbed-crypto/html/overview/conventions.html#concurrent-calls) defines minimum expectations for concurrent calls.
