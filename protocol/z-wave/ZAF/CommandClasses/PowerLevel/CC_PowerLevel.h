/**
 * @file
 * Handler for Command Class Powerlevel.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_POWERLEVEL_H_
#define _CC_POWERLEVEL_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_typedefs.h>
#include <ZW_classcmd.h>
#include <ZAF_types.h>

/**
 * For backwards compatibility.
 */
#define CommandClassPowerLevelVersionGet()    CC_Powerlevel_getVersion()
#define handleCommandClassPowerLevel(a, b, c) CC_Powerlevel_handler(a, b, c)
#define CommandClassPowerLevelIsInProgress()  CC_Powerlevel_isInProgress()


/**
 * Load parameters from NVM
 */
void loadStatusPowerLevel(void);

 /**
 * loads initial power level status from nvram
 */
void loadInitStatusPowerLevel(void);

/**
 * Returns whether a powerlevel test is in progress.
 * @return true if in progress, false otherwise.
 */
bool CC_Powerlevel_isInProgress(void);

#endif
