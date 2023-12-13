
/**
 * @file
 * Handler for Command Class Association Group Info.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <CC_AssociationGroupInfo.h>
#include <AppTimer.h>
#include <SwTimer.h>
#include <string.h>
#include <cc_agi_config_api.h>
#include "ZW_TransportSecProtocol.h"
#include "ZAF_CC_Invoker.h"
#include <ZAF_Common_interface.h>
#include "zaf_transport_tx.h"
#include "zaf_config.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

#define REPORT_ONE_GROUP 1
#define REPORT_ALL_GROUPS 2

typedef enum
{
  REPORT_STATUS_INACTIVE,
  REPORT_STATUS_ONE_GROUP,
  REPORT_STATUS_ALL_GROUPS
}
report_status_t;

typedef struct
{
  zaf_cc_list_t * pCmdClassList;
  uint8_t ** ppGroupList;
}
context_t;

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static uint8_t currentGroupId;
static uint8_t associationGroupInfoGetEndpoint = 0;
static report_status_t reportStatus = REPORT_STATUS_INACTIVE;
static RECEIVE_OPTIONS_TYPE_EX rxOptions = { 0 };
static SSwTimer AGIReportSendTimer = { 0 };
static const cc_agi_config_t * p_config = NULL;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

void ZCB_AGIReport(TRANSMISSION_RESULT * pTransmissionResult);
static void ZCB_AGIReportSendTimer(SSwTimer* pTimer);

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static void ZAF_CC_AGI_CorrectGroupIdIfInvalid(uint8_t endpoint, uint8_t * pGroupId)
{
  /*
   * tableSize counts the number of groups excluding lifeline.
   * Hence, for an endpoint with 3 groups (group 2-4), the tableSize will be 3.
   * Since groups are one indexed, group 4 would be treated as an invalid group unless we add one
   * to tableSize before checking.
   *
   * 4 > 3 + 1 = false => group 4 is valid
   * 5 > 3 + 1 = true  => group 5 is invalid
   */
  ASSERT(p_config != NULL);
  if ((1 >= *pGroupId) || (*pGroupId > p_config[endpoint].group_count + 1))
  {
    *pGroupId = 1;
  }
}

ZW_WEAK const cc_agi_config_t * cc_agi_get_config(void)
{
  static const cc_agi_config_t myAgi = {
                                          .groups = NULL,
                                          .group_count = 0
  };

  return &myAgi;
}

ZW_WEAK uint8_t cc_agi_config_get_group_count_by_endpoint(__attribute__((unused)) uint8_t endpoint)
{
  return 0; // Lifeline will always exist, but is not included in this number.
}

/**
 * Invokes the CC function that adds one or more CC / C pairs.
 *
 * This function will be invoked for each linked CC.
 *
 * @param[in] p_cc_entry Given CC entry.
 * @param[in,out] context Context containing the list to which the CC / C pair must be added.
 * @return Always returns false.
 */
static bool cc_callback(CC_handler_map_latest_t const * const p_cc_entry, zaf_cc_context_t context)
{
  // Continue on invalid CC.
  if (0xFF == p_cc_entry->CC) {
    return false;
  }
  // Continue if CC is not required to report via Lifeline.
  if (NULL == p_cc_entry->lifeline_report_get) {
    return false;
  }
  // Loop through each CC supported by the given endpoint (or root device).
  context_t * p_context = context;
  for ( uint8_t i = 0; i < p_context->pCmdClassList->list_size; i++) {

    // Check if there is a match between the two lists.
    if (p_context->pCmdClassList->cc_list[i] == p_cc_entry->CC) {
      // Match found!

      // Call the current CCs lifeline report function that will fill out the group list and increase the group list size.
      uint8_t size_add = p_cc_entry->lifeline_report_get((ccc_pair_t *)*(p_context->ppGroupList));
      *p_context->ppGroupList += 2 * size_add;
    }
  }

  return false;
}

/**
 * @brief Set Application specific Group Command List
 * @param[out] pGroupList pointer to the list
 * @param[out] pGroupListSize Pointer to a variable that can contain the list size.
 * @param[in] groupId group identifier
 * @param[in] endpoint is the endpoint number
 * @return command status (true/false)
 * @private
 */
