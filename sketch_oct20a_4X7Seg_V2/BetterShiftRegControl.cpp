//By Darrien Varrette
//BetterShiftRegControl.cpp

#include "BetterShiftRegControl.h"


BetterShiftRegControl::BetterShiftRegControl(__uint16_t register_init_count, __uint8_t connected_Pins_mask)
{
  this->_init_BetterShiftRegisterControl_Private(register_init_count);
  std::cout << "Data Pin: " << (connected_Pins_mask&IC_P_DS == IC_P_DS) << std::endl;
  std::cout << "Clock Pin: " << (connected_Pins_mask&IC_P_SH_CP == IC_P_SH_CP) << std::endl;
  std::cout << "Latch Pin: " << (connected_Pins_mask&IC_P_ST_CP == IC_P_ST_CP) << std::endl;
  std::cout << "Reset Pin: " << (connected_Pins_mask&IC_P_MR == IC_P_MR) << std::endl;
  std::cout << "OutputEnable Pin: " << (connected_Pins_mask&IC_P_OE==IC_P_OE) << std::endl;
  this->_Connected_Pins_Mask = connected_Pins_mask;
};


void BetterShiftRegControl::setupPinModes()
{
  if (this->_Connected_Pins_Mask&IC_P_DS)
  {
    this->pin_Data_connected = true;
    this->registerPinModeSet( this->getPinID(Data_74HC595), OUTPUT );
  };
  if (this->_Connected_Pins_Mask&IC_P_SH_CP)
  {
    this->pin_Clock_connected = true;
    this->registerPinModeSet( this->getPinID(Clock_74HC595), OUTPUT );
  };
  if (this->_Connected_Pins_Mask&IC_P_ST_CP)
  {
    this->pin_Latch_connected = true;
    this->registerPinModeSet( this->getPinID(Latch_74HC595), OUTPUT );
  };
  if (this->_Connected_Pins_Mask&IC_P_MR)
  {
    this->pin_Reset_connected = true;
    this->registerPinModeSet( this->getPinID(Reset_74HC595), OUTPUT );
  };
  if (this->_Connected_Pins_Mask&IC_P_OE)
  {
    this->pin_OutputEnable_connected = true;
    this->registerPinModeSet( this->getPinID(OutputEnable_74HC595), OUTPUT );
  };
  ;
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
  this->_registerPinState = (__uint8_t*)malloc( _registerCount*(sizeof(__uint8_t)) );
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
  //Serial.println("@BetterShiftRegControl::_flush_registerPinState");
  if (flushed_to_registers==false){
    __uint16_t pinID_OE = getPinID(OutputEnable_74HC595);
    __uint16_t pinID_CLK = getPinID(Clock_74HC595);
    __uint16_t pinID_MR = getPinID(Reset_74HC595);
    __uint16_t pinID_LATCH = getPinID(Latch_74HC595);
    __uint16_t pinID_DS = getPinID(Data_74HC595);
    if (pin_Clock_connected){
      registerPinWrite(pinID_CLK, _get_registerPinState(Clock_74HC595));
    };
    if (pin_OutputEnable_connected){
      registerPinWrite(pinID_OE, _get_registerPinState(OutputEnable_74HC595));
    };
    if (pin_Reset_connected){
      registerPinWrite(pinID_MR, _get_registerPinState(Reset_74HC595));
    };
    if (pin_Latch_connected){
      registerPinWrite(pinID_LATCH, _get_registerPinState(Latch_74HC595));
    };
    if (pin_Data_connected){
      registerPinWrite(pinID_DS, _get_registerPinState(Data_74HC595));
    };
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
  //Serial.println("@BetterShiftRegControl::set_shift_register_outputs");
  //Serial.println(registerSelect);
  //Serial.println(newPinStates,BIN);
  //Serial.println(this->_registerPinState[ registerSelect ],BIN);
  this->_registerPinState[ registerSelect ] = newPinStates;
  //Serial.println(this->_registerPinState[ registerSelect ],BIN);
};




void BetterShiftRegControl::updateShiftRegister(__uint8_t bitshiftorder)
{
  //__uint16_t pinID_OE = getPinID((PinNames_of_74HC595)OutputEnable_74HC595);
  //__uint16_t pinID_CLK = getPinID((PinNames_of_74HC595)Clock_74HC595);
  //__uint16_t pinID_MR = getPinID((PinNames_of_74HC595)Reset_74HC595);
  //__uint16_t pinID_LATCH = getPinID((PinNames_of_74HC595)Latch_74HC595);
  //__uint16_t pinID_DS = getPinID((PinNames_of_74HC595)Data_74HC595);
  __uint8_t byteBuffer;
  this->_flush_registerPinState();
  _set_registerPinState(Clock_74HC595, LOW);
  _set_registerPinState(OutputEnable_74HC595, HIGH);//disable output of chip
  _set_registerPinState(Reset_74HC595, HIGH);//keep Pin HIGH to not reset chip
  _set_registerPinState(Latch_74HC595, HIGH);//disable latch
  this->_flush_registerPinState();
  //reset Chip if possible
  _set_registerPinState(Clock_74HC595, LOW);
  this->_flush_registerPinState();
  _set_registerPinState(Reset_74HC595, LOW);
  this->_flush_registerPinState();
  _set_registerPinState(Clock_74HC595, HIGH);
  this->_flush_registerPinState();
  _set_registerPinState(Clock_74HC595, LOW);
  this->_flush_registerPinState();
  _set_registerPinState(Reset_74HC595, HIGH);
  this->_flush_registerPinState();
  _set_registerPinState(Clock_74HC595, HIGH);
  this->_flush_registerPinState();
  _set_registerPinState(Latch_74HC595, HIGH);//disable latch
  this->_flush_registerPinState();
  //push data into chip
  _set_registerPinState(Latch_74HC595, LOW);//enable latch
  this->_flush_registerPinState();
  for (__uint32_t registerIndex = 0; registerIndex < _registerCount; registerIndex++)
  {
    byteBuffer = _registerPinState[ _registerCount - 1 - registerIndex ];
    //std::cout<<"registerIndex:"<< registerIndex <<std::endl;
    //std::cout<<"byteBuffer:"<< int8_to_binstr( byteBuffer ) <<std::endl;
    for (__uint8_t index = 0; index <= 7; index++)
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
        case LSBFIRST:
          dataBit = dataBit_LSB;
          break;
        case MSBFIRST:
          dataBit = dataBit_MSB;
          break;
        default:
          break;
      };
      
      
      _set_registerPinState(Data_74HC595, dataBit);
      this->_flush_registerPinState();
      _set_registerPinState(Clock_74HC595, HIGH);
      this->_flush_registerPinState();
      _set_registerPinState(Clock_74HC595, LOW);
      this->_flush_registerPinState();
    };
  };
  _set_registerPinState(Latch_74HC595, HIGH);//disable latch
  this->_flush_registerPinState();
  ;
  _set_registerPinState(Clock_74HC595, LOW);
  _set_registerPinState(Reset_74HC595, HIGH);
  _set_registerPinState(OutputEnable_74HC595, LOW);//enable output of chip
  this->_flush_registerPinState();
};

