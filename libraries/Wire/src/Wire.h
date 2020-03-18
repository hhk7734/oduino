/*
  Wire.cpp - I2C library for odroid

  Copyright (c) 2019 Hyeonki Hong. All rights reserved.
  This file is part of the odroid core for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRE_H_
#define _WIRE_H_
#pragma once

#include <Arduino.h>
#include <linux/i2c-dev.h>

const int I2C_BUFFER_SIZE = I2C_RDWR_IOCTL_MAX_MSGS;

class TwoWire: public HardwareI2C {
public:
    TwoWire(uint8_t _i2c_num);

    void begin(uint8_t slave_address);
    void begin(void) { begin(0xFF); }
    void end(void);

    void setClock(uint32_t freq);

    void beginTransmission(uint8_t slave_address);
    void beginTransmission(int slave_address) {
        beginTransmission((uint8_t)slave_address);
    }

    uint8_t endTransmission(bool stop);
    uint8_t endTransmission(void) { return endTransmission(true); }

    uint8_t requestFrom(uint8_t slave_address, size_t len, bool stop);
    uint8_t requestFrom(uint8_t slave_address, size_t len);
    uint8_t requestFrom(int slave_address, int len);
    uint8_t requestFrom(int slave_address, int len, int stop);

    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *data, size_t len);
    virtual int    available(void);
    virtual int    read(void);
    virtual int    peek(void);
    virtual void   flush(void);
    void           onReceive(void (*)(int));
    void           onRequest(void (*)(void));

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

private:
    int     fd;
    uint8_t i2c_num;
    uint8_t device_address;

    uint8_t rx_buff[I2C_BUFFER_SIZE];
    uint8_t rx_buff_len;
    uint8_t rx_buff_index;

    uint8_t tx_buff[I2C_BUFFER_SIZE];
    uint8_t tx_buff_index;
};

extern TwoWire &Wire;
extern TwoWire  Wire1;
extern TwoWire  Wire2;

#endif    // _WIRE_H_