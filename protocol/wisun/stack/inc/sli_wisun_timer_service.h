/*
 * Copyright (c) 2023 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * # Features
 *   - Provides multiple virtual timers
 *   - Uses only one physical timer provided by RAIL
 *   - Microsecond resolution
 *   - No overflow thanks to 64 bits timers
 *   - Can be used by multiple threads
 *
 * # Architecture
 *
 * The timer service needs a context for each thread in which user callbacks
 * will run.
 * At any time, the physical timer phy_timer is configured to fire on the
 * soonest expiration date of all the virtual timers in the system.
 *
 * stage 1: IRQ
 * When the physical timer expires, main_phy_timer_callback() is ran in IRQ to
 * signal this event to the appropriate thread via a context specific callback.
 * This ensures that we spend as few time as possible in IRQ, and that the user
 * callback will run later in the appropriate thread.
 *
 * stage 2: Thread
 * When a thread receives its timer event, it must call
 * sli_wisun_timer_context_dispatcher() which will run the callback associated
 * to the expired user timer.
 */

#ifndef TIMER_SERVICE_H
#define TIMER_SERVICE_H
#include <stdint.h>
#include <stdbool.h>
#include <cmsis_os2.h>
#include "ns_list.h"
#include "sl_wisun_common.h"

typedef struct sli_wisun_timer sli_wisun_timer_t;
typedef struct sli_wisun_timer_context sli_wisun_timer_context_t;

// Parameters for each user timer provided by the service
struct sli_wisun_timer {
    sli_wisun_timer_context_t *context;    // Context from which the callback will run
    void (*callback)(sli_wisun_timer_t *); // Function to run at expiration
    uint64_t period_us;                    // Period in microseconds (0 if not periodic)
    uint64_t expire_time_us;               // Next expiration absolute time in microseconds
    const char *name;                      // Name used in debug traces (can be NULL)
    ns_list_link_t link;                   // Reserved for ns_list
    uint32_t is_valid;                     // Valid value is set when the timer is inititialized
    bool persistent;                       // True to keep timer running while the interface is down
};

/**
 * Parameters for each thread which will run callbacks i.e. each thread calling
 * sli_wisun_timer_context_dispatcher().
 * This structure should be stored in the main data structure of the thread to
 * allow retrieval in timer callbacks via container_of().
 */
struct sli_wisun_timer_context {
    NS_LIST_HEAD(sli_wisun_timer_t, link) timer_list;  // List of user timers
    void (*irq_callback)(sli_wisun_timer_context_t *); // Callback ran in IRQ to notify the thread
    const char *name;                                  // Name used in debug traces (can be NULL)
    osMutexId_t mutex;                                 // Protect access to timer_list (r/w)
    ns_list_link_t link;                               // Reserved for ns_list
#ifdef TIMER_SERVICE_DEBUG
    struct {
        uint64_t signal_us;                            // Date of the pending signal (0 means none)
        uint32_t max_signal_delay_us;
        uint32_t max_cb_duration_us;
        uint64_t max_timer_delay_us;
    } stats;                                           // Data used for monitoring and debug
#endif
};

// -----------------------------------------------------------------------------

/**
 * Lower Layer: system setup
 *
 * For each thread that will run user callbacks, a context must be created with
 * sli_wisun_timer_context_setup(), making sure that irq_callback only signals
 * the expiration event to the thread in order to be as fast as possible since
 * it will run in IRQ context.
 * When a thread receives the expiration event, it must call
 * sli_wisun_timer_context_dispatcher() that will run the right callback for the
 * expired timer(s).
 * sli_wisun_timer_context_setup() must not be called after the first timer of
 * the system is started.
 */
void sli_wisun_timer_context_setup(sli_wisun_timer_context_t *ctxt,
                                   void (*irq_callback)(sli_wisun_timer_context_t *),
                                   const char *name);
void sli_wisun_timer_context_dispatcher(sli_wisun_timer_context_t *ctxt);

// -----------------------------------------------------------------------------

