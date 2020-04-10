/*
 * MIT License
 *
 * Copyright (c) 2020 Hyeonki Hong <hhk7734@gmail.com>
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

#include "wiringPiWrapper.h"

#include <wiringPi.h>

void wiringpi_setup() { wiringPiSetupPhys(); }

void wiringpi_pinMode(int pinNumber, int _pinMode) {
    pinMode(pinNumber, _pinMode);
}

void wiringpi_digitalWrite(int pinNumber, int status) {
    digitalWrite(pinNumber, status);
}

int wiringpi_digitalRead(int pinNumber) { return digitalRead(pinNumber); }

int wiringpi_analogRead(int pinNumber) { return analogRead(pinNumber); }

void wiringpi_attachInterrupt(int interruptNumber,
                              void (*callback)(void),
                              int mode) {
    uint8_t wiringPi_interrupt_mode;
    switch(mode) {
    case 2: wiringPi_interrupt_mode = INT_EDGE_BOTH; break;
    case 3: wiringPi_interrupt_mode = INT_EDGE_FALLING; break;
    case 4: wiringPi_interrupt_mode = INT_EDGE_RISING; break;
    default: break;
    }
    wiringPiISR(interruptNumber, wiringPi_interrupt_mode, callback);
}

void wiringpi_detachInterrupt(int interruptNumber) {
    wiringPiISRCancel(interruptNumber);
}