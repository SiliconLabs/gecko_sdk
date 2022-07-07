/*
 *    Copyright (c) 2017, The OpenThread Authors.
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    3. Neither the name of the copyright holder nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *    POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes definitions for mDNS publisher.
 */

#ifndef OTBR_AGENT_MDNS_HPP_
#define OTBR_AGENT_MDNS_HPP_

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <sys/select.h>

#include "common/code_utils.hpp"
#include "common/types.hpp"

namespace otbr {

namespace Mdns {

/**
 * @addtogroup border-router-mdns
 *
 * @brief
 *   This module includes definition for mDNS publisher.
 *
 * @{
 */

/**
 * This interface defines the functionality of mDNS publisher.
 *
 */
class Publisher : private NonCopyable
{
public:
    /**
     * This structure represents a name/value pair of the TXT record.
     *
     */
    struct TxtEntry
    {
        std::string          mName;  ///< The name of the TXT entry.
        std::vector<uint8_t> mValue; ///< The value of the TXT entry.

        TxtEntry(const char *aName, const char *aValue)
            : TxtEntry(aName, reinterpret_cast<const uint8_t *>(aValue), strlen(aValue))
        {
        }

        TxtEntry(const char *aName, const uint8_t *aValue, size_t aValueLength)
            : TxtEntry(aName, strlen(aName), aValue, aValueLength)
        {
        }

        TxtEntry(const char *aName, size_t aNameLength, const uint8_t *aValue, size_t aValueLength)
            : mName(aName, aNameLength)
            , mValue(aValue, aValue + aValueLength)
        {
        }
    };

    typedef std::vector<TxtEntry>    TxtList;
    typedef std::vector<std::string> SubTypeList;

    /**
     * This structure represents information of a discovered service instance.
     *
     */
    struct DiscoveredInstanceInfo
    {
        bool                    mRemoved    = false; ///< The Service Instance is removed.
        uint32_t                mNetifIndex = 0;     ///< Network interface.
        std::string             mName;               ///< Instance name.
        std::string             mHostName;           ///< Full host name.
        std::vector<Ip6Address> mAddresses;          ///< IPv6 addresses.
        uint16_t                mPort     = 0;       ///< Port.
        uint16_t                mPriority = 0;       ///< Service priority.
        uint16_t                mWeight   = 0;       ///< Service weight.
        std::vector<uint8_t>    mTxtData;            ///< TXT RDATA bytes.
        uint32_t                mTtl = 0;            ///< Service TTL.
    };

    /**
     * This structure represents information of a discovered host.
     *
     */
    struct DiscoveredHostInfo
    {
        std::string             mHostName;  ///< Full host name.
        std::vector<Ip6Address> mAddresses; ///< IP6 addresses.
        uint32_t                mTtl = 0;   ///< Host TTL.
    };

    /**
     * This function is called to notify a discovered service instance.
     *
     */
    using DiscoveredServiceInstanceCallback =
        std::function<void(const std::string &aType, const DiscoveredInstanceInfo &aInstanceInfo)>;

    /**
     * This function is called to notify a discovered host.
     *
     */
    using DiscoveredHostCallback =
        std::function<void(const std::string &aHostName, const DiscoveredHostInfo &aHostInfo)>;

    /**
     * mDNS state values.
     *
     */
    enum class State
    {
        kIdle,  ///< Unable to publish service.
        kReady, ///< Ready to publish service.
    };

    /**
     * This function pointer is called when mDNS publisher state changed.
     *
     * @param[in] aContext  A pointer to application-specific context.
     * @param[in] aState    The new state.
     *
     */
    typedef void (*StateHandler)(void *aContext, State aState);

    /**
     * This method reports the result of a service publication.
     *
     * @param[in] aName     The service instance name.
     * @param[in] aType     The service type.
     * @param[in] aError    An error that indicates whether the service publication succeeds.
     * @param[in] aContext  A user context.
     *
     */
    typedef void (*PublishServiceHandler)(const std::string &aName,
                                          const std::string &aType,
                                          otbrError          aError,
                                          void *             aContext);

    /**
     * This method reports the result of a host publication.
     *
     * @param[in] aName     The host name.
     * @param[in] aError    An OTBR error that indicates whether the host publication succeeds.
     * @param[in] aContext  A user context.
     *
     */
    typedef void (*PublishHostHandler)(const std::string &aName, otbrError aError, void *aContext);

    /**
     * This method sets the handler for service publication.
     *
     * @param[in] aHandler  A handler which will be called when a service publication is finished.
     * @param[in] aContext  A user context which is associated to @p aHandler.
     *
     */
    void SetPublishServiceHandler(PublishServiceHandler aHandler, void *aContext)
    {
        mServiceHandler        = aHandler;
        mServiceHandlerContext = aContext;
    }

