/*
  UART.cpp - Hardware serial library for Wiring
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

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
  Modified 2019-2020 by Hyeonki hong (odroid support)
*/

#include "UART.h"

#include <cerrno>         // errno
#include <chrono>         // std::chrono::milliseconds()
#include <cstring>        // std::strerror()
#include <fcntl.h>        // open(), fcntl()
#include <iostream>       // std::cerr, std::endl
#include <stdexcept>      // std::runtime_error()
#include <sys/ioctl.h>    // ioctl()
#include <termios.h>
#include <thread>      // std::this_thread::sleep_for()
#include <unistd.h>    // read(), write(), close()

static inline ssize_t unistd_read(int fd, void *buf, size_t n) {
    return read(fd, buf, n);
}

static inline ssize_t unistd_write(int fd, const void *buf, size_t n) {
    return write(fd, buf, n);
}

// tty0uart - oduino
UartClass Serial("/dev/ttyhk0");

UartClass::UartClass(const std::string &device)
    : mFd(-1)
    , mDevice(device) {}

UartClass::~UartClass() { end(); }

void UartClass::begin(unsigned long baudrate, uint16_t mode) {
    if(mFd > 0) { end(); }

    // No controlling tty, Enables nonblocking mode.
    mFd = open(mDevice.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(mFd < 0) {
        std::cerr << "Failed to open " << mDevice << std::endl;
        throw std::runtime_error(std::strerror(errno));
    }

    // Explicit reset due to O_NONBLOCK.
    fcntl(mFd, F_SETFL, O_RDWR);
    setBaudrate(baudrate);
    setMode(mode);
}

void UartClass::end() {
    close(mFd);
    mFd = -1;
}

int UartClass::available(void) {
    int result;

    if(ioctl(mFd, FIONREAD, &result) < 0) {
        std::cerr << "Failed to read UART RX buffer size." << std::endl;
        return -1;
    }

    return result;
}

int UartClass::peek(void) { return -1; }

int UartClass::read(void) {
    uint8_t data;
    if(unistd_read(mFd, &data, 1) != 1) {
        std::cerr << "Failed to read UART RX buffer." << std::endl;
        return -1;
    }
    return data;
}

int UartClass::availableForWrite(void) { return -1; }

void UartClass::flush(void) {}

size_t UartClass::write(uint8_t c) { return unistd_write(mFd, &c, 1); }

size_t UartClass::write(const uint8_t *buffer, size_t size) {
    return unistd_write(mFd, buffer, size);
}

void UartClass::setBaudrate(uint32_t baudrate) {
    struct termios options;
    speed_t        baudrate_ = B0;

    switch(baudrate) {
    case 50: baudrate_ = B50; break;
    case 75: baudrate_ = B75; break;
    case 110: baudrate_ = B110; break;
    case 134: baudrate_ = B134; break;
    case 150: baudrate_ = B150; break;
    case 200: baudrate_ = B200; break;
    case 300: baudrate_ = B300; break;
    case 600: baudrate_ = B600; break;
    case 1200: baudrate_ = B1200; break;
    case 1800: baudrate_ = B1800; break;
    case 2400: baudrate_ = B2400; break;
    case 4800: baudrate_ = B4800; break;
    case 9600: baudrate_ = B9600; break;
    case 19200: baudrate_ = B19200; break;
    case 38400: baudrate_ = B38400; break;
    case 57600: baudrate_ = B57600; break;
    case 115200: baudrate_ = B115200; break;
    case 230400: baudrate_ = B230400; break;
    case 460800: baudrate_ = B460800; break;
    case 500000: baudrate_ = B500000; break;
    case 576000: baudrate_ = B576000; break;
    case 921600: baudrate_ = B921600; break;
    case 1000000: baudrate_ = B1000000; break;
    case 1152000: baudrate_ = B1152000; break;
    case 1500000: baudrate_ = B1500000; break;
    case 2000000: baudrate_ = B2000000; break;
    case 2500000: baudrate_ = B2500000; break;
    case 3000000: baudrate_ = B3000000; break;
    case 3500000: baudrate_ = B3500000; break;
    case 4000000: baudrate_ = B4000000; break;
    default:
        baudrate_ = B115200;
        std::cerr << baudrate << " is invalid." << std::endl
                  << "115200 is set to buadrate." << std::endl;
        break;
    };

    tcgetattr(mFd, &options);

    cfsetispeed(&options, baudrate_);
    cfsetospeed(&options, baudrate_);

    tcsetattr(mFd, TCSANOW, &options);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void UartClass::setMode(uint16_t mode) {
    struct termios options;

    tcgetattr(mFd, &options);

    // Raw level read/write. Non-standard.
    cfmakeraw(&options);

    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 100;    // timeout = 10s

    // Ignore Error.
    options.c_iflag |= IGNPAR;

    // Disable implementation-defined output processing.
    options.c_oflag &= ~OPOST;

    options.c_cflag |= (CLOCAL | CREAD);

    options.c_cflag &= ~CSIZE;
    switch(mode & SERIAL_DATA_MASK) {
    case SERIAL_DATA_5: options.c_cflag |= CS5;
    case SERIAL_DATA_6: options.c_cflag |= CS6;
    case SERIAL_DATA_7: options.c_cflag |= CS7;
    case SERIAL_DATA_8: options.c_cflag |= CS8;
    }

    switch(mode & SERIAL_PARITY_MASK) {
    case SERIAL_PARITY_NONE:
        // None
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~INPCK;
        break;
    case SERIAL_PARITY_EVEN:
        // Even
        options.c_iflag |= INPCK;
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        break;
    case SERIAL_PARITY_ODD:
        // Odd
        options.c_iflag |= INPCK;
        options.c_cflag |= PARENB;
        options.c_cflag |= PARODD;
        break;
    case SERIAL_PARITY_MARK:
        // Mark
        break;
    case SERIAL_PARITY_SPACE:
        // Space
        break;
    }

    switch(mode & SERIAL_STOP_BIT_MASK) {
    case SERIAL_STOP_BIT_1: options.c_cflag &= ~CSTOPB; break;
    case SERIAL_STOP_BIT_2: options.c_cflag |= CSTOPB; break;
    }

    options.c_lflag &= ~(ISIG | ICANON | ECHO | ECHOE);

    tcsetattr(mFd, TCSANOW, &options);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}