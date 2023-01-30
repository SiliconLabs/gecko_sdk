/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_wisun_config.h"


//! Wi-SUN Device private key
const uint8_t wisun_config_device_private_key[] = {
"-----BEGIN PRIVATE KEY-----\r\n"
"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQguF1oBuIMzOtpsOMH\r\n"
"df97vr2GppQfXOKDJ4RogFMk7QChRANCAASo6qu6eHf6ACvzdrrC2kH5CFG8zij1\r\n"
"1N1V40KjRqZeHNtSwXKXDs6BuCq2gIpCC5hOxuJyl4sxa/hNXsnFfoiP\r\n"
"-----END PRIVATE KEY-----"
};

//! Wi-SUN Device certificate
const uint8_t wisun_config_device_certificate[] = {
"-----BEGIN CERTIFICATE-----\r\n"
"MIIByDCCAW6gAwIBAgIUPRtrFcA6dw03sTpD1dArHpFi65gwCgYIKoZIzj0EAwIw\r\n"
"HjEcMBoGA1UEAwwTV2ktU1VOIERlbW8gUm9vdCBDQTAgFw0yMTAzMDEwNzQyNDBa\r\n"
"GA85OTk5MTIzMTIzNTk1OVowHTEbMBkGA1UEAwwSV2ktU1VOIERlbW8gRGV2aWNl\r\n"
"MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEqOqrunh3+gAr83a6wtpB+QhRvM4o\r\n"
"9dTdVeNCo0amXhzbUsFylw7OgbgqtoCKQguYTsbicpeLMWv4TV7JxX6Ij6OBiDCB\r\n"
"hTAOBgNVHQ8BAf8EBAMCA4gwIQYDVR0lAQH/BBcwFQYJKwYBBAGC5CUBBggrBgEF\r\n"
"BQcDAjAvBgNVHREBAf8EJTAjoCEGCCsGAQUFBwgEoBUwEwYJKwYBBAGCt0ECBAYx\r\n"
"MjM0NTYwHwYDVR0jBBgwFoAUk2TUDvdoou5d8Kz6crzFH01POiQwCgYIKoZIzj0E\r\n"
"AwIDSAAwRQIhANBxFWMzNMKyA+nMK0sbCUpqK1gVMyeoKqh0zvS3COyLAiAx8nCN\r\n"
"B7RkW8RmZ0UMWY26g7P6TbqJiAI3zoKkSxpJPg==\r\n"
"-----END CERTIFICATE-----"
};

//! Wi-SUN CA certificate
const uint8_t wisun_config_ca_certificate[] = {
"-----BEGIN CERTIFICATE-----\r\n"
"MIIBojCCAUmgAwIBAgIUSOJfgI08JDWdAjuqvH3REMyjjFswCgYIKoZIzj0EAwIw\r\n"
"HjEcMBoGA1UEAwwTV2ktU1VOIERlbW8gUm9vdCBDQTAgFw0yMTAyMjIwOTU5NDFa\r\n"
"GA85OTk5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTV2ktU1VOIERlbW8gUm9vdCBD\r\n"
"QTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABG1Mn4dd9+IVJZSEcjpFKehvvRyQ\r\n"
"t9QcIBCN2ysf+BJUlFfU8TvC3w2waFrLuC+JHM+1TBEm1GLNDF7piCgqltWjYzBh\r\n"
"MBIGA1UdEwEB/wQIMAYBAf8CAQIwCwYDVR0PBAQDAgEGMB0GA1UdDgQWBBSTZNQO\r\n"
"92ii7l3wrPpyvMUfTU86JDAfBgNVHSMEGDAWgBSTZNQO92ii7l3wrPpyvMUfTU86\r\n"
"JDAKBggqhkjOPQQDAgNHADBEAiAdlM3ENdd7GHHbTsTiZMc7T5DDFQ2abeUI1be+\r\n"
"ytGaAAIgZREIYV4yhjoluqT4+snj/zQkqEqcYh/DMbx2gLKDgZ4=\r\n"
"-----END CERTIFICATE-----"
};