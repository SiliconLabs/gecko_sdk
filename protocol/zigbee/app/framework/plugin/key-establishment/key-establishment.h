/***************************************************************************//**
 * @file
 * @brief APIs and defines for the Key Establishment plugin, which handles
 *        establishment of link keys per the Smart Energy Key Establishment
 *        cluster.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "app/framework/common/zigbee_app_framework_callback.h"
#endif

#ifndef EMBER_SCRIPTED_TEST
#include "zigbee_stack_callback_dispatcher.h"
#endif // EMBER_SCRIPTED_TEST

/**
 * @defgroup key-establishment Key Establishment Client/Server
 * @ingroup component cluster
 * @brief API and Callbacks for the Key Establishment Cluster Client/Server Component
 *
 * Silicon Labs implementation of the Smart Energy Key Establishment cluster.
 * The key establishment cluster is used by the Smart Energy profile to
 * perform Certificate-Based Key Establishment (CBKE), which performs mutual
 * authentication and establishes a symmetric APS link key. Direct CBKE
 * between any two non-TC devices is supported after the two devices have
 * completed partner link key exchange via Trust Center. This component defaults
 * to using CBKE functions with the 163k ECC curve support, but users can also
 * choose the 283k1 ECC curve by selecting the 'CBKE 283k1' component.
 *
 */

/**
 * @addtogroup key-establishment
 * @{
 */

/** @brief Init - bytes: suite (2), key gen time (1), derive secret time (1), cert (48)
 */
#define EM_AF_KE_INITIATE_SIZE        (2 + 1 + 1 + EMBER_CERTIFICATE_SIZE)
#define EM_AF_KE_INITIATE_SIZE_283K1  (2 + 1 + 1 + EMBER_CERTIFICATE_283K1_SIZE)
#define EM_AF_KE_EPHEMERAL_SIZE       EMBER_PUBLIC_KEY_SIZE
#define EM_AF_KE_EPHEMERAL_SIZE_283K1 EMBER_PUBLIC_KEY_283K1_SIZE
#define EM_AF_KE_SMAC_SIZE            EMBER_SMAC_SIZE

/** @brief Terminate - bytes: status (1), wait time (1), suite (2)
 */
#define EM_AF_KE_TERMINATE_SIZE (1 + 1 + 2)

#define APS_ACK_TIMEOUT_SECONDS 1

#define KEY_ESTABLISHMENT_APS_DUPLICATE_DETECTION_TIMEOUT_SEC   5

/** @brief The offset within the 163k1 curve certificate struct where the issuer field
 *  lives.  22-bytes for Public Key Reconstruction data, and 8-bytes for subject.
 */
#define CERT_SUBJECT_OFFSET 22
#define CERT_ISSUER_OFFSET  (CERT_SUBJECT_OFFSET + 8)
#define CERT_ISSUER_SIZE    8

/** @brief The offset within the 283k1 curve certificate struct where the issuer field
 *  lives.  22-bytes for Public Key Reconstruction data, and 8-bytes for subject.
 */
#define CERT_SUBJECT_OFFSET_283K1 (1 + 8 + 1 + 1 + 8 + 5 + 4)
#define CERT_ISSUER_OFFSET_283K1  (1 + 8 + 1 + 1)

/** @brief These values reported to the remote device as to how long the local
 *  device takes to execute these operations.
 */
#define DEFAULT_EPHEMERAL_DATA_GENERATE_TIME_SECONDS   (10 + APS_ACK_TIMEOUT_SECONDS)
#define DEFAULT_GENERATE_SHARED_SECRET_TIME_SECONDS    (15 + APS_ACK_TIMEOUT_SECONDS)

extern const uint8_t sli_zigbee_af_key_establish_message_to_data_size[];

#define sli_zigbee_af_key_establishment_generate_cbke_keys_handler          sli_zigbee_af_generate_cbke_keys_callback
#define sli_zigbee_af_key_establishment_calculate_smacs_handler            sli_zigbee_af_calculate_smacs_callback
#define sli_zigbee_af_key_establishment_generate_cbke_keys_handler283k1     sli_zigbee_af_generate_cbke_keys_callback_283k1
#define sli_zigbee_af_key_establishment_calculate_smacs_handler283k1       sli_zigbee_af_calculate_smacs_callback_283k1

#define TERMINATE_STATUS_STRINGS { \
    "Success",                     \
    "Unknown Issuer",              \
    "Bad Key Confirm",             \
    "Bad Message",                 \
    "No resources",                \
    "Unsupported suite",           \
    "Invalid certificate",         \
    "???",                         \
}
#define UNKNOWN_TERMINATE_STATUS 7

