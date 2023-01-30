#ifndef SL_WSRCP_BTL_INTERFACE_H
#define SL_WSRCP_BTL_INTERFACE_H

void wisun_rcp_btl_reset(struct sl_wsrcp_mac *rcp_mac);

SL_WEAK void wisun_rcp_btl_reset(struct sl_wsrcp_mac *rcp_mac) 
{
    (void)rcp_mac;
}

#endif //SL_WSRCP_BTL_INTERFACE_H