void BetterShiftRegControl::setShiftOrder(__uint8_t bitshiftorder)
{
  this->_DataShiftOrder = bitshiftorder;
};

void BetterShiftRegControl::update()
{
  this->updateShiftRegister( this->_DataShiftOrder );
};



/*
###################################################################################
###################################################################################
###################################################################################
###################################################################################
###################################################################################
*/

void BetterShiftRegControl::registerPinWrite(__uint16_t selectPinID, bool newState)
{
  digitalWrite( selectPinID, newState);
};
__uint8_t BetterShiftRegControl::registerPinRead( __uint16_t selectPinID )
{
  return digitalRead( selectPinID );
};
void BetterShiftRegControl::registerPinModeSet( __uint8_t selectPinID, __uint8_t newMode )
{
  pinMode(selectPinID, newMode);
};
    

/*
base code layout Copyed from Arduino Source code
source: https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/wiring_shift.c
*/

uint8_t BetterShiftRegControl::shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		this->registerPinWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST)
			value |= this->registerPinRead(dataPin) << i;
		else
			value |= this->registerPinRead(dataPin) << (7 - i);
		this->registerPinWrite(clockPin, LOW);
	}
	return value;
}

void BetterShiftRegControl::shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST) {
			this->registerPinWrite(dataPin, val & 1);
			val >>= 1;
		} else {	
			this->registerPinWrite(dataPin, (val & 128) != 0);
			val <<= 1;
		}
			
		this->registerPinWrite(clockPin, HIGH);
		this->registerPinWrite(clockPin, LOW);		
	}
}

