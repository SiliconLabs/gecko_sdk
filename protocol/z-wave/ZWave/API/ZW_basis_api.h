/**
 * @file
 * Z-Wave common controller/slave application interface.
 *
 * Z Wave <=> Application general software interface.
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef _ZW_BASIS_API_H_
#define _ZW_BASIS_API_H_

#include <ZW_typedefs.h>
#include <stdint.h>

/* Z-Wave includes */
#include <ZW_transport_api.h>
#include <ZW_classcmd.h>

/**
 * @addtogroup ZWaveAPI Z-Wave API
 * @{
 *
 * @addtogroup BASIS Z-Wave Basis API
 * This section defines functions that are implemented in all Z Wave nodes.
 * @{
*/

/** Return values of @ref ApplicationInit */
typedef enum _APPLICATION_STATUS_
{
  APPLICATION_RUNNING,    ///< Application started normally
  APPLICATION_POWER_DOWN, ///< Application started in special mode:
                          ///< Scheduler started, but Z-Wave protocol task did not.
  APPLICATION_TEST        ///< Test only, not to be used in production
} ZW_APPLICATION_STATUS;

/**
 * @addtogroup NUM_CHANNELS Number of Channels
 * @{
 */
#define NUM_CHANNELS               3  ///< Number of channels of Z-Wave protocol
#define NUM_CHANNELS_LR            4  ///< Number of channels of Z-Wave Long Range protocol
                                      ///< 100kbps, 40kbps, 9.6kbps and US_LR1/US_LR2
#define NUM_CHANNELS_LR_END_DEVICE 2  ///< US_LR1 and US_LR2
///@}

///  Node type structure used in ApplicationNodeInformation
typedef struct _APPL_NODE_TYPE_
{
  uint8_t generic;  ///< Generic Device Type
  uint8_t specific; ///< Specific Device Type
} APPL_NODE_TYPE;

typedef struct _NODE_TYPE_
{
  uint8_t basic;     ///< Basic Device Type, is it a Controller, Controller_Static,
                     ///< Slave or a Slave_Routing Device Type
  uint8_t generic;   ///< Generic Device Type
  uint8_t specific;  ///< Specific Device Type
} NODE_TYPE;


/** Node info stored within the non-volatile memory
* This are the first (protocol part) payload bytes from the Node Infomation frame */
typedef struct _NODEINFO_
{
  uint8_t    capability;  ///< Network capabilities
  uint8_t    security;    ///< Network security
  uint8_t    reserved;
  NODE_TYPE  nodeType;    ///< Basic, Generic and Specific Device types - Basic is generated...
} NODEINFO;


typedef struct
{
  signed char rssi_dBm[NUM_CHANNELS_LR];
} RSSI_LEVELS;


/** Network modes that can be set by @ref ZAF_setNetworkLearnMode */
typedef enum _E_NETWORK_LEARN_MODE_ACTION_
{
  E_NETWORK_LEARN_MODE_DISABLE =  0,       ///< Disable learn process
  E_NETWORK_LEARN_MODE_INCLUSION  = 1,     ///< Enable the learn process to do an inclusion
  E_NETWORK_LEARN_MODE_EXCLUSION  = 2,     ///< Enable the learn process to do an exclusion
  E_NETWORK_LEARN_MODE_EXCLUSION_NWE = 3,  ///< Enable the learn process to do an network wide exclusion
  E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART = 4, ///< Enable the learn process to do an SMARTSTART inclusion
  E_NETWORK_LEARN_MODE_COUNT
} E_NETWORK_LEARN_MODE_ACTION;


/**
* Description of reset reason.
*
* Enum is defined in ZW API as its not HW platform specific.
* @warning For backwards compatibility the enum values must comply with
* the values from ZW_WAKEUP below.
*/
typedef enum EResetReason_t
{
  ERESETREASON_PIN         = 0,   /**< Reset triggered by reset pin */
  ERESETREASON_DEEP_SLEEP_WUT     = 1,   /**< Reset triggered by wake up by timer from deep sleep state  */
//Legacy: ZW_WAKEUP_SENSOR = 2,   /**< Wake up by a Wakeup Beam */
  ERESETREASON_WATCHDOG    = 3,   /**< Reset triggered by watchdog */
  ERESETREASON_DEEP_SLEEP_EXT_INT = 4,   /**< Reset triggered by external interrupt event in deep sleep state */
  ERESETREASON_POWER_ON    = 5,   /**< Reset triggered by power on */
//Legacy: ZW_WAKEUP_USB_SUSPEND= 6  /**< Wake up by USB suspend */
  ERESETREASON_SOFTWARE    = 7,   /**< Reset triggered by software */
//Legacy: ZW_WAKEUP_EMRG_WD_RESET= 8,  /**< Wake up by emergency watchdog reset */
  ERESETREASON_BROWNOUT    = 9,   /**< Reset triggered by brownout circuit */
  ERESETREASON_TAMPER      = 10,  /**< Reset triggered by tamper attempt. */
  ERESETREASON_OTHER       = 0xFF /**< Reset triggered by none of the above */
} EResetReason_t;

