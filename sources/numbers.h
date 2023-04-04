/*
 * This project is Aiko, an operating system for weak devices like 
 * microcontrollers. It has support for devices based on eight-bit 
 * architectures. It is suitable even for devices with only 128 bytes 
 * of operational memory. You can make it easier to code your projects 
 * based on such platforms by using Aiko as a scheduler.
 *
 * Author: Cixo
 */

#ifndef CX_AIKO_NUMBERS_H_INCLUDED
#define CX_AIKO_NUMBERS_H_INCLUDED

/** \def AIKO_SHORT_NUMBERS
 * If Yoy want to use aiko on small embedded which 8 bit architecture, you can
 * use this switch, then aiko want to using 8 bit int not 16 bit.
 */
#ifndef AIKO_SHORT_NUMBERS

/** \typedef uint_t 
 * This is type for storing unsigned int numbers. You can change it for
 * example to uint16_t or uint8_t when You porting this.
 */
typedef unsigned int uint_t;

/** \def MAX_UINT_VALUE
 * This define maximum value of uint_t type.
 */
#define MAX_UINT_VALUE 0xFFFF

/* If user define using 8 bit numbers in aiko to optimize it */
#else

#include <stdint.h>

/** \typedef uint_t 
 * This is type for storing unsigned int numbers. You can change it for
 * example to uint16_t or uint8_t when You porting this.
 */
typedef uint8_t uint_t;

/** \def MAX_UINT_VALUE
 * This define maximum value of uint_t type.
 */
#define MAX_UINT_VALUE 0xFF

#endif

#endif
