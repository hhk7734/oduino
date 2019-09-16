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
  Modified 19 June 2019 by Hyeonki hong (odroid support)
*/

#include "UART.h"

#include <wiringSerial.h>
#include <unistd.h>
#include <pthread.h>

UartClass Serial( NULL );

#if defined( ARDUINO_ODROID_C2 ) || defined( ARDUINO_ODROID_N2 )
UartClass Serial1( "/dev/ttyS1" );
#endif

#if defined( ARDUINO_ODROID_XU3 ) || defined( ARDUINO_ODROID_XU4 )
UartClass Serial1( "/dev/ttySAC0" );
#endif

#if defined( ARDUINO_ODROID_N2 )
UartClass Serial2( "/dev/ttyS2" );
#endif

const int BUFFER_SIZE = 256;
char      buffer[BUFFER_SIZE];
uint16_t  buffer_head = 0;
uint16_t  buffer_tail = 0;
pthread_t stdin_thread;

UartClass::UartClass( const char *_device )
{
    if( _device != NULL )
    {
        device = ( char * )malloc( sizeof( char ) * ( strlen( _device ) + 1 ) );
        strcpy( device, _device );
    }
}

void *stdin_thread_loop( void *arg )
{
    for( ;; )
    {
        char temp = serialGetchar( STDIN_FILENO );

        if( temp == '\n' )
        {
            buffer[buffer_head] = '\r';
            buffer_head         = ( buffer_head + 1 ) % BUFFER_SIZE;
            if( buffer_head == buffer_tail )
            {
                buffer_tail = ( buffer_tail + 1 ) % BUFFER_SIZE;
            }
        }

        buffer[buffer_head] = temp;
        buffer_head         = ( buffer_head + 1 ) % BUFFER_SIZE;

        if( buffer_head == buffer_tail )
        {
            buffer_tail = ( buffer_tail + 1 ) % BUFFER_SIZE;
        }
    }
}

void UartClass::begin( unsigned long baudrate, uint16_t config )
{
    if( device == NULL )
    {
        fd = STDOUT_FILENO;
        pthread_create( &stdin_thread, NULL, stdin_thread_loop, NULL );
    }
    else
    {
        fd = serialOpen( device, baudrate );
    }
}

void UartClass::end()
{
    if( device != NULL )
    {
        serialClose( fd );
        free( device );
    }
}

int UartClass::available( void )
{
    if( device != NULL )
    {
        return serialDataAvail( fd );
    }
    else
    {
        return ( BUFFER_SIZE + buffer_head - buffer_tail ) % BUFFER_SIZE;
    }
}
int UartClass::peek( void ) {}

int UartClass::read( void )
{
    if( device != NULL )
    {
        return serialGetchar( fd );
    }
    else
    {
        if( available() != 0 )
        {
            char temp   = buffer[buffer_tail];
            buffer_tail = ( buffer_tail + 1 ) % BUFFER_SIZE;
            return temp;
        }
        else
        {
            return -1;
        }
    }
}
int UartClass::availableForWrite( void ) {}

void UartClass::flush( void ) {}

size_t UartClass::write( uint8_t c )
{
    serialPutchar( fd, c );
    return 1;
}