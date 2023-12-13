//#include <stdint.h>
#include <sys/select.h>
//#include <openthread/instance.h>
#include "openthread-core-config.h"
#include "openthread/platform/radio.h"
#include "common/log.hpp"
#include "common/settings.hpp"
#include "instance/instance.hpp"
#include <openthread/dataset.h>
#include "meshcop/dataset.hpp"
#include "utils/parse_cmdline.hpp"
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>

//----------------------------------------------------------------------
// mbedtls stubs

#if (!defined(MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES) && \
     (!defined(MBEDTLS_NO_PLATFORM_ENTROPY) || defined(MBEDTLS_HAVEGE_C) || defined(MBEDTLS_ENTROPY_HARDWARE_ALT)))
#define OT_MBEDTLS_STRONG_DEFAULT_ENTROPY_PRESENT
#endif

#if !OPENTHREAD_RADIO
static mbedtls_ctr_drbg_context sCtrDrbgContext;
static mbedtls_entropy_context  sEntropyContext;
#ifndef OT_MBEDTLS_STRONG_DEFAULT_ENTROPY_PRESENT
static constexpr uint16_t kEntropyMinThreshold = 16;
#endif
#endif

//----------------------------------------------------------------------
// ParseAsHexString implementation (required for use in src/posix/platform/radio.cpp)
// Borrowed from util/third_party/openthread/src/core/utils/parse_cmdline.cpp

using namespace ot;
using namespace Utils;

static Error ParseDigit(char aDigitChar, uint8_t &aValue)
{
    Error error = kErrorNone;

    VerifyOrExit(('0' <= aDigitChar) && (aDigitChar <= '9'), error = kErrorInvalidArgs);
    aValue = static_cast<uint8_t>(aDigitChar - '0');

exit:
    return error;
}

static Error ParseHexDigit(char aHexChar, uint8_t &aValue)
{
    Error error = kErrorNone;

    if (('A' <= aHexChar) && (aHexChar <= 'F'))
    {
        ExitNow(aValue = static_cast<uint8_t>(aHexChar - 'A' + 10));
    }

    if (('a' <= aHexChar) && (aHexChar <= 'f'))
    {
        ExitNow(aValue = static_cast<uint8_t>(aHexChar - 'a' + 10));
    }

    error = ParseDigit(aHexChar, aValue);

exit:
    return error;
}

enum HexStringParseMode
{
    kModeExtactSize,   // Parse hex string expecting an exact size (number of bytes when parsed).
    kModeUpToSize,     // Parse hex string expecting less than or equal a given size.
    kModeAllowPartial, // Allow parsing of partial segments.
};

static Error ParseHexString(const char *&aString, uint16_t &aSize, uint8_t *aBuffer, HexStringParseMode aMode)
{
    Error  error      = kErrorNone;
    size_t parsedSize = 0;
    size_t stringLength;
    size_t expectedSize;
    bool   skipFirstDigit;

    VerifyOrExit(aString != nullptr, error = kErrorInvalidArgs);

    stringLength = strlen(aString);
    expectedSize = (stringLength + 1) / 2;

    switch (aMode)
    {
    case kModeExtactSize:
        VerifyOrExit(expectedSize == aSize, error = kErrorInvalidArgs);
        break;
    case kModeUpToSize:
        VerifyOrExit(expectedSize <= aSize, error = kErrorInvalidArgs);
        break;
    case kModeAllowPartial:
        break;
    }

    // If number of chars in hex string is odd, we skip parsing
    // the first digit.

    skipFirstDigit = ((stringLength & 1) != 0);

    while (parsedSize < expectedSize)
    {
        uint8_t digit;

        if ((aMode == kModeAllowPartial) && (parsedSize == aSize))
        {
            // If partial parse mode is allowed, stop once we read the
            // requested size.
            ExitNow(error = kErrorPending);
        }

        if (skipFirstDigit)
        {
            *aBuffer       = 0;
            skipFirstDigit = false;
        }
        else
        {
            SuccessOrExit(error = ParseHexDigit(*aString, digit));
            aString++;
            *aBuffer = static_cast<uint8_t>(digit << 4);
        }

        SuccessOrExit(error = ParseHexDigit(*aString, digit));
        aString++;
        *aBuffer |= digit;

        aBuffer++;
        parsedSize++;
    }

    aSize = static_cast<uint16_t>(parsedSize);

exit:
    return error;
}

