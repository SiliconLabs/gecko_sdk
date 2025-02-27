/*******************************************************************************
 * @file
 * @brief Stub implementation of the tcp interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <openthread/instance.h>
#include <openthread/message.h>

#include "bsdtcp/tcp_var.h"
#include "lib/cbuf.h"

void bmp_init(uint8_t *buf, size_t numbytes)
{
    OT_UNUSED_VARIABLE(buf);
    OT_UNUSED_VARIABLE(numbytes);
}

size_t cbuf_free_space(struct cbufhead *chdr)
{
    OT_UNUSED_VARIABLE(chdr);
    return 0;
}

void cbuf_init(struct cbufhead *chdr, uint8_t *buf, size_t len)
{
    OT_UNUSED_VARIABLE(chdr);
    OT_UNUSED_VARIABLE(buf);
    OT_UNUSED_VARIABLE(len);
}

size_t cbuf_pop(struct cbufhead *chdr, size_t numbytes)
{
    OT_UNUSED_VARIABLE(chdr);
    OT_UNUSED_VARIABLE(numbytes);
    return 0;
}

void cbuf_reference(const struct cbufhead *chdr, struct otLinkedBuffer *first, struct otLinkedBuffer *second)
{
    OT_UNUSED_VARIABLE(chdr);
    OT_UNUSED_VARIABLE(first);
    OT_UNUSED_VARIABLE(second);
}

void cbuf_contiguify(struct cbufhead *chdr, uint8_t *bitmap)
{
    OT_UNUSED_VARIABLE(chdr);
    OT_UNUSED_VARIABLE(bitmap);
}

size_t cbuf_used_space(struct cbufhead *chdr)
{
    OT_UNUSED_VARIABLE(chdr);
    return 0;
}

void initialize_tcb(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
}

void lbuf_init(struct lbufhead *buffer)
{
    OT_UNUSED_VARIABLE(buffer);
}

size_t lbuf_used_space(const struct lbufhead *buffer)
{
    OT_UNUSED_VARIABLE(buffer);
    return 0;
}

int tcp6_usr_connect(struct tcpcb *tp, struct sockaddr_in6 *sinp6)
{
    OT_UNUSED_VARIABLE(tp);
    OT_UNUSED_VARIABLE(sinp6);
    return ENOSYS;
}

void tcp_dropwithreset(struct ip6_hdr *ip6,
                       struct tcphdr  *th,
                       struct tcpcb   *tp,
                       otInstance     *instance,
                       int             tlen,
                       int             rstreason)
{
    OT_UNUSED_VARIABLE(ip6);
    OT_UNUSED_VARIABLE(th);
    OT_UNUSED_VARIABLE(tp);
    OT_UNUSED_VARIABLE(instance);
    OT_UNUSED_VARIABLE(tlen);
    OT_UNUSED_VARIABLE(rstreason);
}

int tcplp_input(struct ip6_hdr       *ip6,
                struct tcphdr        *th,
                otMessage            *msg,
                struct tcpcb         *tp,
                struct tcpcb_listen  *tpl,
                struct tcplp_signals *sig)
{
    OT_UNUSED_VARIABLE(ip6);
    OT_UNUSED_VARIABLE(th);
    OT_UNUSED_VARIABLE(msg);
    OT_UNUSED_VARIABLE(tp);
    OT_UNUSED_VARIABLE(tpl);
    OT_UNUSED_VARIABLE(sig);
    return ENOSYS;
}

int tcp_timer_2msl(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

int tcp_timer_active(struct tcpcb *tp, uint32_t timer_type)
{
    OT_UNUSED_VARIABLE(tp);
    OT_UNUSED_VARIABLE(timer_type);
    return ENOSYS;
}

int tcp_timer_delack(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

int tcp_timer_keep(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

int tcp_timer_persist(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

int tcp_timer_rexmt(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

void tcp_usr_abort(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
}

int tcp_usr_rcvd(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}

int tcp_usr_send(struct tcpcb          *tp,
                 int                    moretocome,
                 struct otLinkedBuffer *data,
                 size_t                 extendby,
                 struct sockaddr_in6   *nam)
{
    OT_UNUSED_VARIABLE(tp);
    OT_UNUSED_VARIABLE(moretocome);
    OT_UNUSED_VARIABLE(data);
    OT_UNUSED_VARIABLE(extendby);
    OT_UNUSED_VARIABLE(nam);
    return ENOSYS;
}

int tcp_usr_shutdown(struct tcpcb *tp)
{
    OT_UNUSED_VARIABLE(tp);
    return ENOSYS;
}
