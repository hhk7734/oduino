#include "Arduino.h"

void attachInterrupt(pin_size_t  interruptNumber,
                     voidFuncPtr callback,
                     PinStatus   mode) {
    uint8_t wiringPi_interrupt_mode;
    switch(mode) {
    case CHANGE: wiringPi_interrupt_mode = INT_EDGE_BOTH; break;
    case FALLING: wiringPi_interrupt_mode = INT_EDGE_FALLING; break;
    case RISING: wiringPi_interrupt_mode = INT_EDGE_RISING; break;
    default: break;
    }
    wiringPiISR(interruptNumber, wiringPi_interrupt_mode, callback);
}

void detachInterrupt(pin_size_t interruptNumber) {
    wiringPiISRCancel(interruptNumber);
}
