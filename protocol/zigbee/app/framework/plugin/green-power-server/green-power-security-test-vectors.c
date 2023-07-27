/***************************************************************************//**
 * @file
 * @brief GP security test vectors code
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#else // !SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "green-power-adapter.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "green-power-server.h"

#include "stack/include/zigbee-security-manager.h"

#if (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
// test vector values
// tclk
// testKey
// testKey1
// testKey2
// testKey3
// testKey4
// testKey5
// testKey11
// testKey1152
// testKey1153

// expects
// Test Vector (A.1.5.6.2.1) #1 - :8C 90 21 43 65 87 11 22 33 44 F3 00 CC A0 BB 2E
// Test Vector (A.1.5.6.2.2) #1 - :8C 98 21 43 65 87 11 22 33 44 9E 7E 14 0F B5 DA
// Test Vector (A.1.5.8.1)   #1 - :C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC CD CE CF
//                           #2 - :61 F1 63 A9
// Test Vector (A.1.5.13.1)  #1 - :C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC CD CE CF
//                           #2 - :3F 9A E0 B5
// Test Vector (A.1.5.8.3)   #1 - :E9 00 06 63 1D 0D FD C6 38 06 8E 5E 69 67 D3 25
//                           #2 - :27 55 9F 75
// Test Vector (A.1.5.13.2)  #1 - :2D 23 8F 58 07 1C 07 8A B0 5C 23 5E 4D ED DF 3B
//                           #2 - :DE F5 18 7D
// Test Vector (A.1.5.4.2)   #1 - :CF 78 7E 72
// Test Vector (A.1.5.4.3)   #1 - :CA 43 24 DD
// Test Vector (A.1.5.5.2)   #1 - :AD 69 A9 78
// Test Vector (A.1.5.5.3)   #1 - :5F 1A 30 34
// Test Vector (A.1.5.9.2)   #1 - :C5 A8 3C 5E
// Test Vector (A.1.5.9.3)   #1 - :D2 A2 36 1B
// Test Vector (A.1.5.7.1)   #1 - :BA 88 86 7F C0 09 39 87 EB 88 64 CE BE 5F C6 13
// Test Vector (A.1.5.7.2)   #1 - :7A 3A 73 43 8D 6E 47 55 28 81 A0 28 AD 59 23 2E
// Test Vector (A.1.5.12.1)  #1 - :8A E7 5B 07 5F 7A 13 23 06 08 FF 7E 93 07 97 6D

#define HAS_MIC_EXPECT 1
#define HAS_KEY_EXPECT 2
struct GpSecurityTestVector {
  const char* title;
  const uint8_t flags;
  const uint8_t mic_expect[4];
  const uint8_t key_expect[16];
};

static struct GpSecurityTestVector gp_test_vector_expects[] = {
  {
    .title = "A.1.5.6.2.1",
    .flags = HAS_KEY_EXPECT,
    // NOTE this is actually the value of an encrypted payload, it just happens to be 16 bytes
    .key_expect = {
      0x8C, 0x90, 0x21, 0x43, 0x65, 0x87, 0x11, 0x22, 0x33, 0x44, 0xF3, 0x00, 0xCC, 0xA0, 0xBB, 0x2E,
    }
  },
  {
    .title = "A.1.5.6.2.2",
    .flags = HAS_KEY_EXPECT,
    .key_expect = {
      0x8C, 0x98, 0x21, 0x43, 0x65, 0x87, 0x11, 0x22, 0x33, 0x44, 0x9E, 0x7E, 0x14, 0x0F, 0xB5, 0xDA,
    }
  },
  {
    .title = "A.1.5.8.1",
    .flags = HAS_MIC_EXPECT | HAS_KEY_EXPECT,
    .mic_expect = {
      0x61, 0xF1, 0x63, 0xA9,
    },
    .key_expect = {
      0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    }
  },
  {
    .title = "A.1.5.13.1",
    .flags = HAS_MIC_EXPECT | HAS_KEY_EXPECT,
    .mic_expect = {
      0x3F, 0x9A, 0xE0, 0xB5,
    },
    .key_expect = {
      0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    }
  },
  {
    .title = "A.1.5.8.3",
    .flags = HAS_MIC_EXPECT | HAS_KEY_EXPECT,
    .mic_expect = {
      0x27, 0x55, 0x9F, 0x75,
    },
    .key_expect = {
      0xE9, 0x00, 0x06, 0x63, 0x1D, 0x0D, 0xFD, 0xC6, 0x38, 0x06, 0x8E, 0x5E, 0x69, 0x67, 0xD3, 0x25,
    }
  },
  {
    .title = "A.1.5.13.2",
    .flags = HAS_MIC_EXPECT | HAS_KEY_EXPECT,
    .mic_expect = {
      0xDE, 0xF5, 0x18, 0x7D,
    },
    .key_expect = {
      0x2D, 0x23, 0x8F, 0x58, 0x07, 0x1C, 0x07, 0x8A, 0xB0, 0x5C, 0x23, 0x5E, 0x4D, 0xED, 0xDF, 0x3B,
    }
  },
  {
    .title = "A.1.5.4.2",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0xCF, 0x78, 0x7E, 0x72,
    }
  },
  {
    .title = "A.1.5.4.3",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0xCA, 0x43, 0x24, 0xDD,
    }
  },
  {
    .title = "A.1.5.5.2",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0xAD, 0x69, 0xA9, 0x78,
    }
  },
  {
    .title = "A.1.5.5.3",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0x5F, 0x1A, 0x30, 0x34,
    }
  },
  {
    .title = "A.1.5.9.2",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0xC5, 0xA8, 0x3C, 0x5E,
    }
  },
  {
    .title = "A.1.5.9.3",
    .flags = HAS_MIC_EXPECT,
    .mic_expect = {
      0xD2, 0xA2, 0x36, 0x1B,
    }
  },
  {
    .title = "A.1.5.7.1",
    .flags = HAS_KEY_EXPECT,
    .key_expect = {
      0xBA, 0x88, 0x86, 0x7F, 0xC0, 0x09, 0x39, 0x87, 0xEB, 0x88, 0x64, 0xCE, 0xBE, 0x5F, 0xC6, 0x13,
    }
  },
  {
    .title = "A.1.5.7.2",
    .flags = HAS_KEY_EXPECT,
    .key_expect = {
      0x7A, 0x3A, 0x73, 0x43, 0x8D, 0x6E, 0x47, 0x55, 0x28, 0x81, 0xA0, 0x28, 0xAD, 0x59, 0x23, 0x2E,
    }
  },
  {
    .title = "A.1.5.12.1",
    .flags = HAS_KEY_EXPECT,
    .key_expect = {
      0x8A, 0xE7, 0x5B, 0x07, 0x5F, 0x7A, 0x13, 0x23, 0x06, 0x08, 0xFF, 0x7E, 0x93, 0x07, 0x97, 0x6D,
    }
  }
};

static bool checkGpSecurityTestResults(struct GpSecurityTestVector *testExpect,
                                       uint8_t *micResult,
                                       uint8_t *keyResult)
{
  // TODO check for gpsecuritytestvector being the wrong address???
  if (testExpect == NULL) {
    emberAfGreenPowerClusterPrintln("[[!! ERROR !!]] null test vector expects");
    return false;
  }
  if (testExpect->flags & HAS_MIC_EXPECT && micResult == NULL) {
    emberAfGreenPowerClusterPrintln("[[!! ERROR !!]] gp test vector config (%s) expects mic result, received none", testExpect->title);
    return false;
  }
  if (testExpect->flags & HAS_KEY_EXPECT && keyResult == NULL) {
    emberAfGreenPowerClusterPrintln("[[!! ERROR !!]] gp test vector config (%s) expects 'key' result, received none", testExpect->title);
    return false;
  }
  bool micMatch = true;
  bool keyMatch = true;
  if (testExpect->flags & HAS_MIC_EXPECT) {
    // print things out...
    micMatch = MEMCOMPARE(testExpect->mic_expect, micResult, 4) == 0;
    if (!micMatch) {
      emberAfGreenPowerClusterPrintln("[[!! FAIL !!]] gp test vector (%s) 'MIC' mismatch", testExpect->title);
    }
  }
  if (testExpect->flags & HAS_KEY_EXPECT) {
    keyMatch = MEMCOMPARE(testExpect->key_expect, keyResult, 16) == 0;
    if (!keyMatch) {
      emberAfGreenPowerClusterPrintln("[[!! FAIL !!]] gp test vector (%s) 'KEY' mismatch", testExpect->title);
    }
  }
  if (micMatch && keyMatch) {
    emberAfGreenPowerClusterPrintln("[[!! PASS !!]] gp test vector (%s)", testExpect->title);
    return true;
  } else {
    return false;
  }
}

EmberStatus sli_zigbee_af_gp_test_security(void)
{
  EmberStatus status = EMBER_ERR_FATAL;
  bool all_test_vectors_passed = true;
  bool single_test_vector_passed = true;
  EmberKeyData tcLk    = { { 0x5A, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6C, 0x6C, 0x69, 0x61, 0x6E, 0x63, 0x65, 0x30, 0x39 } };
  uint8_t mic[4] = { 0 };
  //uint128_t testIeee = 0x8877665544332211; in Little endian order
  uint8_t testIeee[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
  EmberGpAddress gpdAddr;
  uint32_t fc = 0;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //A.1.5.6 Security test  vectors for ApplicationID = 0b000 and bidirectional operation
  //A.1.5.6.2 Security test vectors for a shared key
  //A.1.5.6.2.1 SecurityLevel = 0b10
  //Outgoing
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.6.2.1) Secured outGoing GPDF command id = 0xF3 Payload={0} SharedKey, seclevel = 0b10 Application Id 0");
  EmberKeyData testKey5 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  fc = 0x44332211;
  uint8_t gpdCommandId = 0xF3;
  uint8_t gpdCommandPayload[2] = { 1, 0 }; //Format to specefy payload = [payloadlength, <payload bytes>]
  uint8_t securedOutgoingGpdf[100] = { 0 };

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey5);
  //loads key into encryption core
  sl_zb_sec_man_load_key_context(&context);

  uint8_t securedGpdfFrameLength = sli_zigbee_af_gp_outgoing_command_encrypt(&gpdAddr,
                                                                             fc,
                                                                             0, // Key type : Shared Key = 0, Individual Key = 1
                                                                             2, // Security Level : Encrypted = 3, MIC only = 2
                                                                             gpdCommandId,
                                                                             gpdCommandPayload, // format [payloadlength, <payload bytes>]
                                                                             securedOutgoingGpdf, // Collector for the secured frame
                                                                             100);

  emberAfGreenPowerClusterPrint("Secured Frame  :");
  for (int i = 0; i < securedGpdfFrameLength; i++) {
    emberAfGreenPowerClusterPrint("%x ", securedOutgoingGpdf[i]);
  }
  emberAfGreenPowerClusterPrint("");
  emberAfGreenPowerClusterPrintln("\nExpected Frame :8C 90 21 43 65 87 11 22 33 44 F3 00 CC A0 BB 2E ");
  emberAfGreenPowerClusterPrintln("");
  // gp test vector check - 0
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[0],
                                                         NULL,
                                                         securedOutgoingGpdf);
  if (all_test_vectors_passed && !single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 0]]");
    all_test_vectors_passed = false;
  }

  //A.1.5.6.2.2 SecurityLevel = 0b11
  //Outgoing
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.6.2.2) Secured outGoing GPDF command id = 0xF3 Payload={0} SharedKey, seclevel = 0b11 Application Id 0");
  securedGpdfFrameLength = sli_zigbee_af_gp_outgoing_command_encrypt(&gpdAddr,
                                                                     fc,
                                                                     0, // Key type : Shared Key = 0, Individual Key = 1
                                                                     3, // Security Level : Encrypted = 3, MIC only = 2
                                                                     gpdCommandId,
                                                                     gpdCommandPayload, // format [payloadlength, <payload bytes>]
                                                                     securedOutgoingGpdf, // Collector for the secured frame
                                                                     100);

  emberAfGreenPowerClusterPrint("Secured Frame  :");
  for (int i = 0; i < securedGpdfFrameLength; i++) {
    emberAfGreenPowerClusterPrint("%x ", securedOutgoingGpdf[i]);
  }
  emberAfGreenPowerClusterPrint("");
  emberAfGreenPowerClusterPrintln("\nExpected Frame :8C 98 21 43 65 87 11 22 33 44 9E 7E 14 0F B5 DA ");
  emberAfGreenPowerClusterPrintln("");
  // gp test vector check - 1
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[1],
                                                         NULL,
                                                         securedOutgoingGpdf);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 1]]");
    all_test_vectors_passed = false;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  gpdAddr.id.sourceId = 0x12345678;
  gpdAddr.applicationId = 0;
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.8.1) for TCLK Decryption of Incoming Key");
  emberAfGreenPowerClusterPrintln("Incoming decrypted key for App Id = %d GpdId= 0x%4X", gpdAddr.applicationId, gpdAddr.id.sourceId);
  EmberKeyData incomingEncryptedKey1 = { { 0x7D, 0x17, 0x7B, 0xD2, 0x9E, 0xA0, 0xFD, 0xA6, 0xB0, 0x17, 0x03, 0x65, 0x87, 0xDC, 0x26, 0x00 } };

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&tcLk);
  //loads tcLk into encryption core
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_key_tc_lk_derivation(&gpdAddr,
                                        0,
                                        mic,
                                        &incomingEncryptedKey1,
                                        true);
  emberAfGreenPowerClusterPrint("Decrypted Key :");
  for (int i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    emberAfCorePrint("%x ", incomingEncryptedKey1.contents[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected Key  :C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC CD CE CF");
  emberAfGreenPowerClusterPrint("\nGenerated MIC :");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC  :61 F1 63 A9");
  // gp test vector check - 2
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[2],
                                                         mic,
                                                         incomingEncryptedKey1.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 2]]");
    all_test_vectors_passed = false;
  }

  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.13.1) for TCLK Decryption of Incoming Key IEEE Address");
  emberAfGreenPowerClusterPrintln("Incoming decrypted key for App Id = 2 Ieee= 0x8877665544332211");
  MEMCOPY(gpdAddr.id.gpdIeeeAddress, testIeee, 8);
  gpdAddr.endpoint = 0x0A;
  gpdAddr.applicationId = 2;
  EmberKeyData incomingEncryptedKey11 = { { 0x2D, 0xF0, 0x67, 0xAF, 0xCD, 0x4D, 0x8C, 0xF0, 0xF5, 0x2E, 0x6C, 0x85, 0x8F, 0x31, 0x4E, 0x22 } };

  sli_zigbee_af_gp_key_tc_lk_derivation(&gpdAddr,
                                        0,
                                        mic,
                                        &incomingEncryptedKey11,
                                        true);
  emberAfGreenPowerClusterPrint("Decrypted Key :");
  for (int i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    emberAfCorePrint("%x ", incomingEncryptedKey11.contents[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected Key  :C0 C1 C2 C3 C4 C5 C6 C7 C8 C9 CA CB CC CD CE CF");
  emberAfGreenPowerClusterPrint("\nGenerated MIC :");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected MIC  :3F 9A E0 B5");
  // gp test vector check - 3
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[3],
                                                         mic,
                                                         incomingEncryptedKey1.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 3]]");
    all_test_vectors_passed = false;
  }

  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.8.3) for TCLK Protected Key for Commissioning Reply");
  emberAfGreenPowerClusterPrintln("OutGoing Protected Key for App Id = 0 GpdId= 0x12345678, fc =4 ");
  // Security Level 3 Key derivation Application Id 0 - Out going
  EmberKeyData testKey = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  gpdAddr.id.sourceId = 0x12345678;
  gpdAddr.applicationId = 0;
  fc = 4;
  sli_zigbee_af_gp_key_tc_lk_derivation(&gpdAddr,
                                        fc,
                                        mic,
                                        &testKey,
                                        false);
  emberAfGreenPowerClusterPrint("Encrypted Key :");
  for (int i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    emberAfCorePrint("%x ", testKey.contents[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected Key  :E9 00 06 63 1D 0D FD C6 38 06 8E 5E 69 67 D3 25");
  emberAfGreenPowerClusterPrint("\nGenerated MIC :");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected MIC  :27 55 9F 75");
  // gp test vector check - 4
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[4],
                                                         mic,
                                                         testKey.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 4]]");
    all_test_vectors_passed = false;
  }

  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.13.2) for TCLK Protected Key for Commissioning Reply");
  emberAfGreenPowerClusterPrintln("OutGoing Protected Key for App Id = 2 Ieee= 0x8877665544332211, fc =3 ");
  // Commissioning Reply TC-LK Protected key App Id = 2
  EmberKeyData testKey11 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  MEMCOPY(gpdAddr.id.gpdIeeeAddress, testIeee, 8);
  gpdAddr.endpoint = 0x0A;
  gpdAddr.applicationId = 2;
  fc = 3;

  sli_zigbee_af_gp_key_tc_lk_derivation(&gpdAddr,
                                        fc,
                                        mic,
                                        &testKey11,
                                        false);
  emberAfGreenPowerClusterPrint("Encrypted Key :");
  for (int i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    emberAfCorePrint("%x ", testKey11.contents[i]);
  }
  emberAfGreenPowerClusterPrint("\nExpected Key  :2D 23 8F 58 07 1C 07 8A B0 5C 23 5E 4D ED DF 3B ");
  emberAfGreenPowerClusterPrint("\nGenerated MIC :");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC  :DE F5 18 7D");
  // gp test vector check - 5
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[5],
                                                         mic,
                                                         testKey11.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 5]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 2 Application Id 0 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.4.2) MIC of command id = 0x02 (No Payload) SharedKey seclevel = 0b10 Application Id 0");
  EmberKeyData testKey1 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey1);
  //loading new key into core
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  0,//EMBER_AF_GREEN_POWER_GP_SHARED_KEY,
                                                  2,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);

  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :CF 78 7E 72");
  // gp test vector check - 6
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[6],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 6]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 3 Application Id 0 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.4.3) MIC of command id = 0x02 (No Payload) SharedKey seclevel = 0b11 Application Id 0");
  EmberKeyData testKey3 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };

  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey3);
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  0,//EMBER_AF_GREEN_POWER_GP_INDIVIDUAL_KEY,
                                                  3,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);
  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :CA 43 24 DD");
  // gp test vector check - 7
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[7],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 7]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 2 Application Id 0 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.5.2) MIC of command id = 0x02 (No Payload) IndividulaKey seclevel = 0b10 Application Id 0");
  EmberKeyData testKey1552 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey1552);
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  1,//EMBER_AF_GREEN_POWER_GP_INDIVIDUAL_KEY,
                                                  2,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);

  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :AD 69 A9 78");
  // gp test vector check - 8
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[8],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 8]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 3 Application Id 0 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.5.3) MIC of command id = 0x02 (No Payload) IndividualKey seclevel = 0b11 Application Id 0");
  EmberKeyData testKey1553 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };

  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey1553);
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  1,//EMBER_AF_GREEN_POWER_GP_SHARED_KEY,
                                                  3,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);
  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :5F 1A 30 34");
  // gp test vector check - 9
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[9],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 9]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 2 Application Id 2 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.9.2) MIC of command id = 0x02 (No Payload) SharedKey seclevel = 0b10 Application Id 2");
  EmberKeyData testKey2 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  MEMCOPY(gpdAddr.id.gpdIeeeAddress, testIeee, 8);
  gpdAddr.endpoint = 0x0A;
  gpdAddr.applicationId = 2;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey2);
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  0,//EMBER_AF_GREEN_POWER_GP_SHARED_KEY,
                                                  2,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);
  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :C5 A8 3C 5E ");
  // gp test vector check - 10
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[10],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 10]]");
    all_test_vectors_passed = false;
  }

  // Shared Key Security Level 3 Application Id 2 - Incoming
  emberAfGreenPowerClusterPrintln("\nTest Vector (A.1.5.9.3) MIC of command id = 0x02 (No Payload) SharedKey seclevel = 0b11 Application Id 2");
  EmberKeyData testKey4 = { { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF } };
  MEMCOPY(gpdAddr.id.gpdIeeeAddress, testIeee, 8);
  gpdAddr.applicationId = 2;
  fc = 2;

  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)&testKey4);
  //loading new key into core
  sl_zb_sec_man_load_key_context(&context);

  sli_zigbee_af_gp_calculate_incoming_command_mic(&gpdAddr,
                                                  false,
                                                  0,//EMBER_AF_GREEN_POWER_GP_SHARED_KEY,
                                                  3,
                                                  fc,
                                                  0x20,
                                                  NULL,
                                                  false,
                                                  mic);
  emberAfGreenPowerClusterPrint("Generated MIC:");
  for (int i = 0; i < 4; i++) {
    emberAfGreenPowerClusterPrint("%x ", mic[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected MIC :D2 A2 36 1B");
  emberAfGreenPowerClusterPrintln(" ");
  // gp test vector check - 11
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[11],
                                                         mic,
                                                         NULL);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 11]]");
    all_test_vectors_passed = false;
  }

  // A.1.5.7.1 NWK-key derived GPD group key
  uint8_t UNUSED nwkKey[EMBER_ENCRYPTION_KEY_SIZE] = { 0x01, 0x03, 0x05, 0x07, 0x09, 0x0b, 0x0d, 0x0f, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0d };
  // Hash it with 'ZGP'
  uint8_t result[EMBER_ENCRYPTION_KEY_SIZE] = { 0 };

  sl_zb_sec_man_context_t context2;
  sl_zb_sec_man_init_context(&context2);
  //Using internal key type to avoid touching NWK key token - unsure if there's supposed
  //to be a real separate NWK key here that shouldn't be changed
  context2.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  sl_zb_sec_man_import_key(&context2, (sl_zb_sec_man_key_t *)nwkKey);
  sl_zb_sec_man_load_key_context(&context2);
  sl_zb_sec_man_hmac_aes_mmo((uint8_t *)"ZGP",
                             3,
                             result);

  emberAfGreenPowerClusterPrint("Network Derived Group Key:");
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", result[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected Key : BA 88 86 7f c0 09 39 87 eb 88 64 ce be 5f c6 13");
  emberAfGreenPowerClusterPrintln(" ");
  // gp test vector check - 12
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[12],
                                                         NULL,
                                                         result);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 12]]");
    all_test_vectors_passed = false;
  }

  EmberKeyData groupKey = { { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf } };
  (void) emberAfWriteAttribute(EMBER_GP_ENDPOINT,
                               ZCL_GREEN_POWER_CLUSTER_ID,
                               ZCL_GP_SERVER_GP_SHARED_SECURITY_KEY_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               groupKey.contents,
                               ZCL_SECURITY_KEY_ATTRIBUTE_TYPE);

  uint8_t gpsSecurityKeyTypeAtrribute;
  EmberKeyData gpSharedKeyAttribute;
  uint8_t keyType = 1;
  (void) emberAfWriteAttribute(EMBER_GP_ENDPOINT,
                               ZCL_GREEN_POWER_CLUSTER_ID,
                               ZCL_GP_SERVER_GP_SHARED_SECURITY_KEY_TYPE_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               (uint8_t *)(&keyType),
                               ZCL_BITMAP8_ATTRIBUTE_TYPE);

  MEMSET(&gpSharedKeyAttribute, 0, sizeof(EmberKeyData));
  emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(&gpsSecurityKeyTypeAtrribute,
                                                          &gpSharedKeyAttribute,
                                                          &gpdAddr);
  emberAfGreenPowerClusterPrint("Shared Key Type = Network Key(%d):\nRetrived Key : ", gpsSecurityKeyTypeAtrribute);
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", gpSharedKeyAttribute.contents[i]);
  }
  emberAfGreenPowerClusterPrintln(" ");

  keyType = 2;
  (void) emberAfWriteAttribute(EMBER_GP_ENDPOINT,
                               ZCL_GREEN_POWER_CLUSTER_ID,
                               ZCL_GP_SERVER_GP_SHARED_SECURITY_KEY_TYPE_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               (uint8_t *)(&keyType),
                               ZCL_BITMAP8_ATTRIBUTE_TYPE);

  MEMSET(&gpSharedKeyAttribute, 0, sizeof(EmberKeyData));
  emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(&gpsSecurityKeyTypeAtrribute,
                                                          &gpSharedKeyAttribute,
                                                          &gpdAddr);
  emberAfGreenPowerClusterPrint("Shared Key Type = Network Derived Group Key (%d):\nRetrived Key : ", gpsSecurityKeyTypeAtrribute);
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", gpSharedKeyAttribute.contents[i]);
  }
  emberAfGreenPowerClusterPrintln(" ");

  keyType = 3;
  (void) emberAfWriteAttribute(EMBER_GP_ENDPOINT,
                               ZCL_GREEN_POWER_CLUSTER_ID,
                               ZCL_GP_SERVER_GP_SHARED_SECURITY_KEY_TYPE_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               (uint8_t *)(&keyType),
                               ZCL_BITMAP8_ATTRIBUTE_TYPE);
  MEMSET(&gpSharedKeyAttribute, 0, sizeof(EmberKeyData));
  emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(&gpsSecurityKeyTypeAtrribute,
                                                          &gpSharedKeyAttribute,
                                                          &gpdAddr);
  emberAfGreenPowerClusterPrint("Shared Key Type = Group Key(%d):\nRetrived Key : ", gpsSecurityKeyTypeAtrribute);
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", gpSharedKeyAttribute.contents[i]);
  }
  emberAfGreenPowerClusterPrintln(" ");

  keyType = 7;
  (void) emberAfWriteAttribute(EMBER_GP_ENDPOINT,
                               ZCL_GREEN_POWER_CLUSTER_ID,
                               ZCL_GP_SERVER_GP_SHARED_SECURITY_KEY_TYPE_ATTRIBUTE_ID,
                               CLUSTER_MASK_SERVER,
                               (uint8_t *)(&keyType),
                               ZCL_BITMAP8_ATTRIBUTE_TYPE);

  gpdAddr.id.sourceId = 0x87654321;
  gpdAddr.applicationId = 0;
  MEMSET(&gpSharedKeyAttribute, 0, sizeof(EmberKeyData));
  emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(&gpsSecurityKeyTypeAtrribute,
                                                          &gpSharedKeyAttribute,
                                                          &gpdAddr);
  emberAfGreenPowerClusterPrint("A.1.5.7.2 Derived individual GPD key =%d, AppId = %d:\nGenerated Key : ", gpsSecurityKeyTypeAtrribute, gpdAddr.applicationId);
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", gpSharedKeyAttribute.contents[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected Key : 7a 3a 73 43 8d 6e 47 55 28 81 a0 28 ad 59 23 2e");
  emberAfGreenPowerClusterPrintln(" ");
  // gp test vector check - 13
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[13],
                                                         NULL,
                                                         gpSharedKeyAttribute.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 13]]");
    all_test_vectors_passed = false;
  }

  MEMCOPY(gpdAddr.id.gpdIeeeAddress, testIeee, 8);
  gpdAddr.applicationId = 2;
  MEMSET(&gpSharedKeyAttribute, 0, sizeof(EmberKeyData));
  emberAfGreenPowerServerDeriveSharedKeyFromSinkAttribute(&gpsSecurityKeyTypeAtrribute,
                                                          &gpSharedKeyAttribute,
                                                          &gpdAddr);
  emberAfGreenPowerClusterPrint("A.1.5.12.1 Derived individual GPD key=%d, AppId = %d:\nGenerated Key : ", gpsSecurityKeyTypeAtrribute, gpdAddr.applicationId);
  for (int i = 0; i < 16; i++) {
    emberAfGreenPowerClusterPrint("%x ", gpSharedKeyAttribute.contents[i]);
  }
  emberAfGreenPowerClusterPrintln("\nExpected Key : 8a e7 5b 07 5f 7a 13 23 06 08 ff 7e 93 07 97 6d");
  emberAfGreenPowerClusterPrintln(" ");
  // gp test vector check - 14
  single_test_vector_passed = checkGpSecurityTestResults(&gp_test_vector_expects[14],
                                                         NULL,
                                                         gpSharedKeyAttribute.contents);
  if (!single_test_vector_passed) {
    emberAfGreenPowerClusterPrintln("[[FAIL 14]]");
    all_test_vectors_passed = false;
  }

  if (all_test_vectors_passed) {
    status = EMBER_SUCCESS;
  }

  return status;
}
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