    /**
     * This method sets the handler for host publication.
     *
     * @param[in] aHandler  A handler which will be called when a host publication is finished.
     * @param[in] aContext  A user context which is associated to @p aHandler.
     *
     */
    void SetPublishHostHandler(PublishHostHandler aHandler, void *aContext)
    {
        mHostHandler        = aHandler;
        mHostHandlerContext = aContext;
    }

    /**
     * This method starts the mDNS publisher.
     *
     * @retval OTBR_ERROR_NONE  Successfully started mDNS publisher;
     * @retval OTBR_ERROR_MDNS  Failed to start mDNS publisher.
     *
     */
    virtual otbrError Start(void) = 0;

    /**
     * This method stops the mDNS publisher.
     *
     */
    virtual void Stop(void) = 0;

    /**
     * This method checks if publisher has been started.
     *
     * @retval true   Already started.
     * @retval false  Not started.
     *
     */
    virtual bool IsStarted(void) const = 0;

    /**
     * This method publishes or updates a service.
     *
     * @param[in] aHostName     The name of the host which this service resides on. If an empty string is
     *                          provided, this service resides on local host and it is the implementation
     *                          to provide specific host name. Otherwise, the caller MUST publish the host
     *                          with method PublishHost.
     * @param[in] aPort         The port number of this service.
     * @param[in] aName         The name of this service. Note that the published service name may be different from the
     *                          original name due to renaming. You should always pass in the original name here to make
     *                          sure you are referring to the intended service.
     * @param[in] aType         The type of this service.
     * @param[in] aSubTypeList  A list of service subtypes.
     * @param[in] aTxtList      A list of TXT name/value pairs.
     *
     * @retval OTBR_ERROR_NONE   Successfully published or updated the service.
     * @retval OTBR_ERROR_ERRNO  Failed to publish or update the service.
     *
     */
    virtual otbrError PublishService(const std::string &aHostName,
                                     uint16_t           aPort,
                                     const std::string &aName,
                                     const std::string &aType,
                                     const SubTypeList &aSubTypeList,
                                     const TxtList &    aTxtList) = 0;

    /**
     * This method un-publishes a service.
     *
     * @param[in] aName  The name of this service. Note that the published service name may be different from the
     *                   original name due to renaming. You should always pass in the original name here to make
     *                   sure you are referring to the intended service.
     * @param[in] aType  The type of this service.
     *
     * @retval OTBR_ERROR_NONE   Successfully un-published the service.
     * @retval OTBR_ERROR_ERRNO  Failed to un-publish the service.
     *
     */
    virtual otbrError UnpublishService(const std::string &aName, const std::string &aType) = 0;

    /**
     * This method publishes or updates a host.
     *
     * Publishing a host is advertising an AAAA RR for the host name. This method should be called
     * before a service with non-empty host name is published.
     *
     * @param[in] aName     The name of the host.
     * @param[in] aAddress  The address of the host.
     *
     * @retval OTBR_ERROR_NONE          Successfully published or updated the host.
     * @retval OTBR_ERROR_INVALID_ARGS  The arguments are not valid.
     * @retval OTBR_ERROR_ERRNO         Failed to publish or update the host.
     *
     */
    virtual otbrError PublishHost(const std::string &aName, const std::vector<uint8_t> &aAddress) = 0;

    /**
     * This method un-publishes a host.
     *
     * @param[in] aName  A host name.
     *
     * @retval OTBR_ERROR_NONE   Successfully un-published the host.
     * @retval OTBR_ERROR_ERRNO  Failed to un-publish the host.
     *
     */
    virtual otbrError UnpublishHost(const std::string &aName) = 0;

    /**
     * This method subscribes a given service or service instance.
     *
     * If @p aInstanceName is not empty, this method subscribes the service instance. Otherwise, this method subscribes
     * the service. mDNS implementations should use the `DiscoveredServiceInstanceCallback` function to notify
     * discovered service instances.
     *
     * @note Discovery Proxy implementation guarantees no duplicate subscriptions for the same service or service
     * instance.
     *
     * @param[in] aType          The service type.
     * @param[in] aInstanceName  The service instance to subscribe, or empty to subscribe the service.
     *
     */
    virtual void SubscribeService(const std::string &aType, const std::string &aInstanceName) = 0;

    /**
     * This method unsubscribes a given service or service instance.
     *
     * If @p aInstanceName is not empty, this method unsubscribes the service instance. Otherwise, this method
     * unsubscribes the service.
     *
     * @note Discovery Proxy implementation guarantees no redundant unsubscription for a service or service instance.
     *
     * @param[in] aType          The service type.
     * @param[in] aInstanceName  The service instance to unsubscribe, or empty to unsubscribe the service.
     *
     */
    virtual void UnsubscribeService(const std::string &aType, const std::string &aInstanceName) = 0;

