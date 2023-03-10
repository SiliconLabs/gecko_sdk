/***************************************************************************//**
 * @file sl_btmesh_provisioning_records.h
 * @brief Mesh provisioning records
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_PROVISIONING_RECORDS_H
#define SL_BTMESH_PROVISIONING_RECORDS_H

/*
 * Some provisioning records, such as device X.509 certificate, are
 * device specific (each device has its own data for the record) while
 * other records are not device specific (each device in a class of
 * devices has the same data for the record).
 *
 * Non device specific records are stored as constant data in the
 * firmware image. This header is for the definitions application
 * can use to set those constants.
 */

/**
 * Provisioning record that is constant across a class of devices,
 * i.e., is not device-specific.
 */
struct mesh_const_provisioning_record {
  const uint8_t *ptr; //< Provisioning record data
  uint16_t len; //< Length of provisioning record data
};

/** Number of spec-defined intermediate certificates */
#define MESH_INTERMEDIATE_CERTIFICATE_COUNT 15

/**
 * Full set of constant provisioning records
 */
struct mesh_const_provisioning_records {
  /** Certificate-based provisioning base URI */
  struct mesh_const_provisioning_record base_uri;
  /** Complete local name */
  struct mesh_const_provisioning_record complete_local_name;
  /** Appearance */
  struct mesh_const_provisioning_record appearance;
  /** Intermediate certificate 1 to 15 */
  struct mesh_const_provisioning_record intermediate_certificate[MESH_INTERMEDIATE_CERTIFICATE_COUNT];
};

/**
 * Constant provisioning records of the device. Application can set
 * the value of individual provisioning records by setting the value
 * of this pointer to point to a structure filled with the record data.
 */
extern const struct mesh_const_provisioning_records *mesh_const_provisioning_records;

#endif
