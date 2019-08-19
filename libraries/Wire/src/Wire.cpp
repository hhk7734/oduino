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

#include "Wire.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#if defined( ARDUINO_ODROID_C1 ) || defined( ARDUINO_ODROID_C2 ) || defined( ARDUINO_ODROID_XU3 ) \
    || defined( ARDUINO_ODROID_XU4 )
TwoWire Wire1( 1 );
#endif

#if defined( ARDUINO_ODROID_C1 ) || defined( ARDUINO_ODROID_C2 ) || defined( ARDUINO_ODROID_N2 )
TwoWire Wire2( 2 );
#endif

#if defined( ARDUINO_ODROID_N2 )
TwoWire Wire3( 3 );
#endif

#if defined( ARDUINO_ODROID_XU3 ) || defined( ARDUINO_ODROID_XU4 )
TwoWire Wire5( 5 );
#endif

#if defined( ARDUINO_ODROID_C1 ) || defined( ARDUINO_ODROID_C2 ) || defined( ARDUINO_ODROID_XU3 ) \
    || defined( ARDUINO_ODROID_XU4 )
TwoWire &Wire = Wire1;
#elif defined( ARDUINO_ODROID_N2 )
TwoWire &Wire = Wire2;
#endif

TwoWire::TwoWire( uint8_t _i2c_num )
    : i2c_num( _i2c_num )
    , fd( -1 )
{
}

void TwoWire::begin( uint8_t slave_address )
{
    char device[11];

    device_address = slave_address;

    sprintf( device, "/dev/i2c-%d", i2c_num );

    if( fd > 0 )
    {
        end();
    }
    if( ( fd = open( device, O_RDWR ) ) < 0 )
    {
        fprintf( stderr, "Unable to open %s : %s\n", device, strerror( errno ) );
        exit( -1 );
    }
}

void TwoWire::end( void )
{
    close( fd );
    fd = -1;
}

void TwoWire::setClock( uint32_t clock ) {}

void TwoWire::beginTransmission( uint8_t slave_address )
{
    device_address = slave_address;
    tx_buff_index  = 0;
}

uint8_t TwoWire::endTransmission( bool stop )
{
    if( stop )
    {
        if( tx_buff_index > 0 )
        {
            struct i2c_rdwr_ioctl_data i2c;
            struct i2c_msg             msgs;
            msgs.addr  = device_address;
            msgs.flags = 0;
            msgs.len   = tx_buff_index;
            msgs.buf   = tx_buff;

            i2c.msgs  = &msgs;
            i2c.nmsgs = 1;

            return ioctl( fd, I2C_RDWR, &i2c );
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

uint8_t TwoWire::requestFrom( uint8_t slave_address, size_t len, bool stop )
{
    device_address = slave_address;
    rx_buff_index  = 0;
    rx_buff_len    = len;

    struct i2c_rdwr_ioctl_data i2c;
    struct i2c_msg             msgs[2];

    if( tx_buff_index > 0 )
    {
        msgs[0].addr  = device_address;
        msgs[0].flags = 0;    /// write
        msgs[0].len   = tx_buff_index;
        msgs[0].buf   = tx_buff;

        msgs[1].addr  = device_address;
        msgs[1].flags = I2C_M_RD;    /// read
        msgs[1].len   = rx_buff_len;
        msgs[1].buf   = rx_buff;

        i2c.msgs  = msgs;
        i2c.nmsgs = 2;
    }
    else
    {
        msgs[0].addr  = device_address;
        msgs[0].flags = I2C_M_RD;    /// read
        msgs[0].len   = rx_buff_len;
        msgs[0].buf   = rx_buff;

        i2c.msgs  = msgs;
        i2c.nmsgs = 1;
    }

    return ioctl( fd, I2C_RDWR, &i2c );
}

uint8_t TwoWire::requestFrom( uint8_t slave_address, size_t len )
{
    return requestFrom( slave_address, len, true );
}

uint8_t TwoWire::requestFrom( int slave_address, int len )
{
    return requestFrom( ( uint8_t )slave_address, ( size_t )len, true );
}

uint8_t TwoWire::requestFrom( int slave_address, int len, int stop )
{
    return requestFrom( ( uint8_t )slave_address, ( size_t )len, ( bool )true );
}

size_t TwoWire::write( uint8_t data )
{
    if( tx_buff_index < I2C_BUFFER_SIZE )
    {
        tx_buff[tx_buff_index++] = data;
    }
    else
    {
    }
}

size_t TwoWire::write( const uint8_t *data, size_t len )
{
    if( tx_buff_index + len - 1 < I2C_BUFFER_SIZE )
    {
        memcpy( &tx_buff[tx_buff_index], data, len );
        tx_buff_index += len;
    }
}

int TwoWire::available( void )
{
    return rx_buff_len - rx_buff_index;
}

int TwoWire::read( void )
{
    if( rx_buff_index < rx_buff_len )
    {
        return rx_buff[rx_buff_index++];
    }
    else
    {
        return 0;
    }
}

int TwoWire::peek( void ) {}

void TwoWire::flush( void ) {}

void TwoWire::onReceive( void ( * )( int ) ) {}

void TwoWire::onRequest( void ( * )( void ) ) {}