Error CmdLineParser::ParseAsHexString(const char *aString, uint16_t &aSize, uint8_t *aBuffer)
{
    return ParseHexString(aString, aSize, aBuffer, kModeUpToSize);
}

//----------------------------------------------------------------------
// AES stub implementation:
// Borrowed from util/third_party/openthread/src/core/crypto/crypto_platform.cpp

using namespace ot;
using namespace Crypto;

OT_TOOL_WEAK void otPlatCryptoRandomInit(void)
{
    mbedtls_entropy_init(&sEntropyContext);

#ifndef OT_MBEDTLS_STRONG_DEFAULT_ENTROPY_PRESENT
    mbedtls_entropy_add_source(&sEntropyContext, handleMbedtlsEntropyPoll, nullptr, kEntropyMinThreshold,
                               MBEDTLS_ENTROPY_SOURCE_STRONG);
#endif

    mbedtls_ctr_drbg_init(&sCtrDrbgContext);

    int rval = mbedtls_ctr_drbg_seed(&sCtrDrbgContext, mbedtls_entropy_func, &sEntropyContext, nullptr, 0);
    OT_ASSERT(rval == 0);
    OT_UNUSED_VARIABLE(rval);
}

OT_TOOL_WEAK void otPlatCryptoRandomDeinit(void)
{
    mbedtls_entropy_free(&sEntropyContext);
    mbedtls_ctr_drbg_free(&sCtrDrbgContext);
}

OT_TOOL_WEAK otError otPlatCryptoRandomGet(uint8_t *aBuffer, uint16_t aSize)
{
    return ot::Crypto::MbedTls::MapError(
        mbedtls_ctr_drbg_random(&sCtrDrbgContext, static_cast<unsigned char *>(aBuffer), static_cast<size_t>(aSize)));
}

OT_TOOL_WEAK otError otPlatCryptoAesInit(otCryptoContext *aContext)
{
    Error                error = kErrorNone;
    mbedtls_aes_context *context;

    VerifyOrExit(aContext != nullptr, error = kErrorInvalidArgs);
    VerifyOrExit(aContext->mContextSize >= sizeof(mbedtls_aes_context), error = kErrorFailed);

    context = static_cast<mbedtls_aes_context *>(aContext->mContext);
    mbedtls_aes_init(context);

exit:
    return error;
}

OT_TOOL_WEAK otError otPlatCryptoAesSetKey(otCryptoContext *aContext, const otCryptoKey *aKey)
{
    Error                error = kErrorNone;
    mbedtls_aes_context *context;
    const LiteralKey     key(*static_cast<const Key *>(aKey));

    VerifyOrExit(aContext != nullptr, error = kErrorInvalidArgs);
    VerifyOrExit(aContext->mContextSize >= sizeof(mbedtls_aes_context), error = kErrorFailed);

    context = static_cast<mbedtls_aes_context *>(aContext->mContext);
    VerifyOrExit((mbedtls_aes_setkey_enc(context, key.GetBytes(), (key.GetLength() * CHAR_BIT)) == 0),
                 error = kErrorFailed);

exit:
    return error;
}

OT_TOOL_WEAK otError otPlatCryptoAesEncrypt(otCryptoContext *aContext, const uint8_t *aInput, uint8_t *aOutput)
{
    Error                error = kErrorNone;
    mbedtls_aes_context *context;

    VerifyOrExit(aContext != nullptr, error = kErrorInvalidArgs);
    VerifyOrExit(aContext->mContextSize >= sizeof(mbedtls_aes_context), error = kErrorFailed);

    context = static_cast<mbedtls_aes_context *>(aContext->mContext);
    VerifyOrExit((mbedtls_aes_crypt_ecb(context, MBEDTLS_AES_ENCRYPT, aInput, aOutput) == 0), error = kErrorFailed);

exit:
    return error;
}

OT_TOOL_WEAK otError otPlatCryptoAesFree(otCryptoContext *aContext)
{
    Error                error = kErrorNone;
    mbedtls_aes_context *context;

    VerifyOrExit(aContext != nullptr, error = kErrorInvalidArgs);
    VerifyOrExit(aContext->mContextSize >= sizeof(mbedtls_aes_context), error = kErrorFailed);

    context = static_cast<mbedtls_aes_context *>(aContext->mContext);
    mbedtls_aes_free(context);

exit:
    return error;
}

