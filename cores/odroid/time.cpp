/*
 * MIT License
 * Copyright (c) 2019-2020 Hyeonki Hong <hhk7734@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Arduino.h"

#include <atomic>
#include <sys/time.h>
#include <time.h>

std::atomic<uint64_t> start_millis;
std::atomic<uint64_t> start_micros;

void init_time(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    start_millis = static_cast<uint64_t>(ts.tv_sec) * 1000ULL
                   + static_cast<uint64_t>(ts.tv_nsec / 1000000L);
    start_micros = static_cast<uint64_t>(ts.tv_sec) * 1000000ULL
                   + static_cast<uint64_t>(ts.tv_nsec / 1000L);
}

static void delay_us_2(uint32_t us) {
    struct timeval t_start;
    struct timeval t_interval;
    struct timeval t_end;

    gettimeofday(&t_start, NULL);
    t_interval.tv_sec  = 0;
    t_interval.tv_usec = us;
    timeradd(&t_start, &t_interval, &t_end);

    while(timercmp(&t_start, &t_end, <)) { gettimeofday(&t_start, NULL); }
}

void delayMicroseconds(unsigned int us) {
    if(us > 200) {
        // The minimum delay made by nanosleep seems to be about 100us.
        struct timespec ts_us;
        struct timespec temp;

        ts_us.tv_sec  = static_cast<time_t>(us / 1000000UL);
        ts_us.tv_nsec = static_cast<long>(us % 1000000UL) * 1000L;

        nanosleep(&ts_us, &temp);
    } else {
        delay_us_2(us);
    }
}

void delay(unsigned long ms) {
    struct timespec ts_ms;
    struct timespec temp;

    ts_ms.tv_sec  = static_cast<time_t>(ms / 1000UL);
    ts_ms.tv_nsec = static_cast<long>(ms % 1000UL) * 1000000L;

    nanosleep(&ts_ms, &temp);
}

unsigned long micros(void) {
    uint64_t        current_micros;
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    current_micros = static_cast<uint64_t>(ts.tv_sec) * 1000000ULL
                     + static_cast<uint64_t>(ts.tv_nsec / 1000L);

    return current_micros - start_micros;
}

unsigned long millis(void) {
    uint64_t        current_millis;
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    current_millis = static_cast<uint64_t>(ts.tv_sec) * 1000ULL
                     + static_cast<uint64_t>(ts.tv_nsec / 1000000L);

    return current_millis - start_millis;
}