bool GetApplGroupCommandList(
                             uint8_t * pGroupList,
                             size_t * pGroupListSize,
                             uint8_t groupId,
                             uint8_t endpoint)
{
  if (ZAF_CONFIG_NUMBER_OF_END_POINTS < endpoint)
  {
    return false; /** Error!!*/
  }

  if (1 == groupId)
  {
    uint8_t * pGroupListStart = pGroupList;
    *pGroupListSize = 0;
    zaf_cc_list_t *pCmdClassList  = NULL; // -> struct

    /*
     * Invoke GetCommandClassList() setting "included" to true because this code will not be
     * processed if the node is not included.
     * Pass the highest granted key because this code will only be processed if the frame was
     * received with highest key.
     */
    pCmdClassList = GetCommandClassList(true, GetHighestSecureLevel(ZAF_GetSecurityKeys()), endpoint);
    ASSERT(NULL != pCmdClassList);  // FATAL: Empty CC list. We should not have reached this point. Unlikely scenario!

    context_t context = {
                         .pCmdClassList = pCmdClassList,
                         .ppGroupList = &pGroupList
    };

    ZAF_CC_foreach(cc_callback, (zaf_cc_context_t)&context);

    *pGroupListSize = (size_t)(pGroupList - pGroupListStart);
  }
  else
  {
    *pGroupListSize = sizeof(ccc_pair_t) * p_config[endpoint].groups[groupId - 2].ccc_pair_count;
    memcpy(pGroupList, (uint8_t* )p_config[endpoint].groups[groupId - 2].ccc_pairs,
           *pGroupListSize);

  }
  return true;
}


static bool SendAssoGroupInfoReport(void)
{
  ZW_APPLICATION_TX_BUFFER txBuf = { 0 };
  zaf_tx_options_t tx_options;

  zaf_transport_rx_to_tx_options(&rxOptions, &tx_options);

  txBuf.ZW_AssociationGroupInfoReport1byteFrame.cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
  txBuf.ZW_AssociationGroupInfoReport1byteFrame.cmd      = ASSOCIATION_GROUP_INFO_REPORT;
  // If thelist mode bit is set in the get frame it should be also set in the report frame.
  txBuf.ZW_AssociationGroupInfoReport1byteFrame.properties1 = ((REPORT_STATUS_ALL_GROUPS == reportStatus) ? ASSOCIATION_GROUP_INFO_REPORT_PROPERTIES1_LIST_MODE_BIT_MASK : 0x00) & 0xFF; // we send one report per group
  txBuf.ZW_AssociationGroupInfoReport1byteFrame.properties1 |= 0x01; // One report pr. group.

  VG_ASSOCIATION_GROUP_INFO_REPORT_VG* report = &txBuf.ZW_AssociationGroupInfoReport1byteFrame.variantgroup1;

  ZAF_CC_AGI_CorrectGroupIdIfInvalid(rxOptions.destNode.endpoint, &currentGroupId);

  report->groupingIdentifier = currentGroupId;
  if (1 == currentGroupId) {
    report->profile1 = ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL;
    report->profile2 = ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE;
  } else {
    const agi_profile_t profile = p_config[rxOptions.destNode.endpoint].groups[currentGroupId - 2].profile;
    report->profile1 = profile.profile_MS;
    report->profile2 = profile.profile_LS;
  }

  return zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_ASSOCIATION_GROUP_INFO_REPORT_1BYTE_FRAME),
                          ZCB_AGIReport, &tx_options);
}


/*
Use this timer to delay the sending of the next AGI report after the mutex is released
Since we cannot get a new tx buffer in the call back because the mutex is reserved
*/
static void
ZCB_AGIReportSendTimer(__attribute__((unused)) SSwTimer* pTimer)
{
  SendAssoGroupInfoReport();
}

/*The AGI report call back we will send a report per association group
  if we seed to send AGI fro all the groups*/
