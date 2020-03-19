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

#ifndef _SPI_H_
#define _SPI_H_
#pragma once

#include <Arduino.h>
#include <string>

enum SpiMode { SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3 };

class SPISettings {
public:
    SPISettings();
    SPISettings(uint32_t clock, BitOrder bitOrder, SpiMode spiMode) {}
    friend class SPIClass;
};

class SPIClass {
public:
    SPIClass(const std::string &device);
    SPIClass(uint16_t bus, uint16_t chipSelect);
    SPIClass(uint16_t chipSelect);
    ~SPIClass();

    void begin(uint32_t clock, BitOrder bitOrder, SpiMode spiMode);
    void begin(void) { begin(1'000'000, MSBFIRST, SPI_MODE0); }
    void end(void);

    [[deprecated(
        "Use setClock() in ODROID. With setClockDivider(), 1MHz is set.")]] void
         setClockDivider(uint8_t clockDiv);
    void setClock(uint32_t clock);
    void setBitOrder(BitOrder bitOrder);
    void setDataMode(SpiMode spiMode);

    void beginTransaction(SPISettings settings);
    void endTransaction(void);

    uint8_t  transfer(uint8_t data);
    size_t   transfer(uint8_t *buf, size_t count);
    uint16_t transfer16(uint16_t data);

protected:
    std::string mDevice;
    int         mFd;
    uint8_t     mOptions;
};

extern SPIClass  SPI0;
extern SPIClass &SPI;

#endif    // _SPI_H_