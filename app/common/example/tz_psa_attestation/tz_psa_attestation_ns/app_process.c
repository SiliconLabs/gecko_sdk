/***************************************************************************//**
 * @file app_process.c
 * @brief Top level application functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "app_process.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Retrieve input character from VCOM port.
 ******************************************************************************/
static void app_iostream_usart_process_action(void);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Space press status
static bool space_press;

/// Enter press status
static bool enter_press;

/// State machine state variable
static state_t app_state = PSA_CRYPTO_INIT;

/// String for example
static uint8_t example_string[] = "PSA Attestation Example";

/// Nonce size for the PSA Attestation Token
static int8_t selected_nonce;

static const uint32_t iat_token_nonce_sizes[] = {
  PSA_INITIAL_ATTEST_CHALLENGE_SIZE_32,
  PSA_INITIAL_ATTEST_CHALLENGE_SIZE_48,
  PSA_INITIAL_ATTEST_CHALLENGE_SIZE_64
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Application state machine, called infinitely.
 ******************************************************************************/
void app_process_action(void)
{
  // Retrieve input character from VCOM port
  app_iostream_usart_process_action();

  switch (app_state) {
    case PSA_CRYPTO_INIT:
      app_state = PSA_CRYPTO_IDLE;
      printf("\n%s - Core running at %" PRIu32 " kHz.\n", example_string,
             CMU_ClockFreqGet(cmuClock_CORE) / 1000);
      printf("  . PSA Crypto initialization... ");
      if (init_psa_crypto() == PSA_SUCCESS) {
        printf("\n  . Current nonce size of PSA Attestation Token is "
               "%lu bytes.\n", iat_token_nonce_sizes[selected_nonce]);
        printf("  + Press SPACE to cycle through the options (%lu or %lu or "
               "%lu), press ENTER to make a selection.\n",
               iat_token_nonce_sizes[0], iat_token_nonce_sizes[1],
               iat_token_nonce_sizes[2]);
        app_state = SELECT_NONCE_SIZE;
      }
      break;

    case SELECT_NONCE_SIZE:
      if (space_press) {
        space_press = false;
        selected_nonce = (selected_nonce + 1) % 3;
        printf("  + Current nonce size of PSA Attestation Token is "
               "%lu bytes.\n", iat_token_nonce_sizes[selected_nonce]);
      }

      if (enter_press) {
        app_state = PSA_CRYPTO_EXIT;
        enter_press = false;
        printf("  + Generating %lu bytes nonce... ",
               iat_token_nonce_sizes[selected_nonce]);
        if (generate_random_number(iat_token_nonce_sizes[selected_nonce])
            != PSA_SUCCESS) {
          break;
        }
        printf("  + The nonce (%lu bytes):",
               iat_token_nonce_sizes[selected_nonce]);
        print_nonce(iat_token_nonce_sizes[selected_nonce]);
        app_state = GET_IAT_TOKEN;
      }
      break;

    case GET_IAT_TOKEN:
      app_state = PSA_CRYPTO_EXIT;
      printf("\n  . Getting the size of the token with %lu bytes nonce... ",
             iat_token_nonce_sizes[selected_nonce]);
      if (get_attested_token_size(iat_token_nonce_sizes[selected_nonce])
          != PSA_SUCCESS) {
        break;
      }
      printf("  + The size of the token is %zu bytes\n", get_token_size());

      printf("\n  . Getting the token with %lu bytes nonce... ",
             iat_token_nonce_sizes[selected_nonce]);
      if (get_attested_token(iat_token_nonce_sizes[selected_nonce])
          != PSA_SUCCESS) {
        break;
      }
      printf("  + The size of the token is %zu bytes\n", get_token_size());

      printf("\n  . Getting the Public Attestation Key... ");
      if (get_public_attestation_key() != PSA_SUCCESS) {
        break;
      }
      printf("  + The Public Attestation Key (64 bytes):\n");
      print_pub_key();

      if (print_attestation_token() != PSA_SUCCESS) {
        break;
      }

      printf("\n  . Current nonce size of PSA Attestation Token is "
             "%lu bytes.\n", iat_token_nonce_sizes[selected_nonce]);
      printf("  + Press SPACE to cycle through the options (%lu or %lu or "
             "%lu), press ENTER to make a selection.\n",
             iat_token_nonce_sizes[0], iat_token_nonce_sizes[1],
             iat_token_nonce_sizes[2]);
      app_state = SELECT_NONCE_SIZE;
      break;

    case PSA_CRYPTO_EXIT:
      printf("\n  . PSA Crypto deinitialization\n");
      mbedtls_psa_crypto_free();
      app_state = PSA_CRYPTO_IDLE;
      break;

    case PSA_CRYPTO_IDLE:
    default:
      break;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Retrieve input character from VCOM port.
 ******************************************************************************/
static void app_iostream_usart_process_action(void)
{
  int8_t c;

  c = getchar();
  if (c > 0) {
    if (c == ' ') {
      space_press = true;
    }
    if (c == '\r') {
      enter_press = true;
    }
  }
}
