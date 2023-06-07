/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _ZAF_TRANSPORT_CONFIG_H_
#define _ZAF_TRANSPORT_CONFIG_H_

/**
 * \defgroup configuration Configuration
 * Configuration
 *
 * \addtogroup configuration
 * @{
 */
/**
 * \defgroup zaf_transport_configuration ZAF Transport Configuration
 * ZAF Transport Configuration
 *
 * \addtogroup zaf_transport_configuration
 * @{
 */

/**
 * Frame queue size <1..255:1>
 *
 */
#if !defined(ZAF_TRANSPORT_CONFIG_QUEUE_SIZE)
#define ZAF_TRANSPORT_CONFIG_QUEUE_SIZE  2
#endif /* !defined(ZAF_TRANSPORT_CONFIG_QUEUE_SIZE) */

/**@}*/ /* \addtogroup zaf_transport_configuration */

/**@}*/ /* \addtogroup configuration */
#endif /* _ZAF_TRANSPORT_CONFIG_H_ */
