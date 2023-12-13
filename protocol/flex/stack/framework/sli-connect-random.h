/***************************************************************************//**
 * @file
 * @brief See @ref random for detailed documentation.
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

#ifndef __SLI_CONNECT_RANDOM_H__
#define __SLI_CONNECT_RANDOM_H__

/** @brief Seeds the ::sli_connect_get_random() pseudorandom number
 * generator.
 *
 * Called by the stack during initialization with a seed from the radio.
 *
 * @param seed  A seed for the pseudorandom number generator.
 */
void sli_connect_seed_random(uint32_t seed);

/** @brief Runs a standard LFSR to generate pseudorandom numbers.
 *
 * Called by the MAC in the stack to choose random backoff slots.
 *
 * Complicated implementations may improve the MAC's
 * ability to avoid collisions in large networks, but it is \b critical to
 * implement this function to return quickly.
 */
uint16_t sli_connect_get_random(void);

#endif //__SLI_CONNECT_RANDOM_H__