    /**
     * This method subscribes a given host.
     *
     * mDNS implementations should use the `DiscoveredHostCallback` function to notify discovered hosts.
     *
     * @note Discovery Proxy implementation guarantees no duplicate subscriptions for the same host.
     *
     * @param[in] aHostName  The host name (without domain).
     *
     */
    virtual void SubscribeHost(const std::string &aHostName) = 0;

    /**
     * This method unsubscribes a given host.
     *
     * @note Discovery Proxy implementation guarantees no redundant unsubscription for a host.
     *
     * @param[in] aHostName  The host name (without domain).
     *
     */
    virtual void UnsubscribeHost(const std::string &aHostName) = 0;

    /**
     * This method sets the callbacks for subscriptions.
     *
     * @param[in] aInstanceCallback  The callback function to receive discovered service instances.
     * @param[in] aHostCallback      The callback function to receive discovered hosts.
     *
     * @returns  The Subscriber ID for the callbacks.
     *
     */
    uint64_t AddSubscriptionCallbacks(DiscoveredServiceInstanceCallback aInstanceCallback,
                                      DiscoveredHostCallback            aHostCallback);

    /**
     * This method cancels callbacks for subscriptions.
     *
     * @param[in] aSubscriberId  The Subscriber ID previously returned by `AddSubscriptionCallbacks`.
     *
     */
    void RemoveSubscriptionCallbacks(uint64_t aSubscriberId);

    virtual ~Publisher(void) = default;

    /**
     * This function creates a mDNS publisher.
     *
     * @param[in] aHandler  The function to be called when this service state changed.
     * @param[in] aContext  A pointer to application-specific context.
     *
     * @returns A pointer to the newly created mDNS publisher.
     *
     */
    static Publisher *Create(StateHandler aHandler, void *aContext);

    /**
     * This function destroys the mDNS publisher.
     *
     * @param[in] aPublisher  A pointer to the publisher.
     *
     */
    static void Destroy(Publisher *aPublisher);

    /**
     * This function decides if two service types (names) are equal.
     *
     * Different implementations may or not append a dot ('.') to the service type (name)
     * and we can not compare if two service type are equal with `strcmp`. This function
     * ignores the trailing dot when comparing two service types.
     *
     * @param[in] aFirstType   The first service type.
     * @param[in] aSecondType  The second service type.
     *
     * @returns A boolean that indicates whether the two service types are equal.
     *
     */
    static bool IsServiceTypeEqual(std::string aFirstType, std::string aSecondType);

    /**
     * This function writes the TXT entry list to a TXT data buffer.
     *
     * The output data is in standard DNS-SD TXT data format.
     * See RFC 6763 for details: https://tools.ietf.org/html/rfc6763#section-6.
     *
     * @param[in]  aTxtList  A TXT entry list.
     * @param[out] aTxtData  A TXT data buffer.
     *
     * @retval OTBR_ERROR_NONE          Successfully write the TXT entry list.
     * @retval OTBR_ERROR_INVALID_ARGS  The @p aTxtList includes invalid TXT entry.
     *
     * @sa DecodeTxtData
     *
     */
    static otbrError EncodeTxtData(const TxtList &aTxtList, std::vector<uint8_t> &aTxtData);

    /**
     * This function decodes a TXT entry list from a TXT data buffer.
     *
     * The input data should be in standard DNS-SD TXT data format.
     * See RFC 6763 for details: https://tools.ietf.org/html/rfc6763#section-6.
     *
     * @param[out]  aTxtList    A TXT entry list.
     * @param[in]   aTxtData    A pointer to TXT data.
     * @param[in]   aTxtLength  The TXT data length.
     *
     * @retval OTBR_ERROR_NONE          Successfully decoded the TXT data.
     * @retval OTBR_ERROR_INVALID_ARGS  The @p aTxtdata has invalid TXT format.
     *
     * @sa EncodeTxtData
     *
     */
    static otbrError DecodeTxtData(TxtList &aTxtList, const uint8_t *aTxtData, uint16_t aTxtLength);

protected:
    enum : uint8_t
    {
        kMaxTextEntrySize = 255,
    };

    void OnServiceResolved(const std::string &aType, const DiscoveredInstanceInfo &aInstanceInfo);
    void OnServiceRemoved(uint32_t aNetifIndex, const std::string &aType, const std::string &aInstanceName);
    void OnHostResolved(const std::string &aHostName, const DiscoveredHostInfo &aHostInfo);

    PublishServiceHandler mServiceHandler        = nullptr;
    void *                mServiceHandlerContext = nullptr;

    PublishHostHandler mHostHandler        = nullptr;
    void *             mHostHandlerContext = nullptr;

    uint64_t mNextSubscriberId = 1;

    std::map<uint64_t, std::pair<DiscoveredServiceInstanceCallback, DiscoveredHostCallback>> mDiscoveredCallbacks;
};

/**
 * @}
 */

} // namespace Mdns

} // namespace otbr

#endif // OTBR_AGENT_MDNS_HPP_
