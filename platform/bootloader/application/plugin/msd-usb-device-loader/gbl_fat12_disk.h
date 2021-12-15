/***************************************************************************//**
 * @file
 * @brief Gecko Bootloader FAT12 disk API
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

#ifndef FAT12FS_H
#define FAT12FS_H

#define SLOT_ID           0           // Bootloader default storage space ID

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/
void gblfat12disk_setLBABit(uint16_t index);
void gblfat12disk_setMostRecentLBA(uint16_t blockNr);
void gblfat12disk_reProgramCheck(bool msddIdle);
void gblfat12disk_prepareFAT12Img(uint8_t *diskStorage,
                                  uint32_t numBlocks,
                                  uint8_t *flashPageBuf);

#endif // FAT12FS_H 
