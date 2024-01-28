//By Darrien Varrette
//BitManipulate.cpp




#include "BitManipulate.h"



void bitWrite(unsigned char &x, __uint8_t n, bool b)
{
  unsigned char write_Mask = u_char{0b00000001};
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
  //
};

void bitWrite(__uint8_t &x, __uint8_t n, bool b)
{
  __uint8_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
};
void bitWrite(__uint16_t &x, __uint16_t n, bool b)
{
  __uint16_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
};
void bitWrite(__uint32_t &x, __uint32_t n, bool b)
{
  __uint32_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
};
void bitWrite(__uint64_t &x, __uint64_t n, bool b)
{
  __uint64_t write_Mask = 0b00000001;
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
};


bool bitRead(__uint8_t x, __uint8_t n)
{
  __uint8_t read_Mask = 0b00000001;
  read_Mask = (read_Mask << n);
  return (read_Mask != 0);
}
bool bitRead(__uint16_t x, __uint16_t n)
{
  __uint16_t read_Mask = 0b0000000000000001;
  read_Mask = (read_Mask << n);
  return (read_Mask != 0);
}
bool bitRead(__uint32_t x, __uint32_t n)
{
  __uint32_t read_Mask = 0b000000000000000000000001;
  read_Mask = (read_Mask << n);
  return (read_Mask != 0);
}
bool bitRead(__uint64_t x, __uint64_t n)
{
  __uint64_t read_Mask = 0b00000000000000000000000000000000000000000000000000000001;
  read_Mask = (read_Mask << n);
  return (read_Mask != 0);
}



