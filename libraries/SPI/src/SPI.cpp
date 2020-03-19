/*
 * SPI Master library for ODROID.
 *
 * Copyright (c) 2015 Arduino LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Modified 2019-2020 by Hyeonki Hong (ODROID support)
 */

#include "SPI.h"

#include <cerrno>      // errno
#include <cstring>     // std::std::strerror(), std::memset()
#include <fcntl.h>     // open()
#include <iostream>    // std::cerr, std::endl
#include <linux/spi/spidev.h>
#include <stdexcept>      // std::runtime_error()
#include <sys/ioctl.h>    // ioctl()
#include <unistd.h>       // close()

SPIClass  SPI0("/dev/spidev0.0");
SPIClass &SPI = SPI0;

SPIClass::SPIClass(const std::string &device)
    : mFd(-1)
    , mDevice(device)
    , mOptions(SPI_MODE0) {}

SPIClass::SPIClass(uint16_t bus, uint16_t chipSelect)
    : mFd(-1)
    , mOptions(SPI_MODE0) {
    mDevice.reserve(20);
    mDevice += "/dev/spidev";
    mDevice += std::to_string(bus);
    mDevice += ".";
    mDevice += std::to_string(chipSelect);
}

SPIClass::SPIClass(uint16_t chipSelect)
    : mFd(-1)
    , mOptions(SPI_MODE0) {
    mDevice.reserve(20);
    mDevice += "/dev/spidev0.";
    mDevice += std::to_string(chipSelect);
}

SPIClass::~SPIClass() { end(); }

void SPIClass::begin(uint32_t clock, BitOrder bitOrder, SpiMode spiMode) {
    if(mFd > 0) { end(); }

    mFd = open(mDevice.c_str(), O_RDWR);
    if(mFd < 0) {
        std::cerr << "Failed to open " << mDevice << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }

    setClock(clock);
    setBitOrder(bitOrder);
    setDataMode(spiMode);

    uint8_t spi_BPW = 0;    // means 8 bits
    if(ioctl(mFd, SPI_IOC_WR_BITS_PER_WORD, &spi_BPW) < 0) {
        std::cerr << "Failed to set SPI bits per word." << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }
}

void SPIClass::end(void) {
    close(mFd);
    mFd = -1;
}

void SPIClass::setClockDivider(uint8_t clockDiv) { setClock(1'000'000); }

void SPIClass::setClock(uint32_t clock) {
    if(ioctl(mFd, SPI_IOC_WR_MAX_SPEED_HZ, &clock) < 0) {
        std::cerr << "Failed to set SPI clock speed." << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }
}

void SPIClass::setBitOrder(BitOrder bitOrder) {
    mOptions &= ~SPI_LSB_FIRST;
    if(bitOrder == LSBFIRST) { mOptions |= SPI_LSB_FIRST; }

    if(ioctl(mFd, SPI_IOC_WR_MODE, &mOptions) < 0) {
        std::cerr << "Failed to set SPI bit odrder." << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }
}

void SPIClass::setDataMode(SpiMode spiMode) {
    mOptions &= ~0x03;
    mOptions |= spiMode;
    if(ioctl(mFd, SPI_IOC_WR_MODE, &mOptions) < 0) {
        std::cerr << "Failed to set SPI mode." << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }
}

void SPIClass::beginTransaction(SPISettings settings) {}

void SPIClass::endTransaction(void) {}

uint8_t SPIClass::transfer(uint8_t data) {
    transfer(&data, 1);
    return data;
}

size_t SPIClass::transfer(uint8_t *buf, size_t count) {
    struct spi_ioc_transfer spi;
    std::memset(&spi, 0, sizeof(spi));

    spi.tx_buf = (unsigned long)buf;
    spi.rx_buf = (unsigned long)buf;
    spi.len    = count;

    return ioctl(mFd, SPI_IOC_MESSAGE(1), &spi);
}

uint16_t SPIClass::transfer16(uint16_t data) {}