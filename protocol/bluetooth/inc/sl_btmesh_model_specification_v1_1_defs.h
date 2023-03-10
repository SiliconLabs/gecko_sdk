/******************************************************************************/
/**
 * @file   sl_btmesh_model_specification_defs.h
 * @brief  Silicon Labs Bluetooth Mesh Model v1.1 Specification Definitions
 *
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_BTMESH_MODEL_SPECIFICATION_V1_1_DEFS_H
#define SL_BTMESH_MODEL_SPECIFICATION_V1_1_DEFS_H

/** Device Firmware Update Server model ID */
#define MESH_DFU_SERVER_MODEL_ID                        0x1402
/** Device Firmware Update Client model ID */
#define MESH_DFU_CLIENT_MODEL_ID                        0x1403
/** Device Firmware Update Distributor Server model ID */
#define MESH_DFU_DISTRIBUTOR_SERVER_MODEL_ID            0x1404
/** Device Firmware Update Distributor Client model ID */
#define MESH_DFU_DISTRIBUTOR_CLIENT_MODEL_ID            0x1405
/** BLOB Transfer Server model ID */
#define MESH_MBT_SERVER_MODEL_ID                        0x1400
/** BLOB Transfer Client model ID */
#define MESH_MBT_CLIENT_MODEL_ID                        0x1401

//TODO are subject to change in final specification
/** Remote provisioning server */
#define MESH_REMOTE_PROV_SERVER_MODEL_ID  0x0004
/** Remote provisioning server */
#define MESH_REMOTE_PROV_CLIENT_MODEL_ID 0x0005
/** Private Beacon server */
#define MESH_PRIVATE_BEACON_SERVER_MODEL_ID   0x000A
/** Private Beacon Client */
#define MESH_PRIVATE_BEACON_CLIENT_MODEL_ID   0x000B

#define MBT_TRANSFER_GET    0x8300
#define MBT_TRANSFER_START  0x8301
#define MBT_TRANSFER_CANCEL 0x8302
#define MBT_TRANSFER_STATUS 0x8303
#define MBT_BLOCK_START     0x8304
#define MBT_CHUNK           0x66
#define MBT_BLOCK_GET       0x8305
#define MBT_BLOCK_STATUS    0x67
#define MBT_INFO_GET        0x8306
#define MBT_INFO_STATUS     0x8307
#define MBT_PARTIAL_BLOCK_REPORT 0x68

#define DFU_INFORMATION_GET                     0x8308
#define DFU_INFORMATION_STATUS                  0x8309
#define DFU_METADATA_CHECK                      0x830A
#define DFU_METADATA_STATUS                     0x830B
#define DFU_UPDATE_GET                          0x830C
#define DFU_UPDATE_START                        0x830D
#define DFU_UPDATE_CANCEL                       0x830E
#define DFU_UPDATE_APPLY                        0x830F
#define DFU_UPDATE_STATUS                       0x8310
#define DFU_DISTRIBUTION_NODES_ADD              0x8311
#define DFU_DISTRIBUTION_NODES_DELETE_ALL       0x8312
#define DFU_DISTRIBUTION_NODES_STATUS           0x8313
#define DFU_DISTRIBUTION_NODES_GET              0x8314
#define DFU_DISTRIBUTION_NODES_LIST             0x8315
#define DFU_DISTRIBUTION_CAPABILITIES_GET       0x8316
#define DFU_DISTRIBUTION_CAPABILITIES_STATUS    0x8317
#define DFU_DISTRIBUTION_GET                    0x8318
#define DFU_DISTRIBUTION_START                  0x8319
#define DFU_DISTRIBUTION_CANCEL                 0x831B
#define DFU_DISTRIBUTION_APPLY                  0x831C
#define DFU_DISTRIBUTION_STATUS                 0x831D
#define DFU_DISTRIBUTION_UPLOAD_GET             0x831E
#define DFU_DISTRIBUTION_UPLOAD_START           0x831F
#define DFU_DISTRIBUTION_UPLOAD_OOB_START       0x8320
#define DFU_DISTRIBUTION_UPLOAD_CANCEL          0x8321
#define DFU_DISTRIBUTION_UPLOAD_STATUS          0x8322
#define DFU_DISTRIBUTION_FW_GET                 0x8323
#define DFU_DISTRIBUTION_FW_GET_BY_INDEX        0x8324
#define DFU_DISTRIBUTION_FW_DELETE              0x8325
#define DFU_DISTRIBUTION_FW_DELETE_ALL          0x8326
#define DFU_DISTRIBUTION_FW_STATUS              0x8327
#define DFU_DISTRIBUTION_SUSPEND                0x831A

/** Firmware List index value representing "not found" */
#define MESH_DFU_FW_INDEX_NOT_FOUND  0xffff

/** Minimum length of a FWID. Must contain a 2-byte Company ID, at minimum */
#define MESH_DFU_FWID_MIN_LEN         2

/** Maximum length of a FWID. 2-byte Company ID + 106 B is the maximum length */
#define MESH_DFU_FWID_MAX_LEN         108

/** Minimum URI length */
#define MESH_DFU_URI_MIN_LEN          0

/** Maximum URI length */
#define MESH_DFU_URI_MAX_LEN          255

/** Minimum metadata length */
#define MESH_DFU_METADATA_MIN_LEN     0

/** Maximum metadata length */
#define MESH_DFU_METADATA_MAX_LEN     255

/** If the Supported URI Scheme Names state exists, it is at least 1 byte long */
#define MESH_DFU_URI_SCHEMES_MIN_LEN  1

/** Maximum Supported URI Scheme Names length */
#define MESH_DFU_URI_SCHEMES_MAX_LEN  255

#endif