//  Legacy ZW_WAKEUP kept for reference.
//  typedef enum _ZW_WAKEUP{
//      /** Wake up after Hardware Reset (RESET_N pin activation) */
//    ZW_WAKEUP_RESET = 0,
//      /* Wake up by the WUT timer */
//    ZW_WAKEUP_WUT = 1,
//      /* Wake up by a Wakeup Beam */
//    ZW_WAKEUP_SENSOR = 2,
//      /* Reset because of a watchdog timeout */
//    ZW_WAKEUP_WATCHDOG = 3,
//      /* Wake up by External input x */
//    ZW_WAKEUP_EXT_INT = 4,
//      /* Reset by Power On Reset circuit */
//    ZW_WAKEUP_POR =5,
//      /* Wake up by USB suspend */
//    ZW_WAKEUP_USB_SUSPEND = 6,
//      /* Wake up by SW reset */
//    ZW_WAKEUP_SW_RESET = 7,
//      /* Wake up by emergency watchdog reset */
//    ZW_WAKEUP_EMRG_WD_RESET = 8,
//      /* Unknown Wakeup reason */
//    ZW_WAKEUP_UNKNOWN = 0xFF
//  } ZW_WAKEUP;

/**
 * @addtogroup APP_NODEINFO Application Node Info
 * Defines for ApplicationNodeInformation field deviceOptionMask
 * @{
 */
///< Not listening Node, corresponds to Reporting Sleeping End Device role type
#define APPLICATION_NODEINFO_NOT_LISTENING            0x00
///< Always On Node, corresponds to Always On (AOS) role type
#define APPLICATION_NODEINFO_LISTENING                0x01
///< Frequently Listening, corresponds to FLiRS role type. Wakes up every 1000ms
#define APPLICATION_FREQ_LISTENING_MODE_1000ms        0x10
///< Frequently Listening, corresponds to FLiRS role type. Wakes up every 250ms
#define APPLICATION_FREQ_LISTENING_MODE_250ms         0x20
///@}

/// @deprecated Use @ref APP_NODEINFO instead
typedef enum _E_SYSTEM_TYPE_
{
  E_SYSTEM_TYPE_NON_LISTENING = APPLICATION_NODEINFO_NOT_LISTENING,     /* 0x00 */
  E_SYSTEM_TYPE_LISTENING = APPLICATION_NODEINFO_LISTENING,     /* 0x01 */
  E_SYSTEM_TYPE_FLIRS = 0x02,                                       /* 0x02 */
} E_SYSTEM_TYPE;

///< @deprecated Use @ref APPLICATION_NODEINFO_LISTENING instead
#define SYSTEM_TYPE_LISTENING_MASK          E_SYSTEM_TYPE_LISTENING
///< @deprecated Use @ref APPLICATION_FREQ_LISTENING_MODE_1000ms or @ref APPLICATION_FREQ_LISTENING_MODE_250ms instead
#define SYSTEM_TYPE_FLIRS_MASK              E_SYSTEM_TYPE_FLIRS

/**
 * ApplicationInit() MUST be defined by the application. This function will be invoked by the
 * Z-Wave stack during boot.
 *
 * ApplicationInit() is invoked before the scheduler starts.
 *
 * ApplicationInit() MUST invoke ZW_ApplicationRegisterTask() as a minimum.
 *
 * \param[in] eResetReason The reason that triggered a reset/boot of the firmware. For instance,
 *                         external pin, wake up timer, power on, etc. Please see
 *                         \ref EResetReason_t.
 *
 * \return The Z-Wave stack acts differently depending on the returned value.
 *         If \ref APPLICATION_RUNNING is returned, everything will boot normally.
 *         If \ref APPLICATION_POWER_DOWN is returned, the Z-Wave stack will NOT start, but the
 *         scheduler will start.
 */
extern  ZW_APPLICATION_STATUS
ApplicationInit(
  EResetReason_t eResetReason
);

/**
 * Initialize the Z-Wave protocol stack.
 */
void sl_zwave_protocol_startup(void);

/**
 * Early startup of Z-Wave platform features
 */
void sl_zwave_platform_startup(void);

/**
 * Gets Z-Wave Protocol Build number
 * @return Z-Wave Protocol Build number
 */
uint16_t ZW_GetProtocolBuildNumber(void);

/**
 * Gets Z-Wave Protocol git hash
 *
 * @return uint8_t* Z-Wave Protocol git hash
 */
uint8_t* ZW_GetProtocolGitHash(void);

/**
 * @} // BASIS
 * @} // ZWaveAPI
 */

#endif /* _ZW_BASIS_API_H_ */

