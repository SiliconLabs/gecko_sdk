/***************************************************************************//**
 * @file sl_zigbee_stack_specific_tlv.c
 * @brief source for global tlv generation
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include PLATFORM_HEADER

#include "stack/include/ember-types.h"
#include "stack/core/ember-multi-network.h"

#include "include/sl_zigbee_tlv_core.h"
#include "include/sl_zigbee_stack_specific_tlv.h"

#include "buffer_manager/legacy-packet-buffer.h"

#include "mac-child.h"
#include "stack/core/ember-stack.h" // for emberGetEui64
#include "stack/include/sl_zigbee_zdo_dlk_negotiation.h" // for sl_zigbee_zdo_dlk_get_supported_negotiation_parameters
#include "stack/routing/zigbee/sl_zigbee_beacon_tlvs.h" // for sl_get_router_info_bitmask
#include "stack/routing/zigbee/management.h" // for pan id conflict counts
#include "stack/routing/zigbee/association.h" // forjoin methods
#include "stack/zigbee/zigbee-device.h" // forjoin methods
// Defines
#define IS_END_ENV(elem) ((elem).isEnd)
///
/// Global TLV Config Getter
///

typedef struct {
  uint8_t tag;
  sl_zigbee_global_tlv_u tlvU;
} GlobalTlvResult_t;

static bool validate_length_tlv_env(uint8_t tag,
                                    uint16_t len,
                                    sl_zigbee_tlv_tag_min_length_t *env);

static bool validate_length_global_tlv(uint8_t tag,
                                       uint16_t len);

// ZigBee Global TLVs
sl_zigbee_tlv_tag_min_length_t global_tlv_env[] =
{ { .tag_id = SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_MFG_SPECIFIC_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_MIN_LEN, },

  // TODO EMZIGBEE-5834 finish defining the global TLV env

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_MIN_LEN, },

  { .tag_id = SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_TAG_ID,
    .min_length = SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_MIN_LEN, },

  TLV_ENV_TERMINATOR, };

// define an array of encapsulation tag ids
uint8_t sl_zigbee_encap_tlv_global_tag_ids[] =
{ SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_TAG_ID,
  SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_TAG_ID, };

// TODO remove dependency on the TLV flag byte

WEAK(sl_status_t sli_zigbee_get_device_capability_extension_data(bool* attach_tlv, uint16_t* bitmask))
{
  (void)attach_tlv;
  (void)bitmask;

  return SL_STATUS_FAIL;
}

// TODO EMZIGBEE-6553 fill in remaining tlv config getters
static GlobalTlvResult_t get_global_tlv_config(uint8_t tag_id)
{
  GlobalTlvResult_t tlvResult;
  bool haveValue = false;
  // NOTE this is used in case encapsulation tlvs fail for some reason
  sl_status_t status;
  switch (tag_id) {
    case SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_TAG_ID:
      tlvResult.tlvU.supportedKeymaskTlv = sl_zigbee_global_tlv_supp_key_negotiation();
      haveValue = true;
      break;
    case SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_TAG_ID:
      tlvResult.tlvU.panConflictTlv = sl_zigbee_global_tlv_pan_id_conflict();
      haveValue = true;
      break;
    // TODO case SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_TAG_ID:
    // TODO case SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_TAG_ID:
    // TODO case SL_ZIGBEE_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_TAG_ID:
    case SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_TAG_ID:
      tlvResult.tlvU.routerInfoTlv = sl_zigbee_global_tlv_router_information();
      haveValue = true;
      break;
    case SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_TAG_ID:
      tlvResult.tlvU.fragmentationTlv = sl_zigbee_global_tlv_fragmentation_param();
      haveValue = true;
      break;
    case SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_TAG_ID:
      status = sl_zigbee_global_tlv_joiner_encapsulation(&tlvResult.tlvU.joinerEncapTlv);
      haveValue = (status == SL_STATUS_OK);
      break;
    case SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_TAG_ID:
      status = sl_zigbee_global_tlv_beacon_appendix_encapsulation(&tlvResult.tlvU.beaconAppendixEncapTlv);
      haveValue = (status == SL_STATUS_OK);
      break;
    case SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_TAG_ID:
    {
      bool attach_tlv = false;
      uint16_t bitmask = 0x0000;
      if ((sli_zigbee_get_device_capability_extension_data(&attach_tlv, &bitmask) == SL_STATUS_OK)
          && attach_tlv) {
        tlvResult.tlvU.deviceCapExtTlv = sl_zigbee_global_tlv_device_capability_extension_param(bitmask);
        haveValue = true;
      }
    }
    break;
    // TODO case SL_ZIGBEE_GLOBAL_TLV_POTENTIAL_PARENTS_TAG_ID:
    // TODO case SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_TAG_ID:
    default:
      haveValue = false;
      break;
  }
  tlvResult.tag = haveValue ? EMBER_SUCCESS : EMBER_ERR_FATAL;
  return tlvResult;
}

sl_status_t sl_zigbee_global_tlv_add_configurations(Buffer *buffer,
                                                    uint16_t index,
                                                    uint8_t tag_c,
                                                    uint8_t *tag_v)
{
  if (tag_c == 0
      || tag_v == NULL
      || buffer == NULL
      || *buffer == NULL_BUFFER) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // loop over tag_v
  // switch on tag id
  // generate the global tlv value for the local device
  // if we don't recognize the TLV or have no value we skip the tag id
  uint8_t i = 0;
  bool abort = false;
  sl_status_t status = SL_STATUS_OK;
  while ((tag_c - i) > 0 && !abort) {
    uint8_t tag_id = tag_v[i];
    GlobalTlvResult_t tlvResult = get_global_tlv_config(tag_id);
    if (tlvResult.tag == SL_STATUS_OK) {
      status = sl_zigbee_tlv_concat_to_buffer(buffer, index, &tlvResult.tlvU.tlv);
      if (status != SL_STATUS_OK) {
        abort = true;
      }
    }
    i++;
  }
  return status;
}

// NOTE this might be a testing only interface that we might want to remove
Buffer sl_zigbee_global_tlv_get_configurations(uint8_t tag_c, uint8_t *tag_v)
{
  Buffer resultBuffer = sli_legacy_buffer_manager_allocate_buffer(0);
  EmberStatus status = sl_zigbee_global_tlv_add_configurations(&resultBuffer,
                                                               0,
                                                               tag_c,
                                                               tag_v);
  if (status != EMBER_SUCCESS) {
    resultBuffer = NULL_BUFFER;
  }
  return resultBuffer;
}

///
/// Supported Key Negotiation Methods TLV Helpers
///
// returns our supported key negotiation methods tlv
sl_zigbee_global_tlv_supp_key_negotiation_t sl_zigbee_global_tlv_supp_key_negotiation(void)
{
  sl_zigbee_global_tlv_supp_key_negotiation_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_SUPP_KEY_NEGOTIATION_MAX_LEN);
  uint8_t *data = sl_zigbee_tlv_get_value_ptr(&tlv);
  sl_zigbee_zdo_dlk_get_supported_negotiation_parameters(&data[SL_ZIGBEE_DLK_NEGOTIATION_TLV_PROTOCOL_INDEX],
                                                         &data[SL_ZIGBEE_DLK_NEGOTIATION_TLV_SECRET_INDEX]);
  MEMCOPY(&data[SL_ZIGBEE_DLK_NEGOTIATION_TLV_LONG_ID_INDEX], emberGetEui64(), EUI64_SIZE);
  return tlv;
}

///
/// Detected PAN ID Conflict Report
///
sl_zigbee_global_tlv_pan_id_conflict_t sl_zigbee_global_tlv_pan_id_conflict(void)
{
  sl_zigbee_global_tlv_pan_id_conflict_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_PAN_ID_CONFLICT_MAX_LEN);
  uint8_t *valPtr = sl_zigbee_tlv_get_value_ptr(&tlv);
  emberStoreLowHighInt16u(valPtr,
                          sli_zigbee_get_pan_id_conflict_count());
  return tlv;
}

///
/// Next Pan ID TLV Helpers
///
// pass in a node id to us

sl_zigbee_global_tlv_next_pan_id_t sl_zigbee_global_tlv_next_pan_from_pan(EmberPanId pan_id)
{
  sl_zigbee_global_tlv_next_pan_id_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_NEXT_PAN_ID_MAX_LEN);
  emberStoreLowHighInt16u(sl_zigbee_tlv_get_value_ptr(&tlv), pan_id);
  return tlv;
}

// return the stored pan id
EmberPanId sl_zigbee_global_tlv_next_pan_get_pan(sl_zigbee_global_tlv_next_pan_id_t *tlv)
{
  return emberFetchLowHighInt16u(sl_zigbee_tlv_get_value_ptr(tlv));
}

///
/// Next Channel Change TLV Helpers
///
// encodes the given channel and page into a uint32 bitmask
sl_zigbee_global_tlv_next_channel_change_t sl_zigbee_global_tlv_next_channel_from_pg_ch(uint8_t page,
                                                                                        uint8_t channel)
{
  sl_zigbee_global_tlv_next_channel_change_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_NEXT_CHANNEL_CHANGE_MAX_LEN);
  uint32_t bitmask = EMBER_PAGE_CHANNEL_MASK_FROM_CHANNEL_NUMBER(page, channel);
  emberStoreLowHighInt32u(sl_zigbee_tlv_get_value_ptr(&tlv), bitmask);
  return tlv;
}

// gets the channel bitmask
uint32_t sl_zigbee_global_tlv_next_channel_change_get_bitmask(sl_zigbee_global_tlv_next_channel_change_t *tlv)
{
  return emberFetchLowHighInt32u(sl_zigbee_tlv_get_value_ptr(tlv));
}

///
/// Symmetric Passphrase TLV Helpers
///
// returns the symmetric passphrase tlv
sl_zigbee_global_tlv_symmetric_passphrase_t sl_zigbee_global_tlv_symmetric_passphrase(uint8_t *passphrase)
{
  sl_zigbee_global_tlv_symmetric_passphrase_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_MIN_LEN);
  MEMCOPY(sl_zigbee_tlv_get_value_ptr(&tlv),
          passphrase,
          ZB_GLOBAL_TLV_SYMMETRIC_PASSPHRASE_MIN_LEN);
  return tlv;
}

///
/// Router Information TLV Helpers
///

// TODO remove this in favor of the beacon_tlv definition
WEAK(uint16_t sl_zigbee_get_router_info_bitmask(void))
{
  return 0xffU;
}
sl_zigbee_global_tlv_router_information_t sl_zigbee_global_tlv_router_information(void)
{
  sl_zigbee_global_tlv_router_information_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_ROUTER_INFORMATION_MIN_LEN);
  uint16_t routerInfoBitmask = sl_zigbee_get_router_info_bitmask();
  emberStoreLowHighInt16u(sl_zigbee_tlv_get_value_ptr(&tlv), routerInfoBitmask);
  return tlv;
}

// Getter function to get the Router Information Bitmask from the TLV
uint16_t sl_zigbee_global_tlv_router_information_get_bitmask(sl_zigbee_global_tlv_router_information_t *tlv)
{
  return emberFetchLowHighInt16u(sl_zigbee_tlv_get_value_ptr(tlv));
}

///
/// device capability extensions Parameters TLV Helpers
///

sl_zigbee_global_tlv_device_capability_extension_t sl_zigbee_global_tlv_device_capability_extension_param(uint16_t bitmask)
{
  sl_zigbee_global_tlv_device_capability_extension_t tlv;

  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_DEVICE_CAPABILITY_EXTENSION_MIN_LEN);
  uint8_t *value = sl_zigbee_tlv_get_value_ptr(&tlv);
  MEMCOPY(value, &bitmask, sizeof(uint16_t));
  return tlv;
}

///
/// Fragmentation Parameters TLV Helpers
///
// returns our fragmentation parameter tlv
sl_zigbee_global_tlv_fragmentation_param_t sl_zigbee_global_tlv_fragmentation_param(void)
{
  sl_zigbee_global_tlv_fragmentation_param_t tlv;
  EmberNodeId nodeId = emberGetNodeId();
  // bit 0 - fragmentation supported?
  uint8_t options = BIT(0);
  uint16_t fragSize = sli_zigbee_maximum_incoming_transfer_size;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_FRAGMENTATION_PARAM_MIN_LEN);
  uint8_t *value = sl_zigbee_tlv_get_value_ptr(&tlv);
  MEMCOPY(value, &nodeId, sizeof(EmberNodeId));
  value += sizeof(EmberNodeId);
  *value = options;
  value++;
  emberStoreLowHighInt16u(value, fragSize);
  return tlv;
}

///
/// Joiner Encapsulation TLV Helpers
///
// populates and returns the Joiner Encasulation TLV
// if something goes wrong, the flag byte will be set to false
sl_status_t sl_zigbee_global_tlv_joiner_encapsulation(sl_zigbee_global_tlv_joiner_encap_t *encapTlv)
{
  bool attach_tlv = false;
  uint16_t bitmask = 0;

  if (encapTlv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  // NOTE in case something goes wrong we can use this to flag an error
  sl_zigbee_tlv_set_tag(encapTlv, SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_TAG_ID);
  sli_zigbee_tlv_set_length_raw(encapTlv, 0);

  // Add the following TLVs
  // - Fragmentation Parameters TLV
  sl_zigbee_global_tlv_fragmentation_param_t fragParamsTlv = sl_zigbee_global_tlv_fragmentation_param();

  // NOTE fragmentation parameters are required
  if (sl_zigbee_encap_tlv_add_tlv((sl_zigbee_tlv_t *) encapTlv,
                                  SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MAX_LEN,
                                  (sl_zigbee_tlv_t *) &fragParamsTlv) != SL_STATUS_OK) {
    return SL_STATUS_FAIL;
  }

  if ( sli_zigbee_get_join_method() != EMBER_USE_NWK_COMMISSIONING_REJOIN) {
    // - Supported Key Negotiation Methods TLV
    // NOTE we don't have to always include supported key negotiation
    sl_zigbee_global_tlv_supp_key_negotiation_t keyNeqMethodsTlv = sl_zigbee_global_tlv_supp_key_negotiation();
    // NOTE don't add dlk tlvs if we've already joined
    // TODO if we have an authentication token, don't add dlk negotiation tlvs (unless we want to?)
    if (sl_zigbee_zdo_dlk_enabled()) {
      if (sl_zigbee_encap_tlv_add_tlv((sl_zigbee_tlv_t *) encapTlv,
                                      SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MAX_LEN,
                                      (sl_zigbee_tlv_t *) &keyNeqMethodsTlv) != SL_STATUS_OK) {
        return SL_STATUS_FAIL;
      }
    }
  }

  if ( (sli_zigbee_get_device_capability_extension_data(&attach_tlv, &bitmask) == SL_STATUS_OK)
       && attach_tlv  ) {
    sl_zigbee_global_tlv_device_capability_extension_t device_capability_tlv = sl_zigbee_global_tlv_device_capability_extension_param(bitmask);
    // Device capability Extension is requested
    if (sl_zigbee_encap_tlv_add_tlv((sl_zigbee_tlv_t *) encapTlv,
                                    SL_ZIGBEE_GLOBAL_TLV_JOINER_ENCAP_MAX_LEN,
                                    (sl_zigbee_tlv_t *) &device_capability_tlv) != SL_STATUS_OK) {
      return SL_STATUS_FAIL;
    }
  }
  return SL_STATUS_OK;
}

///
///  Beacon Appendix Encapsulation TLV Helpers
///
// populates the Beacon Appendix Encasulation TLV
sl_status_t sl_zigbee_global_tlv_beacon_appendix_encapsulation(sl_zigbee_global_tlv_beacon_appendix_encap_t *encapTlv)
{
  if (encapTlv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  sl_zigbee_tlv_set_tag(encapTlv, SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_TAG_ID);
  sli_zigbee_tlv_set_length_raw(encapTlv, 0);

  // Add the following TLVs
  // - Supported Key Negotiation Methods TLV
  // - Fragmentation Parameters TLV
  sl_zigbee_global_tlv_supp_key_negotiation_t keyNeqMethodsTlv = sl_zigbee_global_tlv_supp_key_negotiation();
  sl_zigbee_global_tlv_fragmentation_param_t fragParamsTlv = sl_zigbee_global_tlv_fragmentation_param();

  // TODO maybe we need to add some assertions about sizes to prevent possible errors?
  // TODO rework the control flow here... r23 should always add fragmentation, dlk is optional...
  if (sl_zigbee_encap_tlv_add_tlv((sl_zigbee_tlv_t *) encapTlv,
                                  SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MAX_LEN,
                                  (sl_zigbee_tlv_t *) &keyNeqMethodsTlv) == SL_STATUS_OK) {
    if (sl_zigbee_encap_tlv_add_tlv((sl_zigbee_tlv_t *) encapTlv,
                                    SL_ZIGBEE_GLOBAL_TLV_BEACON_APPENDIX_ENCAP_MAX_LEN,
                                    (sl_zigbee_tlv_t *) &fragParamsTlv) == SL_STATUS_OK) {
      return SL_STATUS_OK;
    }
  }
  return SL_STATUS_FAIL;
}

///
/// Configuration Mode Parameters
///
// returns a TLV containing the provided configuration parameters bitmask
sl_zigbee_global_tlv_configuration_params_t sl_zigbee_global_tlv_configuration_params_from_bitmask(uint16_t mask)
{
  sl_zigbee_global_tlv_configuration_params_t tlv;
  sl_zigbee_tlv_set_tag(&tlv, SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_TAG_ID);
  sl_zigbee_tlv_set_length(&tlv, SL_ZIGBEE_GLOBAL_TLV_CONFIGURATION_PARAMS_MAX_LEN);
  emberStoreLowHighInt16u(sl_zigbee_tlv_get_value_ptr(&tlv), mask);
  return tlv;
}

uint16_t sl_zigbee_global_tlv_configuration_params_get_bitmask(sl_zigbee_global_tlv_configuration_params_t *tlv)
{
  return emberFetchLowHighInt16u(sl_zigbee_tlv_get_value_ptr(tlv));
}

bool sli_zigbee_tlv_validate_tag_length(uint8_t tag,
                                        uint16_t len,
                                        sl_zigbee_tlv_tag_min_length_t *env)
{
  if (tag < ZB_LOCAL_TLV_LOCAL_TAG_END) {
    return validate_length_tlv_env(tag, len, env);
  } else {
    // must be a global tlv
    // TODO EMZIGBEE-5833 figure out encapsulation validation
    return validate_length_global_tlv(tag, len);
  }
}

bool sli_zigbee_tlv_is_encap_tag_id(uint8_t tag_id)
{
  uint16_t i = 0;
  uint16_t count = sizeof(sl_zigbee_encap_tlv_global_tag_ids) / sizeof(uint8_t);
  while (i < count && tag_id != sl_zigbee_encap_tlv_global_tag_ids[i]) {
    i++;
  }
  return (i < count);
}

// a local tlv environment acts a sort of mapping for how the
// message context defines the local tlvs.  It contains a value
// indicating the number of local tlvs that are expected, and an
// array minimum lengths for the tag ids mapped to the index
static bool validate_length_tlv_env(uint8_t tag,
                                    uint16_t len,
                                    sl_zigbee_tlv_tag_min_length_t *env)
{
  if (env != NULL) {
    // search through the entire environment
    while (!IS_END_ENV(*env)) {
      if (env->tag_id == tag) {
        // make sure len is at least the minimum
        return len >= env->min_length;
      } else {
        // increment the pointer
        env++;
      }
    }
  }
  // return true for anything we aren't aware of
  return true;
}

static bool validate_length_global_tlv(uint8_t tag,
                                       uint16_t len)
{
  return validate_length_tlv_env(tag, len, global_tlv_env);
}

bool sl_zigbee_stack_tlv_id_is_manufacturer_specifc(uint8_t tag)
{
  return TLV_TAG_ID_IS_MFG_SPECIFIC(tag);
}

sl_status_t sl_zigbee_stack_specific_tlv_check(uint8_t tag,
                                               uint16_t len,
                                               sl_zigbee_tlv_tag_min_length_t *env,
                                               bool encapRecurse)
{
  sl_status_t status = SL_STATUS_NOT_SUPPORTED;
  if (!sli_zigbee_tlv_validate_tag_length(tag, len, env)) {
    status = SL_STATUS_WOULD_OVERFLOW;
  } else if (sli_zigbee_tlv_is_encap_tag_id(tag) && encapRecurse) {
    status = SL_STATUS_INVALID_MODE;
  } else {
    status = SL_STATUS_NOT_SUPPORTED;
  }
  return status;
}
