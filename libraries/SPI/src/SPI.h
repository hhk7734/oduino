/* 
  SPI.h - SPI library for odroid

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
#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stddef.h>

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

class SPISettings
{
public:
    SPISettings();
};

class SPIClass
{
public:
    static void begin( uint32_t speed, uint8_t mode );
    static void begin( void ) { begin( 1000000, 0 ); }
    static void end( void );

    static void setBitOrder( uint8_t bitOrder );
    static void setDataMode( uint8_t dataMode );
    static void setClockDivider( uint8_t clockDiv );
    static void setFrequency( uint32_t freq );

    static void beginTransaction( SPISettings settings );
    static void endTransaction( void );

    static uint8_t  transfer( uint8_t data );
    static uint8_t  transfer( uint8_t *buf, size_t count );
    static uint16_t transfer16( uint16_t data );

private:
    static int      fd;
    static uint32_t clock_speed;
    static uint8_t  spi_mode;
};

extern SPIClass SPI;

#endif    // _SPI_H_