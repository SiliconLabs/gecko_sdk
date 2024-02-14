/*
 * Copyright (c) 2022 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */
#ifndef SL_WSRCP_API_H
#define SL_WSRCP_API_H

#include <stdint.h>

struct mcps_data_conf_payload_s;
struct mcps_data_conf_s;
struct mcps_data_ie_list;
struct mcps_data_ind_s;
struct sl_wsrcp_mac;

// Share with legacy implementation
extern uint32_t g_key_id_cache[7];

bool rcp_rx(struct sl_wsrcp_mac *rcp_mac);
void rcp_on_err(int code, const char *fmt, ...);
void rcp_ind_nop(struct sl_wsrcp_mac *rcp_mac);
void rcp_ind_reset(struct sl_wsrcp_mac *rcp_mac);
void rcp_cnf_data_tx(struct sl_wsrcp_mac *rcp_mac,
                     const struct mcps_data_conf_s *cnf,
                     const struct mcps_data_conf_payload_s *ie_ext);
void rcp_ind_data_rx(struct sl_wsrcp_mac *rcp_mac,
                     const struct mcps_data_ind_s *ind,
                     const struct mcps_data_ie_list *ie_ext);

#endif
