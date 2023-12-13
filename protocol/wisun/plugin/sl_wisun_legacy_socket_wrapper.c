#include <string.h>
#include "sl_wisun_api.h"
#include "sl_wisun_legacy_socket_wrapper.h"

#define CHECK_STATUS(retval) \
  ((retval == SOCKET_RETVAL_ERROR) ? SL_STATUS_FAIL : SL_STATUS_OK)

typedef union {
  int32_t data;
  sl_wisun_ip_address_t ip_addr;
} sockopt_data_t;

sl_status_t sl_wisun_open_socket(sl_wisun_socket_protocol_t protocol,
                                 sl_wisun_socket_id_t *socket_id)
{
  int32_t socket_type;

  sl_status_t status = SL_STATUS_FAIL;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  switch (protocol) {
    case SL_WISUN_SOCKET_PROTOCOL_UDP:
      socket_type = SOCK_DGRAM;
      break;
    case SL_WISUN_SOCKET_PROTOCOL_TCP:
      socket_type = SOCK_STREAM;
      break;
    case SL_WISUN_SOCKET_PROTOCOL_ICMP:
      socket_type = SOCK_RAW;
      break;
    default:
      goto error_handler;
      break;
  }

  socket_retval = socket(AF_INET6, socket_type | SOCK_NONBLOCK, IPPROTO_IP);
  if (socket_retval >= 0) {
    *socket_id = socket_retval;
    status = SL_STATUS_OK;
  }

  error_handler:

  return status;
}

sl_status_t sl_wisun_close_socket(sl_wisun_socket_id_t socket_id)
{
  sl_status_t status = (sl_close(socket_id) == SOCKET_RETVAL_OK) ? SL_STATUS_OK : SL_STATUS_FAIL;
  return status;
}

