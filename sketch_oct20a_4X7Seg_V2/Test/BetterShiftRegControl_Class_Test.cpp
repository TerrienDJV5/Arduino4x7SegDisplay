//By Darrien Varrette
//BetterShiftRegControl_Class_Test.cpp

#include "../BetterShiftRegControl.cpp"//here to get compiled

#include <bitset>
#include <iostream>
/*
std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}
*/

using namespace std;

#include "../BetterShiftRegControl.h"







void BetterShiftRegControl::registerPinWrite(__uint16_t selectPinID, bool newState)
{
  std::cout << "(overwritten Func) register_PIN:"<<"(ID:"<< selectPinID <<")" <<" == " << newState << std::endl;
};


/*
IC_P_DS
IC_P_SH_CP
IC_P_ST_CP
IC_P_MR
IC_P_OE
*/

BetterShiftRegControl shiftregister_Test(2, IC_P_DS|IC_P_SH_CP|IC_P_ST_CP);
//u_int8_t pinconfig = shiftregister_Test.createPinUsageConfig(true, true, true, false, false);





int main()
{
  shiftregister_Test.setPinID(Data_74HC595, 34);
  shiftregister_Test.setPinID(Clock_74HC595, 35);
  shiftregister_Test.setPinID(Latch_74HC595, 36);
  shiftregister_Test.setPinID(Reset_74HC595, 37);
  shiftregister_Test.setPinID(OutputEnable_74HC595, 38);
  __uint16_t pinID_data = shiftregister_Test.getPinID(Data_74HC595);
  std::cout << pinID_data <<":" 
    << shiftregister_Test.getPinID(Clock_74HC595) <<":" 
    << shiftregister_Test.getPinID(Latch_74HC595) <<":" 
    << shiftregister_Test.getPinID(Reset_74HC595) <<":" 
    << shiftregister_Test.getPinID(OutputEnable_74HC595) <<":" << std::endl;
  
  shiftregister_Test.set_shift_register_outputs(0, 0b10101010);
  shiftregister_Test.set_shift_register_outputs(1, 0b11110000);
  shiftregister_Test.updateShiftRegister(MSB_FIRST);
  return 0;
};


