#include "Arduino.h"
#include "wiringPiWrapper.h"

void attachInterrupt(pin_size_t  interruptNumber,
                     voidFuncPtr callback,
                     PinStatus   mode) {
    wiringpi_attachInterrupt(interruptNumber, callback, mode);
}

void detachInterrupt(pin_size_t interruptNumber) {
    wiringpi_detachInterrupt(interruptNumber);
}
