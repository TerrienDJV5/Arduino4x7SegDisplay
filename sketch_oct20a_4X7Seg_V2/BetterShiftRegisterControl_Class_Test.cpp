//By Darrien Varrette
//BetterShiftRegisterControl_Class_Test.cpp



#include <bitset>
#include <iostream>
std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}

using namespace std;

#include "BetterShiftRegisterControl.h"





void BetterShiftRegisterControl::registerPinWrite(__uint16_t selectPinID, bool newState)
{
  std::cout << "(overwritten Func) register_PIN:"<<"(ID:"<< selectPinID <<")" <<" == " << newState << std::endl;
};

/*
BetterShiftRegisterControl::_pinName2IDMaskList_enum config_Connected_Pins[5] = {
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Data_PinIDMask_,
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Clock_PinIDMask_,
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Latch_PinIDMask_,
};
BetterShiftRegisterControl shiftregister_Test(2, config_Connected_Pins);
*/

/*
IC_P_DS
IC_P_SH_CP
IC_P_ST_CP
IC_P_MR
IC_P_OE
*/

BetterShiftRegisterControl shiftregister_Test(2, IC_P_DS|IC_P_SH_CP|IC_P_ST_CP);
//u_int8_t pinconfig = shiftregister_Test.createPinUsageConfig(true, true, true, false, false);





int main()
{
  shiftregister_Test.setPinID((PinNames_of_74HC595)Data_74HC595, 34);
  shiftregister_Test.setPinID(Clock_74HC595, 35);
  shiftregister_Test.setPinID(Latch_74HC595, 36);
  shiftregister_Test.setPinID(Reset_74HC595, 37);
  shiftregister_Test.setPinID(OutputEnable_74HC595, 38);
  __uint16_t pinID_data = shiftregister_Test.getPinID((PinNames_of_74HC595)Data_74HC595);
  std::cout << pinID_data <<":" 
    << shiftregister_Test.getPinID(Clock_74HC595) <<":" 
    << shiftregister_Test.getPinID(Latch_74HC595) <<":" 
    << shiftregister_Test.getPinID(Reset_74HC595) <<":" 
    << shiftregister_Test.getPinID(OutputEnable_74HC595) <<":" << std::endl;
  
  shiftregister_Test.set_shift_register_outputs(0, 0b10101010);
  shiftregister_Test.set_shift_register_outputs(1, 0b11110000);
  shiftregister_Test.updateShiftRegister(MSBFIRST);
  return 0;
};


