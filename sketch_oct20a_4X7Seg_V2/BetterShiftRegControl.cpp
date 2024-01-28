//By Darrien Varrette
//BetterShiftRegControl.cpp

#include "BetterShiftRegControl.h"


BetterShiftRegControl::BetterShiftRegControl(__uint16_t register_init_count, __uint8_t connected_Pins_mask)
{
  this->_init_BetterShiftRegisterControl_Private(register_init_count);
  std::cout << "Fata Pin: " << (connected_Pins_mask&IC_P_DS) << std::endl;
  std::cout << "Clock Pin: " << (connected_Pins_mask&IC_P_SH_CP) << std::endl;
  std::cout << "Latch Pin: " << (connected_Pins_mask&IC_P_ST_CP) << std::endl;
  std::cout << "Reset Pin: " << (connected_Pins_mask&IC_P_MR) << std::endl;
  std::cout << "OutputEnable Pin: " << (connected_Pins_mask&IC_P_OE) << std::endl;
  this->_Connected_Pins_Mask = connected_Pins_mask;
};

void BetterShiftRegControl::_init_BetterShiftRegisterControl_Private(__uint16_t register_init_count)
{
  this->_registerCount = register_init_count;
  this->_init_registerPinState();
  this->_set_registerPinState((PinNames_of_74HC595)Data_74HC595, LOW);
  this->_set_registerPinState((PinNames_of_74HC595)Clock_74HC595, LOW);
  this->_set_registerPinState((PinNames_of_74HC595)Latch_74HC595, LOW);
  this->_set_registerPinState((PinNames_of_74HC595)Reset_74HC595, HIGH);
  this->_set_registerPinState((PinNames_of_74HC595)OutputEnable_74HC595, LOW);
};

void BetterShiftRegControl::_init_registerPinState()
{
  this->_registerPinState = (__uint8_t*)malloc( _registerCount );
};


