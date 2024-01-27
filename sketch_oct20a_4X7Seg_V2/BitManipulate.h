//By Darrien Varrette
//BitManipulate.h


#ifndef BitManipulate_h
#define BitManipulate_h


#include <bitset>
#include "BitManipulate.cpp"



/*
Writes to a bit of a variable, e.g. bool, int, long. Note that float & double are not supported. You can write to a bit of variables up to an unsigned long (32 bits / 4 bytes).
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitwrite/
x: the numeric variable to which to write.
n: which bit of the number to write, starting at 0 for the least-significant (rightmost) bit.
b: the value to write to the bit (0 or 1).
*/
void bitWrite(unsigned char &x, u_int8_t n, bool b);
void bitWrite(std::byte &x, u_int8_t n, bool b);

/*
Reads a bit of a variable, e.g. bool, int. Note that float & double are not supported. You can read the bit of variables up to an unsigned long long (64 bits / 8 bytes).
https://www.arduino.cc/reference/en/language/functions/bits-and-bytes/bitread/
x: the number from which to read.
n: which bit to read, starting at 0 for the least-significant (rightmost) bit.
returns
The value of the bit (0 or 1).
*/
bool bitRead(u_int8_t x, u_int8_t n);


#endif



