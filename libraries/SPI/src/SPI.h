#ifndef _SPI_H_
#define _SPI_H_
#pragma once

#include <Arduino.h>

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

#define SPI_CLOCK_DIV2 0xFF
#define SPI_CLOCK_DIV4 0xFF
#define SPI_CLOCK_DIV8 0xFF
#define SPI_CLOCK_DIV16 0xFF
#define SPI_CLOCK_DIV32 0xFF
#define SPI_CLOCK_DIV64 0xFF
#define SPI_CLOCK_DIV128 0xFF

class SPISettings
{
public:
    SPISettings();
    SPISettings( uint32_t clock, uint8_t bitOrder, uint8_t dataMode ) {}
    friend class SPIClass;
};

class SPIClass
{
public:
    SPIClass( uint8_t _channel );
    void begin( const char *device, uint32_t speed, uint8_t mode );
    void begin( uint32_t speed, uint8_t mode );
    void begin( void ) { begin( 1000000, 0 ); }
    void end( void );

    void setBitOrder( uint8_t bitOrder );
    void setDataMode( uint8_t dataMode );
    void setClockDivider( uint8_t clockDiv );
    void setFrequency( uint32_t freq );

    void beginTransaction( SPISettings settings );
    void endTransaction( void );

    uint8_t  transfer( uint8_t data );
    uint8_t  transfer( uint8_t *buf, size_t count );
    uint16_t transfer16( uint16_t data );

private:
    int     fd;
    uint8_t channel;
};

extern SPIClass  SPI0;
extern SPIClass &SPI;

#endif    // _SPI_H_