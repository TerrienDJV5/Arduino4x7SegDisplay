//By Darrien Varrette
//BitManipulate.cpp


#include "Arduino.h"

#include "BitManipulate.h"


void bit_Write(__uint8_t &x, __uint8_t n, bool b)
{
  __uint8_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x & ~write_Mask;
  x = x ^ (write_Mask * b);
};
void bit_Write(__uint16_t &x, __uint8_t n, bool b)
{
  __uint16_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x & ~write_Mask;
  x = x ^ (write_Mask * b);
};
void bit_Write(__uint32_t &x, __uint8_t n, bool b)
{
  __uint32_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x & ~write_Mask;
  x = x ^ (write_Mask * b);
};
void bit_Write(__uint64_t &x, __uint8_t n, bool b)
{
  __uint64_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x & ~write_Mask;
  x = x ^ (write_Mask * b);
};


bool bit_Read(__uint8_t x, __uint8_t n)
{
  __uint8_t read_Mask = 0b00000001;
  read_Mask = (read_Mask << n);
  return ((x&read_Mask) != 0);
}
bool bit_Read(__uint16_t x, __uint8_t n)
{
  __uint16_t read_Mask = 0b0000000000000001;
  read_Mask = (read_Mask << n);
  return ((x&read_Mask) != 0);
}
bool bit_Read(__uint32_t x, __uint8_t n)
{
  __uint32_t read_Mask = 0b000000000000000000000001;
  read_Mask = (read_Mask << n);
  return ((x&read_Mask) != 0);
}
bool bit_Read(__uint64_t x, __uint8_t n)
{
  __uint64_t read_Mask = 0b00000000000000000000000000000000000000000000000000000001;
  read_Mask = (read_Mask << n);
  return ((x&read_Mask) != 0);
}



