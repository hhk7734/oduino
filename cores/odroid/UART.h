/*
  UART.h - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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

  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
  Modified 2019-2020 by Hyeonki hong (odroid support)
*/

#ifndef _UART_CLASS_H_
#define _UART_CLASS_H_
#pragma once

#include "api/HardwareSerial.h"

#include <string>

class UartClass: public HardwareSerial {
public:
    UartClass(const std::string &device);
    ~UartClass();

    void begin(unsigned long baudrate, uint16_t mode);
    void begin(unsigned long baudrate = 115200) { begin(baudrate, SERIAL_8N1); }
    void end(void);
    virtual int    available(void) override;
    virtual int    peek(void) override;
    virtual int    read(void) override;
    virtual int    availableForWrite(void);
    virtual void   flush(void) override;
    virtual size_t write(uint8_t) override;
    inline size_t  write(unsigned long n) { return write((uint8_t)n); }
    inline size_t  write(long n) { return write((uint8_t)n); }
    inline size_t  write(unsigned int n) { return write((uint8_t)n); }
    inline size_t  write(int n) { return write((uint8_t)n); }
    using Print::write;    // pull in write(str) and write(buf, size) from Print
    virtual size_t write(const uint8_t *buffer, size_t size) override;
    virtual        operator bool() override { return true; }

protected:
    std::string mDevice;
    int         mFd;

private:
    void setBaudrate(uint32_t baudrate);
    void setMode(uint16_t mode);
};

extern UartClass Serial;
#define HAVE_HWSERIAL0

#endif    // _UART_CLASS_H_
