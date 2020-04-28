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

#include "Wire.h"

#include <algorithm>    // std::copy()
#include <cerrno>       // errno
#include <cstring>      // std::std::strerror()
#include <fcntl.h>      // open()
#include <iostream>     // std::cerr, std::endl
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdexcept>      // std::runtime_error()
#include <sys/ioctl.h>    // ioctl()
#include <unistd.h>       // close()

TwoWire  Wire0("/dev/i2c-0");
TwoWire  Wire1("/dev/i2c-1");
TwoWire &Wire = Wire0;

TwoWire::TwoWire(const std::string &device)
    : mDevice(device)
    , mFd(-1) {}

TwoWire::TwoWire(uint8_t deviceNum)
    : mFd(-1) {
    mDevice.reserve(15);
    mDevice += "/dev/i2c-";
    mDevice += std::to_string(deviceNum);
}

TwoWire::~TwoWire() { end(); }

void TwoWire::begin(uint8_t slaveAddress) {
    if(mFd > 0) { end(); }

    mFd = open(mDevice.c_str(), O_RDWR);
    if(mFd < 0) {
        std::cerr << "Failed to open " << mDevice << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }

    mSlaveAddress = slaveAddress;
}

void TwoWire::end(void) {
    close(mFd);
    mFd = -1;
}

void TwoWire::setClock(uint32_t clock) {}

void TwoWire::beginTransmission(uint8_t slaveAddress) {
    mSlaveAddress  = slaveAddress;
    mTxBufferIndex = 0;
}

uint8_t TwoWire::endTransmission(bool stopBit) {
    if(stopBit) {
        if(mTxBufferIndex > 0) {
            struct i2c_rdwr_ioctl_data i2c;
            struct i2c_msg             msgs;
            msgs.addr  = mSlaveAddress;
            msgs.flags = 0;
            msgs.len   = mTxBufferIndex;
            msgs.buf   = mTxBuffer;

            i2c.msgs  = &msgs;
            i2c.nmsgs = 1;

            return ioctl(mFd, I2C_RDWR, &i2c);
        } else {
            return 0;
        }
    }

    return 0;
}

uint8_t TwoWire::requestFrom(uint8_t slaveAddress, size_t size, bool stop) {
    mSlaveAddress  = slaveAddress;
    mRxBufferIndex = 0;
    mRxBufferSize  = size;

    struct i2c_rdwr_ioctl_data i2c;
    struct i2c_msg             msgs[2];

    if(mTxBufferIndex > 0) {
        msgs[0].addr  = mSlaveAddress;
        msgs[0].flags = 0;    /// write
        msgs[0].len   = mTxBufferIndex;
        msgs[0].buf   = mTxBuffer;

        msgs[1].addr  = mSlaveAddress;
        msgs[1].flags = I2C_M_RD;    /// read
        msgs[1].len   = mRxBufferSize;
        msgs[1].buf   = mRxBuffer;

        i2c.msgs  = msgs;
        i2c.nmsgs = 2;
    } else {
        msgs[0].addr  = mSlaveAddress;
        msgs[0].flags = I2C_M_RD;    /// read
        msgs[0].len   = mRxBufferSize;
        msgs[0].buf   = mRxBuffer;

        i2c.msgs  = msgs;
        i2c.nmsgs = 1;
    }

    return ioctl(mFd, I2C_RDWR, &i2c);
}

void TwoWire::onReceive(void (*)(int)) {}

void TwoWire::onRequest(void (*)(void)) {}

size_t TwoWire::write(uint8_t data) {
    if(mTxBufferIndex < MAX_I2C_BUFFER_SIZE) {
        mTxBuffer[mTxBufferIndex++] = data;
        return 1;
    } else {
        return 0;
    }
}

size_t TwoWire::write(const uint8_t *data, size_t size) {
    if(mTxBufferIndex + size <= MAX_I2C_BUFFER_SIZE) {
        std::copy(data, data + size, &mTxBuffer[mTxBufferIndex]);
        mTxBufferIndex += size;
        return size;
    } else {
        return 0;
    }
}

int TwoWire::available(void) { return mRxBufferSize - mRxBufferIndex; }

int TwoWire::read(void) {
    if(mRxBufferIndex < mRxBufferSize) {
        return mRxBuffer[mRxBufferIndex++];
    } else {
        return -1;
    }
}

int TwoWire::peek(void) {
    if(mRxBufferIndex < mRxBufferSize) {
        return mRxBuffer[mRxBufferIndex];
    } else {
        return -1;
    }
}

void TwoWire::flush(void) {}