void BetterShiftRegControl::_set_registerPinState(PinNames_of_74HC595 pinSelect, bool newState)
{
  __uint8_t lastpinstate = this->_allPinStates;
  _pinName2IDMaskList_enum pinSelectMask;
  switch (pinSelect)
  {
    case (PinNames_of_74HC595)Data_74HC595:
      pinSelectMask = _Data_PinIDMask_;
      this->_allPinStates = (this->_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
      break;
    case (PinNames_of_74HC595)Clock_74HC595:
      pinSelectMask = _Clock_PinIDMask_;
      this->_allPinStates = (this->_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
      break;
    case (PinNames_of_74HC595)Latch_74HC595:
      pinSelectMask = _Latch_PinIDMask_;
      this->_allPinStates = (this->_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
      break;
    case (PinNames_of_74HC595)Reset_74HC595:
      pinSelectMask = _Reset_PinIDMask_;
      this->_allPinStates = (this->_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
      break;
    case (PinNames_of_74HC595)OutputEnable_74HC595:
      pinSelectMask = _OutputEnable_PinIDMask_;
      this->_allPinStates = (this->_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
      break;
    default:
      break;
  };
  if (lastpinstate != this->_allPinStates){
    this->flushed_to_registers = false;
  }else{
    this->flushed_to_registers = true;
  }
};


void BetterShiftRegControl::_flush_registerPinState()
{
  if (flushed_to_registers==false){
    __uint16_t pinID_OE = getPinID((PinNames_of_74HC595)OutputEnable_74HC595);
    __uint16_t pinID_CLK = getPinID((PinNames_of_74HC595)Clock_74HC595);
    __uint16_t pinID_MR = getPinID((PinNames_of_74HC595)Reset_74HC595);
    __uint16_t pinID_LATCH = getPinID((PinNames_of_74HC595)Latch_74HC595);
    __uint16_t pinID_DS = getPinID((PinNames_of_74HC595)Data_74HC595);
    registerPinWrite(pinID_CLK, _get_registerPinState((PinNames_of_74HC595)Clock_74HC595));
    registerPinWrite(pinID_OE, _get_registerPinState((PinNames_of_74HC595)OutputEnable_74HC595));
    registerPinWrite(pinID_MR, _get_registerPinState((PinNames_of_74HC595)Reset_74HC595));
    registerPinWrite(pinID_LATCH, _get_registerPinState((PinNames_of_74HC595)Latch_74HC595));
    registerPinWrite(pinID_DS, _get_registerPinState((PinNames_of_74HC595)Data_74HC595));
  };
  this->flushed_to_registers = true;
};




bool BetterShiftRegControl::_get_registerPinState(PinNames_of_74HC595 pinSelect)
{
  switch (pinSelect)
  {
    case Data_74HC595:
      return (_allPinStates & _dataPinMask)==_dataPinMask;
      break;
    case Clock_74HC595:
      return (_allPinStates & _clockPinMask)==_clockPinMask;
      break;
    case Latch_74HC595:
      return (_allPinStates & _latchPinMask)==_latchPinMask;
      break;
    case Reset_74HC595:
      return (_allPinStates & _resetPinMask)==_resetPinMask;
      break;
    case OutputEnable_74HC595:
      return (_allPinStates & _outputEnablePinMask)==_outputEnablePinMask;
      break;
    default:
      return false;
      break;
  }
};

__uint8_t BetterShiftRegControl::createPinUsageConfig(bool dataPin, bool clockPin, bool latchPin, bool outputenablePin, bool resetPin)
{
  return (_Clock_PinIDMask_*clockPin | _Data_PinIDMask_*dataPin | _Latch_PinIDMask_*latchPin | _Reset_PinIDMask_*resetPin | _OutputEnable_PinIDMask_*outputenablePin);
};


void BetterShiftRegControl::setPinID(PinNames_of_74HC595 pinSelect, __uint16_t input_PinID)
{
  switch(pinSelect)
  {
    case Clock_74HC595:
      this->_clockPinID = input_PinID;
      break;
    case Data_74HC595:
      this->_dataPinID = input_PinID;
      break;
    case Latch_74HC595:
      this->_latchPinID = input_PinID;
      break;
    case Reset_74HC595:
      this->_resetPinID = input_PinID;
      break;
    case OutputEnable_74HC595:
      this->_outputEnablePinID = input_PinID;
      break;
    default:
      break;
  }
};

__uint16_t BetterShiftRegControl::getPinID(PinNames_of_74HC595 pinSelect)
{
  __uint16_t getPinID = 0;
  switch(pinSelect)
  {
    case Clock_74HC595:
      getPinID = this->_clockPinID;
      break;
    case Data_74HC595:
      getPinID = this->_dataPinID;
      break;
    case Latch_74HC595:
      getPinID = this->_latchPinID;
      break;
    case Reset_74HC595:
      getPinID = this->_resetPinID;
      break;
    case OutputEnable_74HC595:
      getPinID = this->_outputEnablePinID;
      break;
    default:
      getPinID = 0;
      break;
  }
  return getPinID;
};

void BetterShiftRegControl::set_shift_register_outputs(__uint32_t registerSelect, __uint8_t newPinStates)
{
  this->_registerPinState[ registerSelect ] = newPinStates;
};




void BetterShiftRegControl::updateShiftRegister(ShiftOrder bitshiftorder)
{
  __uint16_t pinID_OE = getPinID((PinNames_of_74HC595)OutputEnable_74HC595);
  __uint16_t pinID_CLK = getPinID((PinNames_of_74HC595)Clock_74HC595);
  __uint16_t pinID_MR = getPinID((PinNames_of_74HC595)Reset_74HC595);
  __uint16_t pinID_LATCH = getPinID((PinNames_of_74HC595)Latch_74HC595);
  __uint16_t pinID_DS = getPinID((PinNames_of_74HC595)Data_74HC595);
  __uint8_t byteBuffer;
  registerPinWrite(pinID_CLK, LOW);
  registerPinWrite(pinID_OE, HIGH);//disable output of chip
  registerPinWrite(pinID_MR, HIGH);//keep Pin HIGH to not reset chip
  registerPinWrite(pinID_LATCH, LOW);//disable latch
  //reset Chip if possible
  registerPinWrite(pinID_LATCH, HIGH);//enable latch
  registerPinWrite(pinID_CLK, LOW);
  registerPinWrite(pinID_MR, LOW);
  registerPinWrite(pinID_CLK, HIGH);
  registerPinWrite(pinID_CLK, LOW);
  registerPinWrite(pinID_MR, HIGH);
  registerPinWrite(pinID_CLK, HIGH);
  registerPinWrite(pinID_LATCH, LOW);//disable latch
  //push data into chip
  registerPinWrite(pinID_LATCH, HIGH);//enable latch
  for (__uint32_t registerIndex = 0; registerIndex < _registerCount; registerIndex++)
  {
    byteBuffer = _registerPinState[ registerIndex ];
    //std::cout<<"registerIndex:"<< registerIndex <<std::endl;
    //std::cout<<"byteBuffer:"<< int8_to_binstr( byteBuffer ) <<std::endl;
    for (__uint8_t index = 0; index < 8; index++)
    {
      //std::cout<<"index:"<< (__uint32_t)index <<std::endl;
      __uint8_t bit_select_mask_LSB = 0b00000001<<index;
      __uint8_t bit_select_mask_MSB = 0b10000000>>index;

      //std::cout<<"bit_select_mask_LSB:"<< int8_to_binstr( bit_select_mask_LSB ) <<std::endl;
      //std::cout<<"bit_select_mask_MSB:"<< int8_to_binstr( bit_select_mask_MSB ) <<std::endl;
      bool dataBit_LSB = (byteBuffer & bit_select_mask_LSB)==(bit_select_mask_LSB);
      bool dataBit_MSB = (byteBuffer & bit_select_mask_MSB)==(bit_select_mask_MSB);
      bool dataBit;
      switch (bitshiftorder)
      {
        case LSB_FIRST:
          dataBit = dataBit_LSB;
          break;
        case MSB_FIRST:
          dataBit = dataBit_MSB;
          break;
        default:
          break;
      };
      registerPinWrite(pinID_CLK, LOW);
      registerPinWrite(pinID_DS, dataBit);
      registerPinWrite(pinID_CLK, HIGH);
    };
  };
  registerPinWrite(pinID_LATCH, LOW);//disable latch
  ;
  registerPinWrite(pinID_OE, LOW);//enable output of chip
};

void BetterShiftRegControl::setShiftOrder(ShiftOrder bitshiftorder)
{
  this->_DataShiftOrder = bitshiftorder;
};




