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

#include "SPI.h"

#include <iostream>

#include <wiringPiSPI.h>
#include <unistd.h>

int      SPIClass::fd          = -1;
uint32_t SPIClass::clock_speed = 1000000;
uint8_t  SPIClass::spi_mode    = 0;

void SPIClass::begin( uint32_t speed, uint8_t mode )
{
    clock_speed = speed;
    spi_mode    = mode;
    fd          = wiringPiSPISetupMode( 0, speed, mode );

    std::cout << "If you want to use multiple SPI device, don't use the CE0 pin" << std::endl;
}

void SPIClass::end( void ) { close( fd ); }

void SPIClass::setBitOrder( uint8_t bitOrder ) {}

void SPIClass::setDataMode( uint8_t dataMode )
{
    spi_mode = dataMode;
    begin( clock_speed, spi_mode );
}
void SPIClass::setClockDivider( uint8_t clockDiv ) {}

void setFrequency( uint32_t freq )
{
    clock_speed = freq;
    begin( clock_speed, spi_mode );
}

void SPIClass::beginTransaction( SPISettings settings ) {}
void SPIClass::endTransaction( void ) {}

uint8_t SPIClass::transfer( uint8_t data )
{
    wiringPiSPIDataRW( fd, &data, 1 );
    return data;
}

uint8_t SPIClass::transfer( void *buf, size_t count )
{
    return wiringPiSPIDataRW( fd, buf, count );
}

uint16_t SPIClass::transfer16( uint16_t data ) {}