//----------------------------------------------------------------------
// Stubs for MAC frame builder operation
// Used for mac-frame and aes-ccm code, not used for any Spinel operations

using namespace ot;

Error Message::Read(uint16_t aOffset, void *aBuf, uint16_t aLength) const
{
    return OT_ERROR_NOT_IMPLEMENTED;
}

// Stubs for AES-CCM GetFirstChunk/GetNextChunk operations

void Message::GetFirstChunk(uint16_t aOffset, uint16_t &aLength, Chunk &aChunk) const
{
    // This method gets the first message chunk (contiguous data
    // buffer) corresponding to a given offset and length. On exit
    // `aChunk` is updated such that `aChunk.GetBytes()` gives the
    // pointer to the start of chunk and `aChunk.GetLength()` gives
    // its length. The `aLength` is also decreased by the chunk
    // length.

    VerifyOrExit(aOffset < GetLength(), aChunk.SetLength(0));

    if (aOffset + aLength >= GetLength())
    {
        aLength = GetLength() - aOffset;
    }

    aOffset += GetReserved();

    aChunk.SetBuffer(this);

    // Special case for the first buffer

    if (aOffset < kHeadBufferDataSize)
    {
        aChunk.Init(GetFirstData() + aOffset, kHeadBufferDataSize - aOffset);
        ExitNow();
    }

    aOffset -= kHeadBufferDataSize;

    // Find the `Buffer` matching the offset

    while (true)
    {
        aChunk.SetBuffer(aChunk.GetBuffer()->GetNextBuffer());

        OT_ASSERT(aChunk.GetBuffer() != nullptr);

        if (aOffset < kBufferDataSize)
        {
            aChunk.Init(aChunk.GetBuffer()->GetData() + aOffset, kBufferDataSize - aOffset);
            ExitNow();
        }

        aOffset -= kBufferDataSize;
    }

exit:
    if (aChunk.GetLength() > aLength)
    {
        aChunk.SetLength(aLength);
    }

    aLength -= aChunk.GetLength();
}

void Message::GetNextChunk(uint16_t &aLength, Chunk &aChunk) const
{
    // This method gets the next message chunk. On input, the
    // `aChunk` should be the previous chunk. On exit, it is
    // updated to provide info about next chunk, and `aLength`
    // is decreased by the chunk length. If there is no more
    // chunk, `aChunk.GetLength()` would be zero.

    VerifyOrExit(aLength > 0, aChunk.SetLength(0));

    aChunk.SetBuffer(aChunk.GetBuffer()->GetNextBuffer());

    OT_ASSERT(aChunk.GetBuffer() != nullptr);

    aChunk.Init(aChunk.GetBuffer()->GetData(), kBufferDataSize);

    if (aChunk.GetLength() > aLength)
    {
        aChunk.SetLength(aLength);
    }

    aLength -= aChunk.GetLength();

exit:
    return;
}

//----------------------------------------------------------------------
// Logging stubs

using namespace ot;

#if OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
LogLevel Instance::sLogLevel = static_cast<LogLevel>(OPENTHREAD_CONFIG_LOG_LEVEL_INIT);

void Instance::SetLogLevel(LogLevel aLogLevel)
{
    if (aLogLevel != sLogLevel)
    {
        sLogLevel = aLogLevel;
    }
}
#endif

//----------------------------------------------------------------------
// Misc. OpenThread stubs

using namespace ot;

// Defined in src/posix/platform/netif.cpp, not used for RCP.
// Referenced from src/posix/platform/system.cpp
char gNetifName[0];

// Found in src/core/api/instance_api.cpp and referenced from timer.cpp
bool otInstanceIsInitialized(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
    return true;
}

// Referenced from system.cpp
bool otTaskletsArePending(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
    return false;
}

void otInstanceFinalize(otInstance *aInstance)
{
}

namespace ot {
    OT_DEFINE_ALIGNED_VAR(gInstanceRaw, sizeof(Instance), uint64_t);

    // Found in instance_api.cpp and referenced  from system.cpp
    extern "C" otInstance *otInstanceInitSingle(void)
    {
        return (otInstance *)gInstanceRaw;
    }
} // namespace ot
