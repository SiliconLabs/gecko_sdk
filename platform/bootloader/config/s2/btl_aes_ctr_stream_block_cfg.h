/***************************************************************************//**
 * @file
 * @brief Configuration header for bootloader aes stream block
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef BTL_AES_CTR_STREAM_BLOCK_CFG_H
#define BTL_AES_CTR_STREAM_BLOCK_CFG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <e BOOTLOADER_AES_CTR_STREAM_BLOCK_CFG_ON> Enable AES CTR stream block size configuration
// <i> Default: 0
// <i> Enable AES CTR Stream Block size configuration to change the number of stream blocks that are pre-computed.
#define BOOTLOADER_AES_CTR_STREAM_BLOCK_CFG_ON                  0
// <o BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED> Set the Number of AES CTR Stream Blocks
// <i> Default: 1
// <i> BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED allows to configure the stream block size that are pre-computed
#define BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED  1
// </e>

// <<< end of configuration section >>>

#if (BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED != 1U)  \
  && (BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED != 2U) \
  && (BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED != 4U) \
  && (BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED != 8U)
#error "Recommnded values for BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED value must be 1 or 2 or 4 or 8"
#endif

#if defined(BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED)
#define SLI_SE_AES_CTR_NUM_BLOCKS_BUFFERED BOOTLOADER_AES_CTR_NUM_BLOCKS_BUFFERED
#endif

#endif //BTL_AES_CTR_STREAM_BLOCK_CFG_H