/**
 * Upper Layer: user timers
 *
 * A timer must be initialized with sli_wisun_timer_init() before use. Its
 * purpose is to associate a callback on expiration and to register the timer in
 * the thread’s context. The callback can use all timer functions.
 *
 * Multiple functions are available to start a timer with different behaviors:
 *   "absolute": one-shot, time from system start
 *   "relative": one-shot, time from time of call to this function
 *   "periodic": periodic, time between each expiration of the timer (first one
 *               being a period from time of call to this function)
 * Multiple time units are supported: microseconds, milliseconds and seconds;
 * respectively provided by functions _us, _ms and _s.
 * The function sli_wisun_timer_start_us() provides the most control over timer
 * start.
 * A running timer can be restarted with a "start" function, no need to call
 * sli_wisun_timer_stop() first.
 * User must ensure that the system is not running more than
 * (2^32)*3/4 microseconds (~53 minutes) without a timer expiration.
 *
 * A timer can be stopped with sli_wisun_timer_stop().
 *
 * A timer can be used by polling with sli_wisun_timer_get_remaining_us(), in
 * this case sli_wisun_timer_init() can be called with a NULL callback.
 *
 * A special state for timers is "infinite" which means "never expire", such a
 * timer is started with sli_wisun_timer_start_infinite(). It is possible to
 * check if a timer is infinite with sli_wisun_timer_is_infinite() and the
 * return of sli_wisun_timer_get_remaining_xx() functions is guaranteed to be
 * greater than the one for a non infinite timer.
 *
 * Timers are automatically stopped when the stack is brought down to avoid
 * callbacks to deleted contexts. Timers can be set to persist using the API
 * sli_wisun_timer_set_persistent().
 */
void sli_wisun_timer_init(sli_wisun_timer_t *timer,
                          sli_wisun_timer_context_t *ctxt,
                          void (*callback)(sli_wisun_timer_t *),
                          const char *name);

void sli_wisun_timer_set_persistent(sli_wisun_timer_t *timer, bool persistent);

void sli_wisun_timer_start_us(sli_wisun_timer_t *timer, uint64_t period_us, uint64_t next_time_us);

void sli_wisun_timer_start_absolute_us(sli_wisun_timer_t *timer, uint64_t time_us);
void sli_wisun_timer_start_relative_us(sli_wisun_timer_t *timer, uint64_t delay_us);
void sli_wisun_timer_start_periodic_us(sli_wisun_timer_t *timer, uint64_t period_us);

void sli_wisun_timer_start_absolute_ms(sli_wisun_timer_t *timer, uint64_t time_ms);
void sli_wisun_timer_start_relative_ms(sli_wisun_timer_t *timer, uint64_t delay_ms);
void sli_wisun_timer_start_periodic_ms(sli_wisun_timer_t *timer, uint64_t period_ms);

void sli_wisun_timer_start_absolute_s(sli_wisun_timer_t *timer, uint64_t time_s);
void sli_wisun_timer_start_relative_s(sli_wisun_timer_t *timer, uint64_t delay_s);
void sli_wisun_timer_start_periodic_s(sli_wisun_timer_t *timer, uint64_t period_s);

void sli_wisun_timer_start_infinite(sli_wisun_timer_t *timer);

void sli_wisun_timer_stop(sli_wisun_timer_t *timer);

/**
 * Utilities
 *
 * sli_wisun_timer_get_current_time_us() returns the time in microseconds from
 * system start.
 * sli_wisun_timer_get_current_time32_us() returns the above time with a reduced
 * dynamic range. This value wraps.
 * sli_wisun_timer_is_running() and sli_wisun_timer_get_remaining_us() can be
 * used to query the status of a timer, the functions with _ms and _s suffixes
 * provide the result respectively in milliseconds and seconds rounded to the
 * nearest integer.
 * sli_wisun_timer_32_to_64_us() returns a 64bits time from a 32bits one, the
 * result is only valid for values closer than (2^32)/2 to the current time.
 */
uint32_t sli_wisun_timer_get_current_time32_us(void);
uint64_t sli_wisun_timer_get_current_time_us(void);
uint64_t sli_wisun_timer_get_current_time_ms(void);
uint64_t sli_wisun_timer_get_current_time_s(void);

bool sli_wisun_timer_is_running(const sli_wisun_timer_t *timer);

uint64_t sli_wisun_timer_get_remaining_us(const sli_wisun_timer_t *timer);
uint64_t sli_wisun_timer_get_remaining_ms(const sli_wisun_timer_t *timer);
uint64_t sli_wisun_timer_get_remaining_s(const sli_wisun_timer_t *timer);

bool sli_wisun_timer_is_infinite(const sli_wisun_timer_t *timer);

uint64_t sli_wisun_timer_32_to_64_us(uint32_t time_us);

void sli_wisun_timer_garbage_collection(void);

#endif