void
ZCB_AGIReport(__attribute__((unused)) TRANSMISSION_RESULT * pTransmissionResult)
{
  if (reportStatus == REPORT_STATUS_ALL_GROUPS)
  {
    if (currentGroupId++ < CC_AGI_groupCount_handler(associationGroupInfoGetEndpoint))
    {
      AppTimerRegister(&AGIReportSendTimer, false, ZCB_AGIReportSendTimer);
      TimerStart(&AGIReportSendTimer, 10);
      return;
    }
  }
  reportStatus = REPORT_STATUS_INACTIVE;
}

uint8_t CC_AGI_groupCount_handler(uint8_t const endpoint)
{
  if (ZAF_GetInclusionMode() == EINCLUSIONMODE_ZWAVE_LR)
  {
      return 1; // Lifeline group and no other groups. (Z-Wave LR only supports lifeline group.)
  }

  return 1 + cc_agi_config_get_group_count_by_endpoint(endpoint); // Lifeline group + other groups.
}

/**
 * Returns whether the command class of a given command class / command pair occurs in a given list
 * of command class / command pairs.
 * @param cmdGrp Command class / command pair containing the command class to be found.
 * @param pCmdGrpList Pointer to an array of command class / command pairs.
 * @param listSize Number of items in the array.
 * @return Returns true if the command class is found and false otherwise.
 */
static bool SearchCmdClass(cc_group_t const * const cmdGrp,
                    cc_group_t const * const pCmdGrpList,
                    uint8_t listSize)
{
  for (; listSize > 0; listSize--) {
    if (cmdGrp->cmdClass == pCmdGrpList[listSize - 1].cmdClass) {
      return true;
    }
  }
  return false;
}

uint8_t cc_agi_get_group_id(agi_profile_t const * const profile,
                            ccc_pair_t const * const cmdGrp,
                            uint8_t endpoint)
{
  uint8_t grpId = 0;

  ASSERT(p_config != NULL);
  cc_agi_config_t const * const p_config_ = &p_config[endpoint];

  for (grpId = 0; grpId < p_config_->group_count; grpId++)
  {
    /*Find profile*/
    if ((profile->profile_MS == p_config_->groups[grpId].profile.profile_MS) &&
        (profile->profile_LS == p_config_->groups[grpId].profile.profile_LS))
    {
      for (uint8_t cmdGrpId = 0; cmdGrpId < p_config_->groups[grpId].ccc_pair_count; cmdGrpId++)
      {
        if ( true == SearchCmdClass(cmdGrp, &p_config_->groups[grpId].ccc_pairs[cmdGrpId], 1))
        {
          // Add 2 to get the actual group ID in terms of specifications.
          return grpId + 2;
        }
      }
    }
  }
  return 0xFF;
}

