/*
  Copyright 2016 Ivan Grokhotkov

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 9 Aug. 2019 by Hyeonki hong
*/

#include "api/itoa.h"

#include <math.h>

void reverse(char *begin, char *end);

char *itoa(int value, char *string, int radix) {
    if(radix < 2 || radix > 16) {
        *string = 0;
        return string;
    }

    char *out      = string;
    int   quotient = abs(value);

    do {
        const int tmp = quotient / radix;
        *out          = "0123456789abcdef"[quotient - (tmp * radix)];
        ++out;
        quotient = tmp;
    } while(quotient);

    // Apply negative sign
    if(value < 0) *out++ = '-';

    reverse(string, out);
    *out = 0;
    return string;
}

char *ltoa(long value, char *string, int radix) {
    if(radix < 2 || radix > 16) {
        *string = 0;
        return string;
    }

    char *out      = string;
    long  quotient = abs(value);

    do {
        const long tmp = quotient / radix;
        *out           = "0123456789abcdef"[quotient - (tmp * radix)];
        ++out;
        quotient = tmp;
    } while(quotient);

    // Apply negative sign
    if(value < 0) *out++ = '-';

    reverse(string, out);
    *out = 0;
    return string;
}

char *utoa(unsigned value, char *string, int radix) {
    if(radix < 2 || radix > 16) {
        *string = 0;
        return string;
    }

    char *   out      = string;
    unsigned quotient = value;

    do {
        const unsigned tmp = quotient / radix;
        *out               = "0123456789abcdef"[quotient - (tmp * radix)];
        ++out;
        quotient = tmp;
    } while(quotient);

    reverse(string, out);
    *out = 0;
    return string;
}

char *ultoa(unsigned long value, char *string, int radix) {
    if(radix < 2 || radix > 16) {
        *string = 0;
        return string;
    }

    char *        out      = string;
    unsigned long quotient = value;

    do {
        const unsigned long tmp = quotient / radix;
        *out                    = "0123456789abcdef"[quotient - (tmp * radix)];
        ++out;
        quotient = tmp;
    } while(quotient);

    reverse(string, out);
    *out = 0;
    return string;
}

void reverse(char *begin, char *end) {
    char *is = begin;
    char *ie = end - 1;
    while(is < ie) {
        char tmp = *ie;
        *ie      = *is;
        *is      = tmp;
        ++is;
        --ie;
    }
}