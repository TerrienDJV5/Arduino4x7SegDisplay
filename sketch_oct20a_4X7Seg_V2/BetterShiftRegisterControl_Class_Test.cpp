//By Darrien Varrette
//BetterShiftRegisterControl_Class_Test.cpp



#include "BetterShiftRegisterControl.cpp"

using namespace std;

/*
enum PinNames_of_74HC595 {
  Clock_74HC595, 
  Data_74HC595, 
  Latch_74HC595, 
  Reset_74HC595, 
  OutputEnable_74HC595, 
};
*/

/*
_Data_PinIDMask_
_Clock_PinIDMask_
_Latch_PinIDMask_
_Reset_PinIDMask_
_OutputEnable_PinIDMask_
_Empty_PinIDMask_
*/
//BetterShiftRegisterControl BSRC_enum;

void BetterShiftRegisterControl::registerPinWrite(std::byte selectPinID, bool newState)
{
  std::cout << "(overwritten Func) register_PIN:"<<"(ID:"<< selectPinID <<")" <<" == " << newState << std::endl;
};

BetterShiftRegisterControl::_pinName2IDMaskList_enum config_Connected_Pins[5] = {
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Data_PinIDMask_,
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Clock_PinIDMask_,
  BetterShiftRegisterControl::_pinName2IDMaskList_enum::_Latch_PinIDMask_,
};
BetterShiftRegisterControl shiftregister_Test(2, config_Connected_Pins);

//u_int8_t pinconfig = shiftregister_Test.createPinUsageConfig(true, true, true, false, false);





int main()
{
  shiftregister_Test.setPinID((PinNames_of_74HC595)Data_74HC595, 34);
  shiftregister_Test.setPinID(Clock_74HC595, 35);
  shiftregister_Test.setPinID(Latch_74HC595, 36);
  shiftregister_Test.setPinID(Reset_74HC595, 37);
  shiftregister_Test.setPinID(OutputEnable_74HC595, 38);
  std::cout << shiftregister_Test.getPinID((PinNames_of_74HC595)Data_74HC595) <<":" 
    << shiftregister_Test.getPinID(Clock_74HC595) <<":" 
    << shiftregister_Test.getPinID(Latch_74HC595) <<":" 
    << shiftregister_Test.getPinID(Reset_74HC595) <<":" 
    << shiftregister_Test.getPinID(OutputEnable_74HC595) <<":" << std::endl;
  
  shiftregister_Test.set_shift_register_outputs(0, 0b10101010);
  shiftregister_Test.set_shift_register_outputs(1, 0b11110000);
  shiftregister_Test.updateShiftRegister(MSBFIRST);
  return 0;
};