static received_frame_status_t
CC_AGI_handler(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_APPLICATION_TX_BUFFER *pCmd,
    __attribute__((unused)) uint8_t cmdLength,
    ZW_APPLICATION_TX_BUFFER *pFrameOut,
    uint8_t * pFrameOutLength)
{
  size_t  length;
  uint8_t groupID;

  if (true == Check_not_legal_response_job(rxOpt))
  {
    // Get/Report do not support bit addressing.
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  switch (pCmd->ZW_Common.cmd)
    {
      case ASSOCIATION_GROUP_NAME_GET:
        ASSERT(p_config != NULL);

        if (3 != cmdLength)
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        pFrameOut->ZW_AssociationGroupNameReport1byteFrame.cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
        pFrameOut->ZW_AssociationGroupNameReport1byteFrame.cmd      = ASSOCIATION_GROUP_NAME_REPORT;

        groupID = pCmd->ZW_AssociationGroupNameGetFrame.groupingIdentifier;
        pFrameOut->ZW_AssociationGroupNameReport1byteFrame.groupingIdentifier = groupID;

        char * pGroupName;

        /* CC:0059.01.01.12.001 in Application Work Group Specifications */
        if ((1 >= groupID) || (groupID > (p_config[rxOpt->destNode.endpoint].group_count + 1)))
        {
          pGroupName = (char*)"Lifeline";
          pFrameOut->ZW_AssociationGroupNameReport1byteFrame.groupingIdentifier = 1 ;
        }
        else
        {
           pGroupName = (char *)p_config[rxOpt->destNode.endpoint].groups[groupID - 2].name;
        }

        memcpy((char*)&(pFrameOut->ZW_AssociationGroupNameReport1byteFrame.name1), (char*)pGroupName, strlen(pGroupName));

        pFrameOut->ZW_AssociationGroupNameReport1byteFrame.lengthOfName = (uint8_t)strlen(pGroupName);

        /*The way the pFrameOutLength is calculated is to get the size of the struct, remove the last uint8_t byte name1/name2/name3 and
        and add the actual group name in bytes
        */
        *pFrameOutLength = (uint8_t)(sizeof(ZW_ASSOCIATION_GROUP_NAME_REPORT_1BYTE_FRAME)
                       - sizeof(uint8_t)
                       + strlen(pGroupName));

        return RECEIVED_FRAME_STATUS_SUCCESS;
        break;

    case ASSOCIATION_GROUP_INFO_GET:
      ASSERT(p_config != NULL);
      // Ignore command if we are already transmitting.
      if (REPORT_STATUS_INACTIVE != reportStatus)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      if (pCmd->ZW_AssociationGroupInfoGetFrame.properties1 &
          ASSOCIATION_GROUP_INFO_GET_PROPERTIES1_LIST_MODE_BIT_MASK)
      {
        /*if list mode is one then ignore groupid and report information about all the asscoication group
         one group at a time*/
         reportStatus = REPORT_STATUS_ALL_GROUPS;
         currentGroupId = 1;
         associationGroupInfoGetEndpoint = rxOpt->destNode.endpoint;
      }
      else
      {
        /*if list mode is zero and group id is not then report the association group info for the specific group*/
        reportStatus = REPORT_STATUS_ONE_GROUP;
        currentGroupId = pCmd->ZW_AssociationGroupInfoGetFrame.groupingIdentifier;
        associationGroupInfoGetEndpoint = rxOpt->destNode.endpoint;
      }

      if (REPORT_STATUS_INACTIVE != reportStatus)
      {
        memcpy((uint8_t*)&rxOptions, (uint8_t*)rxOpt, sizeof(RECEIVE_OPTIONS_TYPE_EX));
        if (true != SendAssoGroupInfoReport())
        {
          reportStatus = REPORT_STATUS_INACTIVE;
          return RECEIVED_FRAME_STATUS_FAIL;
        }
        else
        {
          return RECEIVED_FRAME_STATUS_SUCCESS;
        }
      }
      return RECEIVED_FRAME_STATUS_FAIL;
      break;

    case ASSOCIATION_GROUP_COMMAND_LIST_GET:
      ASSERT(p_config != NULL);
      groupID = pCmd->ZW_AssociationGroupCommandListGetFrame.groupingIdentifier;

      ZAF_CC_AGI_CorrectGroupIdIfInvalid(rxOpt->destNode.endpoint, &groupID);

      bool status = GetApplGroupCommandList(&pFrameOut->ZW_AssociationGroupCommandListReport1byteFrame.command1, &length, groupID, rxOpt->destNode.endpoint);

      if ((true != status) || (0 == length))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      pFrameOut->ZW_AssociationGroupCommandListReport1byteFrame.cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
      pFrameOut->ZW_AssociationGroupCommandListReport1byteFrame.cmd      = ASSOCIATION_GROUP_COMMAND_LIST_REPORT;
      pFrameOut->ZW_AssociationGroupCommandListReport1byteFrame.groupingIdentifier = groupID;
      pFrameOut->ZW_AssociationGroupCommandListReport1byteFrame.listLength = (uint8_t)length;

      *pFrameOutLength = (uint8_t)(sizeof(ZW_ASSOCIATION_GROUP_COMMAND_LIST_REPORT_1BYTE_FRAME)
                       - sizeof(uint8_t)
                       + length);

      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
      break;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

static void init(void)
{
  p_config = cc_agi_get_config();
}


REGISTER_CC_V4(COMMAND_CLASS_ASSOCIATION_GRP_INFO, ASSOCIATION_GRP_INFO_VERSION_V3, CC_AGI_handler, NULL, NULL, NULL, 0, init, NULL);
