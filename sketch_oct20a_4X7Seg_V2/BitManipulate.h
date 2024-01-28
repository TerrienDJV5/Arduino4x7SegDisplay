//By Darrien Varrette
//BitManipulate.h


#ifndef BitManipulate_h
#define BitManipulate_h


#include <bitset>




/*
Writes to a bit of a variable, e.g. bool, int, long. Note that float & double are not supported. You can write to a bit of variables up to an unsigned long (32 bits / 4 bytes).
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitwrite/
example: bitWrite(&x, n, b)
x: the numeric variable to which to write.
n: which bit of the number to write, starting at 0 for the least-significant (rightmost) bit.
b: the value to write to the bit (0 or 1).
*/
void bit_Write(__uint8_t &x, __uint8_t n, bool b);
void bit_Write(__uint16_t &x, __uint16_t n, bool b);
void bit_Write(__uint32_t &x, __uint32_t n, bool b);
void bit_Write(__uint64_t &x, __uint64_t n, bool b);

/*
Reads a bit of a variable, e.g. bool, int. Note that float & double are not supported. You can read the bit of variables up to an unsigned long long (64 bits / 8 bytes).
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitread/
example: bitResult = bitRead(x, n)
x: the number from which to read.
n: which bit to read, starting at 0 for the least-significant (rightmost) bit.
returns
The value of the bit (0 or 1).
*/
bool bit_Read(__uint8_t x, __uint8_t n);
bool bit_Read(__uint16_t x, __uint16_t n);
bool bit_Read(__uint32_t x, __uint32_t n);
bool bit_Read(__uint64_t x, __uint64_t n);


#endif



