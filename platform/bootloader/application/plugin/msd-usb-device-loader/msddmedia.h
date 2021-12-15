/***************************************************************************//**
 * @file
 * @brief Media interface for Mass Storage class Device (MSD).
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

#ifndef MSDDMEDIA_H
#define MSDDMEDIA_H

#include "msdd.h"

extern uint32_t flashPageSize;

typedef struct flashStat {
  uint8_t *pPageBase;
  bool    pendingWrite;
} flashStat;

extern flashStat flashStatus;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/
bool     MSDDMEDIA_CheckAccess(MSDD_CmdStatus_TypeDef *pCmd, uint32_t lba, uint32_t sectors);
void     MSDDMEDIA_Flush(void);
uint32_t MSDDMEDIA_GetSectorCount(void);
bool     MSDDMEDIA_Init(void);
void     MSDDMEDIA_Read(MSDD_CmdStatus_TypeDef *pCmd, uint8_t *data, uint32_t sectors);
void     MSDDMEDIA_Write(MSDD_CmdStatus_TypeDef *pCmd, uint8_t *data, uint32_t sectors);

uint8_t* MSDDMEDIA_getFlashBuffer(void);
uint8_t* MSDDMEDIA_getDiskStorage(void);

#endif // MSDDMEDIA_H 
