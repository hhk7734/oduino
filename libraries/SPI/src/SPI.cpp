#include "SPI.h"

#include <errno.h>
#include <stdio.h>     // sprintf(), fprintf()
#include <stdlib.h>    // exit()
#include <unistd.h>
#include <wiringPiSPI.h>

SPIClass  SPI0(0);
SPIClass &SPI = SPI0;

SPIClass::SPIClass(uint8_t _channel)
    : channel(_channel)
    , fd(-1) {}

void SPIClass::begin(const char *device, uint32_t speed, uint8_t mode) {
    if(fd > 0) { end(); }

    fd = wiringPiSPISetupInterface(device, channel, speed, mode);
    if(fd < 0) {
        fprintf(stderr, "Unable to open %s : %s\n", device, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void SPIClass::begin(uint32_t speed, uint8_t mode) {
    char device[20];
    sprintf(device, "/dev/spidevX.%d", channel);

    if(fd > 0) { end(); }

    fd = wiringPiSPISetupMode(channel, speed, mode);
    if(fd < 0) {
        fprintf(stderr, "Unable to open %s : %s\n", device, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void SPIClass::end(void) {
    close(fd);
    fd = -1;
}

void SPIClass::setBitOrder(uint8_t bitOrder) {}

void SPIClass::setDataMode(uint8_t dataMode) {}

void SPIClass::setClockDivider(uint8_t clockDiv) {}

void SPIClass::setFrequency(uint32_t freq) {}

void SPIClass::beginTransaction(SPISettings settings) {}

void SPIClass::endTransaction(void) {}

uint8_t SPIClass::transfer(uint8_t data) {
    wiringPiSPIDataRW(channel, &data, 1);
    return data;
}

uint8_t SPIClass::transfer(uint8_t *buf, size_t count) {
    return wiringPiSPIDataRW(channel, buf, count);
}

uint16_t SPIClass::transfer16(uint16_t data) {}