typedef enum {
  NO_KEY_ESTABLISHMENT_EVENT     = 0,
  //Initiator only event
  CHECK_SUPPORTED_CURVES         = 1,
  BEGIN_KEY_ESTABLISHMENT        = 2,
  GENERATE_KEYS                  = 3,
  SEND_EPHEMERAL_DATA_MESSAGE    = 4,
  GENERATE_SHARED_SECRET         = 5,
  SEND_CONFIRM_KEY_MESSAGE       = 6,

  // Initiator only event
  INITIATOR_RECEIVED_CONFIRM_KEY = 7,
} KeyEstablishEvent;

typedef uint8_t KeyEstablishMessage;

extern EmberAfCbkeKeyEstablishmentSuite sli_zigbee_af_available_cbke_suite;
extern EmberAfCbkeKeyEstablishmentSuite sli_zigbee_af_current_cbke_suite;
extern sl_zigbee_event_t emberAfPluginKeyEstablishmentApsDuplicateDetectionEvent;
# define isCbkeKeyEstablishmentSuiteValid() \
  (sli_zigbee_af_current_cbke_suite <= EMBER_AF_CBKE_KEY_ESTABLISHMENT_SUITE_283K1)

# define isCbkeKeyEstablishmentSuite163k1() \
  (sli_zigbee_af_current_cbke_suite         \
   == EMBER_AF_CBKE_KEY_ESTABLISHMENT_SUITE_163K1)

# define isCbkeKeyEstablishmentSuite283k1() \
  (sli_zigbee_af_current_cbke_suite         \
   == EMBER_AF_CBKE_KEY_ESTABLISHMENT_SUITE_283K1)

#define cleanupAndStop(message) cleanupAndStopWithDelay((message), 0)

/**
 * @name API
 * @{
 */

bool checkIssuer(uint8_t *issuer);
void cleanupAndStopWithDelay(EmberAfKeyEstablishmentNotifyMessage message,
                             uint8_t delayInSec);
EmberAfKeyEstablishmentNotifyMessage sendCertificate(void);
void sendNextKeyEstablishMessage(KeyEstablishMessage message,
                                 uint8_t *data);

/** @} */  // end of name API
/** @} */  // end of key-establishment

EmberStatus sli_zigbee_af_generate_cbke_keys_for_curve(void);
void sli_zigbee_af_key_establishment_select_curve(EmberAfCbkeKeyEstablishmentSuite suite);
EmberStatus sli_zigbee_af_calculate_smacs_for_curve(bool amInitiator,
                                                    EmberCertificate283k1Data* partnerCert,
                                                    EmberPublicKey283k1Data* partnerEphemeralPublicKey);
/** @brief Clear data for store link key curve.
 *
 * @param storeLinkKet Ver.: always
 *
 * @return EmberStatus status
 *
 */
EmberStatus emberClearTemporaryDataMaybeStoreLinkKeyForCurve(bool storeLinkKey);

/**
 * @defgroup key_establishment_cb Key Establishment
 * @ingroup af_callback
 * @brief Callbacks for Key Establishment Component
 *
 */

/**
 * @addtogroup key_establishment_cb
 * @{
 */

/** @brief Callback to read key establishments attributes.
 *
 * @param suite Key establishment suite Ver.: always
 */
void emberAfPluginKeyEstablishmentReadAttributesCallback(EmberAfCbkeKeyEstablishmentSuite suite);

/** @brief Callback for key establishment event.
 *
 * @param status Ver.: always
 * @param amInitiator Ver.: always
 * @param partnerShortId Ver.: always
 * @param delayInSeconds Ver.: always
 *
 * @return bool success is true
 */
bool emberAfPluginKeyEstablishmentEventCallback(EmberAfKeyEstablishmentNotifyMessage status,
                                                bool amInitiator,
                                                EmberNodeId partnerShortId,
                                                uint8_t delayInSeconds);

/** @brief Callback for Interpan key establishment.
 *
 * @param status Ver.: always
 * @param amInitiator Ver.: always
 * @param panId Ver.: always
 * @param eui64 Ver.: always
 * @param delayInSeconds Ver.: always
 *
 */
bool emberAfPluginKeyEstablishmentInterPanCallback(EmberAfKeyEstablishmentNotifyMessage status,
                                                   bool amInitiator,
                                                   EmberPanId panId,
                                                   const EmberEUI64 eui64,
                                                   uint8_t delayInSeconds);

/** @} */  // end of key_establishment_cb
void sli_zigbee_af_skip_check_supported_curves(EmberAfCbkeKeyEstablishmentSuite suite);
void sli_zigbee_af_set_available_curves(EmberAfCbkeKeyEstablishmentSuite suite);
// Test code
#if defined(EMBER_TEST) && defined(EMBER_SCRIPTED_TEST)
void scriptTestCheckpoint(char* formatString, ...);
#else
#define scriptTestCheckpoint(string, ...)
#endif /*defined(EMBER_TEST) && defined(EMBER_SCRIPTED_TEST)*/
