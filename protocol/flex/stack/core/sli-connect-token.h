/***************************************************************************//**
 * @file
 * @brief
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
#ifndef __SLI_CONNECT_TOKEN_H__
#define __SLI_CONNECT_TOKEN_H__

#ifndef EMBER_TEST
#include "sl_token_manufacturing_api.h"
#else
//no special handling for the manufacturing tokens
#define TOKEN_MFG TOKEN_DEF
#endif

//-- Build structure defines

/**
 * @description Simple declarations of all of the token types so that they can
 * be referenced from anywhere in the code base.
 */
#define DEFINETYPES
  #include "stack/config/token-stack.h"
#undef DEFINETYPES

//-- Build parameter links
#define DEFINETOKENS

/**
 * @description Macro for translating token definitions into size variables.
 * This provides a convenience for abstracting the 'sizeof(type)' anywhere.
 *
 * @param name: The name of the token.
 *
 * @param type: The token type.  The types are found in token-stack.h.
 */
#define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  TOKEN_##name##_SIZE = sizeof(type),
enum {
    #include "stack/config/token-stack.h"
};

#undef TOKEN_DEF

// #define DEFINEADDRESSES
// *
//  * @description Macro for creating a 'region' element in the enum below.  This
//  * creates an element in the enum that provides a starting point (address) for
//  * subsequent tokens to align against.  ( See hal/micro/avr-atmega/token.c for
//  * the instances of TOKEN_NEXT_ADDRESS() );
//  *
//  * @param region: The name to give to the element in the address enum..
//  *
//  * @param address: The address in EEPROM where the region begins.
// //
// #define TOKEN_NEXT_ADDRESS(region, address)
//   TOKEN_##region##_NEXT_ADDRESS = ((address) - 1),

/**
 * @description Macro for creating ADDRESS and END elements for each token in
 * the enum below.  The ADDRESS element is linked to from the the normal
 * TOKEN_##name macro and provides the value passed into the internal token
 * system calls.  The END element is a placeholder providing the starting
 * point for the ADDRESS of the next dynamically positioned token.
 *
 * @param name: The name of the token.
 *
 * @param arraysize: The number of elements in an indexed token (arraysize=1
 * for scalar tokens).
 */
#define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  TOKEN_##name##_ADDRESS,                                            \
  TOKEN_##name##_END = TOKEN_##name##_ADDRESS                        \
                       + (TOKEN_##name##_SIZE * arraysize) - 1,

/**
 * @description The enum that operates on the two macros above.  Also provides
 * an indentifier so the address of the top of the token system can be known.
 */
enum {
  #include "stack/config/token-stack.h"
  TOKEN_MAXIMUM_SIZE
};

#undef TOKEN_DEF
#undef TOKEN_NEXT_ADDRESS
#undef DEFINEADDRESSES

/**
 * @description Enum for translating token defs into a number.  This number is
 * used as an index into the Address Lookup table.  The Address Lookup table
 * is defined in hal/micro/generic/token-ram.c.  The reason for the lookup
 * table is so mupltiple stack files can be built once using this header, then
 * each image being created can rebuild token-ram.c with it's own set of
 * configuration parameters and still map the tokens properly.
 *
 * The special entry TOKEN_COUNT is always at the top of the enum, allowing
 * the token system to know how many tokens there are.
 *
 * @param name: The name of the token.
 */
#define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  TOKEN_##name,
enum {
    #include "stack/config/token-stack.h"
  TOKEN_COUNT
};

#undef TOKEN_DEF

/**
 * @description Macro for typedef'ing the CamelCase token type found in
 * token-stack.h to a capitalized TOKEN style name that ends in _TYPE.
 * This macro allows other macros below to use 'token##_TYPE' to declare
 * a local copy of that token.
 *
 * @param name: The name of the token.
 *
 * @param type: The token type.  The types are found in token-stack.h.
 */
#define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  typedef type TOKEN_##name##_TYPE;
  #include "stack/config/token-stack.h"
#undef TOKEN_DEF
#undef DEFINETOKENS

#undef TOKEN_MFG

#ifdef EMBER_TEST
#include "sli-connect-token-manager-stubs.h"
#else
#include "sl_token_manager.h"
#endif

#endif // __SLI_CONNECT_TOKEN_H__