sl_status_t sl_wisun_sendto_on_socket(sl_wisun_socket_id_t socket_id,
                                      const sl_wisun_ip_address_t *remote_address,
                                      uint16_t remote_port,
                                      uint16_t data_length,
                                      const uint8_t *data)
{
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t dest_addr;
  dest_addr.sin6_family    = AF_INET6;
  dest_addr.sin6_port      = remote_port;
  dest_addr.sin6_flowinfo  = 0;
  dest_addr.sin6_scope_id  = 0;
  memcpy(&dest_addr.sin6_addr.address, &remote_address->address, IPV6_ADDR_SIZE);

  socket_retval = sendto(socket_id,
                         (const void *)data,
                         data_length,
                         0, //flags
                         (const struct sockaddr *)&dest_addr,
                         sizeof(sockaddr_in6_t));

  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_listen_on_socket(sl_wisun_socket_id_t socket_id)
{
  int32_t socket_retval = listen(socket_id, 0);
  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_accept_on_socket(sl_wisun_socket_id_t socket_id,
                                      sl_wisun_socket_id_t *remote_socket_id,
                                      sl_wisun_ip_address_t *remote_address,
                                      uint16_t *remote_port)
{
  sockaddr_in6_t remote_addr;

  sl_status_t status = SL_STATUS_FAIL;
  socklen_t optlen = sizeof(sockaddr_in6_t);

  int32_t socket_retval = accept(socket_id, (struct sockaddr *)&remote_addr, &optlen);
  if (socket_retval != SOCKET_INVALID_ID) {
    *remote_socket_id = socket_retval;
    *remote_address   = remote_addr.sin6_addr;
    *remote_port      = remote_addr.sin6_port;
    status            = SL_STATUS_OK;
  }
  return status;
}

sl_status_t sl_wisun_connect_socket(sl_wisun_socket_id_t socket_id,
                                    const sl_wisun_ip_address_t *remote_address,
                                    uint16_t remote_port)
{
  sockaddr_in6_t addr;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  addr.sin6_family   = AF_INET6;
  addr.sin6_port     = remote_port;
  addr.sin6_flowinfo = 0;
  addr.sin6_scope_id = 0;
  memcpy(&addr.sin6_addr.address, &remote_address->address, IPV6_ADDR_SIZE);

  socket_retval = connect(socket_id, (const struct sockaddr *)&addr, sizeof(sockaddr_in6_t));
  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_bind_socket(sl_wisun_socket_id_t socket_id,
                                 const sl_wisun_ip_address_t *local_address,
                                 uint16_t local_port)
{
  sockaddr_in6_t addr;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  addr.sin6_family   = AF_INET6;
  addr.sin6_flowinfo = 0;
  addr.sin6_port     = local_port;
  addr.sin6_scope_id = 0;
  memcpy(&addr.sin6_addr.address, &local_address->address, IPV6_ADDR_SIZE);

  socket_retval = bind(socket_id, (const struct sockaddr *)&addr, sizeof(sockaddr_in6_t));
  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_send_on_socket(sl_wisun_socket_id_t socket_id,
                                    uint16_t data_length,
                                    const uint8_t *data)
{
  int32_t socket_retval = send(socket_id, (const void *)data, data_length, 0);
  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_receive_on_socket(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_ip_address_t *remote_address,
                                       uint16_t *remote_port,
                                       uint16_t *data_length,
                                       uint8_t *data)
{
  sockaddr_in6_t addr;
  sockaddr_in6_t *addr_ptr;

  socklen_t addrlen     = sizeof(sockaddr_in6_t);
  sl_status_t status    = SL_STATUS_FAIL;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  if (remote_address) {
    addr_ptr           = &addr;
    addr.sin6_family   = AF_INET6;
    addr.sin6_port     = *remote_port;
    addr.sin6_flowinfo = 0;
    addr.sin6_scope_id = 0;
    memcpy(&addr.sin6_addr.address, &remote_address->address, IPV6_ADDR_SIZE);
  } else {
    addr_ptr = NULL;
  }

  socket_retval = recvfrom(socket_id,
                           (void *)data,
                           *(uint32_t *) data_length,
                           0,
                           (struct sockaddr *) addr_ptr,
                           &addrlen);

  if (socket_retval != SOCKET_RETVAL_ERROR) {
    *remote_address = addr.sin6_addr;
    *remote_port    = addr.sin6_port;
    status          = SL_STATUS_OK;
  }
  return status;
}

sl_status_t sl_wisun_set_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       const sl_wisun_socket_option_data_t *option_data)
{
  int32_t socket_retval;
  int32_t level;
  int32_t optname;
  const void *optval;
  socklen_t optlen;
  sl_wisun_socket_option_data_t sockopt_data;

  switch (option) {
    case SL_WISUN_SOCKET_OPTION_EVENT_MODE:
      sockopt_data.value = option_data->event_mode.mode;
      level   = APP_LEVEL_SOCKET;
      optname = SOCKET_EVENT_MODE;
      optval = &sockopt_data.value;
      optlen = sizeof(uint32_t);
      break;
    case SL_WISUN_SOCKET_OPTION_MULTICAST_GROUP:
      switch (option_data->multicast_group.action) {
        case SL_WISUN_MULTICAST_GROUP_ACTION_JOIN:
          optname = IPV6_JOIN_GROUP;
          break;
        case SL_WISUN_SOCKET_EVENT_MODE_POLLING:
          optname = IPV6_LEAVE_GROUP;
          break;
        default:
          // Unknown action
          return SL_STATUS_INVALID_TYPE;
          break;
      }
      sockopt_data.ipv6_address = option_data->multicast_group.address;
      level = IPPROTO_IPV6;
      optval  = (const void *) &sockopt_data.ipv6_address;
      optlen  = sizeof(sl_wisun_ip_address_t);
      break;
    case SL_WISUN_SOCKET_OPTION_SEND_BUFFER_LIMIT:
      sockopt_data.value = option_data->send_buffer_limit.limit;
      level   = SOL_SOCKET;
      optname = SO_SNDBUF;
      optval  = (const void *) &sockopt_data.value;
      optlen  = sizeof(int32_t);
      break;
    case SL_WISUN_SOCKET_OPTION_EDFE_MODE:
      sockopt_data.value = option_data->edfe_mode.mode;
      level   = IPPROTO_IPV6;
      optname = SOCKET_EDFE_MODE;
      optval  = (const void *) &sockopt_data.value;
      optlen  = sizeof(uint32_t);
      break;
    case SL_WISUN_SOCKET_OPTION_UNICAST_HOP_LIMIT:
      sockopt_data.value = option_data->unicast_hop_limit.hop_limit;
      level   = IPPROTO_IPV6;
      optname = IPV6_UNICAST_HOPS;
      optval  = (const void *) &sockopt_data.value;
      optlen  = sizeof(int16_t);
      break;
    case SL_WISUN_SOCKET_OPTION_MULTICAST_HOP_LIMIT:
      sockopt_data.value = option_data->unicast_hop_limit.hop_limit;
      level   = IPPROTO_IPV6;
      optname = IPV6_UNICAST_HOPS;
      optval  = (const void *) &sockopt_data.value;
      optlen  = sizeof(int16_t);
      break;
    default:
      return SL_STATUS_INVALID_TYPE;
      break;
  }
  socket_retval = setsockopt(socket_id, level, optname, optval, optlen);

  return CHECK_STATUS(socket_retval);
}

sl_status_t sl_wisun_get_socket_option(sl_wisun_socket_id_t socket_id,
                                       sl_wisun_socket_option_t option,
                                       sl_wisun_socket_option_data_t *option_data)
{
  int32_t socket_retval;
  int32_t level;
  int32_t optname;
  void *optval;
  socklen_t optlen;
  sl_wisun_socket_option_data_t sockopt_data;

  sl_status_t status = SL_STATUS_INVALID_TYPE;

  if (option == SL_WISUN_SOCKET_OPTION_SEND_BUFFER_LIMIT) {
    level   = SOL_SOCKET;
    optname = SO_SNDBUF;
    sockopt_data.value = 0;
    optval  = (void *) &sockopt_data.value;
    optlen  = sizeof(uint32_t);

    socket_retval = getsockopt(socket_id, level, optname, optval, &optlen);
    if (socket_retval != SOCKET_RETVAL_ERROR) {
      option_data->send_buffer_limit.limit = sockopt_data.value;
      status = SL_STATUS_OK;
    } else {
      status = SL_STATUS_FAIL;
    }
  }
  return status;
}
