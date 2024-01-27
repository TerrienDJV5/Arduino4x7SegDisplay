//By Darrien Varrette
//BetterShiftRegisterControl.cpp

#include "BetterShiftRegisterControl.h"

/*
using namespace std;
#include <bitset>
#include <cstddef>
#include <iostream>
std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}
#include <string.h>
#include <sstream>
*/



void BetterShiftRegisterControl::setPinID(PinNames_of_74HC595 pinSelect, u_int16_t input_PinID)
{
  switch(pinSelect)
  {
    case (PinNames_of_74HC595)Clock_74HC595:
      this->_clockPinID = input_PinID;
      break;
    case (PinNames_of_74HC595)Data_74HC595:
      this->_dataPinID = input_PinID;
      break;
    case (PinNames_of_74HC595)Latch_74HC595:
      this->_latchPinID = input_PinID;
      break;
    case (PinNames_of_74HC595)Reset_74HC595:
      this->_resetPinID = input_PinID;
      break;
    case (PinNames_of_74HC595)OutputEnable_74HC595:
      this->_outputEnablePinID = input_PinID;
      break;
    default:
      break;
  }
};

u_int16_t BetterShiftRegisterControl::getPinID(PinNames_of_74HC595 pinSelect)
{
  u_int16_t getPinID = -1;
  switch(pinSelect)
  {
    case (PinNames_of_74HC595)Clock_74HC595:
      getPinID = this->_clockPinID;
      break;
    case (PinNames_of_74HC595)Data_74HC595:
      getPinID = this->_dataPinID;
      break;
    case (PinNames_of_74HC595)Latch_74HC595:
      getPinID = this->_latchPinID;
      break;
    case (PinNames_of_74HC595)Reset_74HC595:
      getPinID = this->_resetPinID;
      break;
    case (PinNames_of_74HC595)OutputEnable_74HC595:
      getPinID = this->_outputEnablePinID;
      break;
    default:
      getPinID = -1;
      break;
  }
  return getPinID;
}

u_int8_t BetterShiftRegisterControl::createPinUsageConfig(bool dataPin, bool clockPin, bool latchPin, bool outputenablePin, bool resetPin)
{
  return (_Clock_PinIDMask_*clockPin | _Data_PinIDMask_*dataPin | _Latch_PinIDMask_*latchPin | _Reset_PinIDMask_*resetPin | _OutputEnable_PinIDMask_*outputenablePin);
}


