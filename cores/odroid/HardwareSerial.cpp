/*
  HardwareSerial.cpp - Hardware serial library for Wiring
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
  Modified 19 June 2019 by Hyeonki hong (odroid support)
*/

#include "HardwareSerial.h"

#include <iostream>

#include <wiringSerial.h>
#include <unistd.h>

HardwareSerial::HardwareSerial( uint8_t _uart_num )
    : uart_num( _uart_num )
{
}

int HardwareSerial::begin( uint32_t baud_rate )
{
    switch( uart_num )
    {
        case 0: fd = STDOUT_FILENO; break;
        case 1: fd = serialOpen( "/dev/ttyS1", baud_rate ); break;
        case 2: fd = serialOpen( "/dev/ttyS2", baud_rate ); break;
        default: fd = -1; break;
    }

    return fd;
}

void HardwareSerial::end()
{
    if( uart_num != 0 ) { serialClose( fd ); }
}

int HardwareSerial::available( void ) { serialDataAvail( fd ); }

int HardwareSerial::peek( void ) {}

int HardwareSerial::read( void ) { return serialGetchar( fd ); }

int HardwareSerial::availableForWrite( void ) {}

void HardwareSerial::flush( void ) {}

size_t HardwareSerial::write( uint8_t c ) { serialPutchar( fd, c ); }

HardwareSerial Serial( 0 );
HardwareSerial Serial1( 1 );
HardwareSerial Serial2( 2 );