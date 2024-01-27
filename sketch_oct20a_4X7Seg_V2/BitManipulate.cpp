//By Darrien Varrette
//BitManipulate.cpp




#include "BitManipulate.h"


void bitWrite(unsigned char &x, u_int8_t n, bool b)
{
  unsigned char write_Mask = u_char{0b00000001};
  write_Mask = (write_Mask << n);
  x = x ^ write_Mask;
  //
};
void bitWrite(std::byte &x, u_int8_t n, bool b)
{
  u_int8_t write_Mask = u_int8_t{0b00000001};
  write_Mask = (write_Mask << n);
  x = x ^ std::byte{write_Mask};
  //
};


bool bitRead(u_int8_t x, u_int8_t n)
{
  u_int8_t read_Mask = u_int8_t{0b00000001};
  read_Mask = (read_Mask << n);
  return (read_Mask != 0);
}




