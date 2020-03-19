/*
 * TWI/I2C library for ODROID.
 *
 * Copyright (c) 2015 Arduino LLC. All rights reserved.
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

#ifndef _WIRE_H_
#define _WIRE_H_
#pragma once

#include <Arduino.h>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <string>

constexpr int MAX_I2C_BUFFER_SIZE = 1 << 7;

class TwoWire: public HardwareI2C {
public:
    TwoWire(const std::string &device);
    TwoWire(uint8_t deviceNum);
    ~TwoWire();

    void begin(uint8_t slaveAddress) override;
    void begin(void) override { begin(0xFF); }
    void end(void) override;

    void setClock(uint32_t clock) override;

    void    beginTransmission(uint8_t slaveAddress) override;
    uint8_t endTransmission(bool stopBit) override;
    uint8_t endTransmission(void) override { return endTransmission(true); }

    uint8_t
            requestFrom(uint8_t slaveAddress, size_t size, bool stopBit) override;
    uint8_t requestFrom(uint8_t slaveAddress, size_t size) override {
        return requestFrom(slaveAddress, size, true);
    }

    void onReceive(void (*)(int)) override;
    void onRequest(void (*)(void)) override;

    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t *data, size_t size) override;

    virtual int  available(void) override;
    virtual int  read(void) override;
    virtual int  peek(void) override;
    virtual void flush(void) override;

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

private:
    std::string mDevice;
    int         mFd;
    uint8_t     mSlaveAddress;

    uint8_t mRxBuffer[MAX_I2C_BUFFER_SIZE];
    size_t  mRxBufferSize;
    size_t  mRxBufferIndex;

    uint8_t mTxBuffer[MAX_I2C_BUFFER_SIZE];
    size_t  mTxBufferIndex;
};

extern TwoWire &Wire;
extern TwoWire  Wire1;
extern TwoWire  Wire2;

#endif    // _WIRE_H_