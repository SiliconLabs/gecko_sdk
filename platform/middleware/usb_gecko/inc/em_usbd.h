/***************************************************************************//**
 * @file
 * @brief USB protocol stack library API for EFM32/EZR32.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef __EM_USBD_H
#define __EM_USBD_H

#include "em_device.h"
#if defined(USB_PRESENT) && (USB_COUNT == 1)
#include "em_usb.h"
#if defined(USB_DEVICE)

#if !defined(SL_SUPRESS_GECKO_USB_DEPRECATION_WARNINGS)
#warning  Warning: Gecko USB is deprecated and will be removed in an upcoming release; Please consider migrating to sl_usb.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#if defined(DEBUG_USB_API)
#define DEBUG_TRACE_ABORT(x)                                    \
  {                                                             \
    if ( x == USB_STATUS_EP_STALLED )                           \
    {  DEBUG_USB_API_PUTS("\nEP cb(), EP stalled");           } \
    else if ( x == USB_STATUS_EP_ABORTED )                      \
    {  DEBUG_USB_API_PUTS("\nEP cb(), EP aborted");           } \
    else if ( x == USB_STATUS_DEVICE_UNCONFIGURED )             \
    {  DEBUG_USB_API_PUTS("\nEP cb(), device unconfigured");  } \
    else if ( x == USB_STATUS_DEVICE_SUSPENDED )                \
    {  DEBUG_USB_API_PUTS("\nEP cb(), device suspended");     } \
    else /* ( x == USB_STATUS_DEVICE_RESET ) */                 \
    {  DEBUG_USB_API_PUTS("\nEP cb(), device reset");         } \
  }
#else
#define DEBUG_TRACE_ABORT(x)
#endif

extern USBD_Device_TypeDef *dev;
extern volatile bool USBD_poweredDown;

__STATIC_INLINE void USBD_ArmEp0(USBD_Ep_TypeDef *ep);
__STATIC_INLINE void USBD_ArmEpN(USBD_Ep_TypeDef *ep);
__STATIC_INLINE void USBD_AbortEp(USBD_Ep_TypeDef *ep);

void USBD_SetUsbState(USBD_State_TypeDef newState);

int  USBDCH9_SetupCmd(USBD_Device_TypeDef *device);

void USBDEP_Ep0Handler(USBD_Device_TypeDef *device);
void USBDEP_EpHandler(uint8_t epAddr);

void USBDINT_RemoteWakeup(void);

__STATIC_INLINE void USBD_ActivateAllEps(bool forceIdle)
{
  int i;

  for ( i = 1; i <= NUM_EP_USED; i++ ) {
    USBDHAL_ActivateEp(&dev->ep[i], forceIdle);
  }
}

__STATIC_INLINE void USBD_ArmEp(USBD_Ep_TypeDef *ep)
{
  if ( ep->num == 0 ) {
    USBD_ArmEp0(ep);
  } else {
    USBD_ArmEpN(ep);
  }
}

__STATIC_INLINE void USBD_ArmEp0(USBD_Ep_TypeDef *ep)
{
  if ( ep->in ) {
    if ( ep->remaining == 0 ) {     /* Zero Length Packet? */
      ep->zlp = 1;
    }

    USBDHAL_SetEp0InDmaPtr(ep->buf);
    USBDHAL_StartEp0In(SL_MIN(ep->remaining, ep->packetSize),
                       dev->ep0MpsCode);
  } else {
    USBDHAL_SetEp0OutDmaPtr(ep->buf);
    USBDHAL_StartEp0Out(ep->packetSize, dev->ep0MpsCode);
  }
}

__STATIC_INLINE void USBD_ArmEpN(USBD_Ep_TypeDef *ep)
{
  if ( ep->in ) {
    USBDHAL_StartEpIn(ep);
  } else {
    USBDHAL_StartEpOut(ep);
  }
}

__STATIC_INLINE void USBD_DeactivateAllEps(USB_Status_TypeDef reason)
{
  int i;
  USBD_Ep_TypeDef *ep;

  for ( i = 1; i <= NUM_EP_USED; i++ ) {
    ep = &dev->ep[i];

    if ( ep->state == D_EP_IDLE ) {
      USBDHAL_DeactivateEp(ep);
    }
  }

  USBDHAL_AbortAllTransfers(reason);
}

__STATIC_INLINE USBD_Ep_TypeDef *USBD_GetEpFromAddr(uint8_t epAddr)
{
  int epIndex;
  USBD_Ep_TypeDef *ep = NULL;

  if ( epAddr & USB_SETUP_DIR_MASK ) {
    epIndex = dev->inEpAddr2EpIndex[epAddr & USB_EPNUM_MASK];
  } else {
    epIndex = dev->outEpAddr2EpIndex[epAddr & USB_EPNUM_MASK];
  }

  if ( epIndex ) {
    #if defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Warray-bounds"
    #endif

    ep = &dev->ep[epIndex];

    #if defined(__GNUC__)
    #pragma GCC diagnostic pop
    #endif
  } else if ( (epAddr & USB_EPNUM_MASK) == 0 ) {
    ep = &dev->ep[0];
  }

  return ep;
}

__STATIC_INLINE void USBD_ReArmEp0(USBD_Ep_TypeDef *ep)
{
  if ( ep->in ) {
    USBDHAL_StartEp0In(SL_MIN(ep->remaining, ep->packetSize),
                       dev->ep0MpsCode);
  } else {
    USBDHAL_StartEp0Out(ep->packetSize, dev->ep0MpsCode);
  }
}

__STATIC_INLINE void USBD_AbortEp(USBD_Ep_TypeDef *ep)
{
  if ( ep->state == D_EP_IDLE ) {
    return;
  }

  if ( ep->in ) {
    USBDHAL_AbortEpIn(ep);
  } else {
    USBDHAL_AbortEpOut(ep);
  }
}

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif /* defined( USB_DEVICE ) */
#endif /* defined( USB_PRESENT ) && ( USB_COUNT == 1 ) */
#endif /* __EM_USBD_H */
