//By Darrien Varrette
//BetterShiftRegisterControl.h


#ifndef BetterShiftRegisterControl_h
#define BetterShiftRegisterControl_h
#include "BitManipulate.h"


//typedef bitset<8> BYTE;
//typedef bitset<1> BOOLEAN;
enum BoolPinState {LOW = false, HIGH = true};

//enum PinModeOptions {OUTPUT, INPUT, INPUT_PULLUP};


#include <bitset>
#include <cstddef>

#include <iostream>
std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}

#include <string.h>

#include <sstream>

std::string int8_to_binstr(u_int8_t value)
{
  std::string output = "00000000";
  u_int8_t select_mask = 0b10000000;
  for (u_int8_t index = 0; index<=7; index++)
  {
    u_int8_t shifted_mask = (select_mask>>index);
    if ((value & shifted_mask)==shifted_mask){
      output[index] = '1';
    }else{
      output[index] = '0';
    }
  }
  return output;
}


union Data {
  std::byte b[2];
  int value;
};

enum ShiftOrder {LSBFIRST, MSBFIRST};
enum PinNames_of_74HC595 {
  Data_74HC595, 
  Clock_74HC595, 
  Latch_74HC595, 
  Reset_74HC595, 
  OutputEnable_74HC595, 
};



class BetterShiftRegisterControl
{
  private:
    bool pin_Data_connected = false;
    bool pin_Clock_connected = false;
    bool pin_Latch_connected = false;
    bool pin_OutputEnable_connected = false;
    bool pin_Reset_connected = false;
    
    
    u_int16_t _dataPinID;//GPIO ID of Pin connected to DS of 74HC595
    u_int16_t _clockPinID;//GPIO ID of Pin connected to SH_CP of 74HC595
    u_int16_t _latchPinID;//GPIO ID of Pin connected to ST_CP of 74HC595
    u_int16_t _outputEnablePinID;//GPIO ID of Pin connected to OE of 74HC595
    u_int16_t _resetPinID;//GPIO ID of Pin connected to MR(SRCLR) of 74HC595
    bool _pinState_data = LOW;
    bool _pinState_clock = LOW;
    bool _pinState_latch = LOW;
    bool _pinState_output = LOW;//default
    bool _pinState_reset = HIGH;//default
    u_int8_t _allPinStates = 0x00;
    u_int8_t _Connected_Pins_Mask = 0x00;

    const static u_int8_t _dataPinMask = 0b00000001;//Pin connected to DS of 74HC595
    const static u_int8_t _clockPinMask = 0b00000010;//Pin connected to SH_CP of 74HC595
    const static u_int8_t _latchPinMask = 0b00000100;//Pin connected to ST_CP of 74HC595
    const static u_int8_t _outputEnablePinMask = 0b00001000;//Pin connected to OE of 74HC595
    const static u_int8_t _resetPinMask = 0b00010000;//Pin connected to MR(SRCLR) of 74HC595
    const static u_int8_t _BlankPinMask = 0b00000000;

    
    u_int32_t _registerCount;//default 1
    u_int8_t *_registerPinState;//[registerCount]
    void _init_BetterShiftRegisterControl_Private(u_int16_t register_init_count)
    {
      this->_registerCount = register_init_count;
      _init_registerPinState();
      _set_registerPinState((PinNames_of_74HC595)Data_74HC595, LOW);
      _set_registerPinState((PinNames_of_74HC595)Clock_74HC595, LOW);
      _set_registerPinState((PinNames_of_74HC595)Latch_74HC595, LOW);
      _set_registerPinState((PinNames_of_74HC595)Reset_74HC595, HIGH);
      _set_registerPinState((PinNames_of_74HC595)OutputEnable_74HC595, LOW);
    };
    void _init_registerPinState()
    {
      this->_registerPinState = (u_int8_t*)malloc( _registerCount );
    };
    void _set_registerPinState(PinNames_of_74HC595 pinSelect, bool newState)
    {
      _pinName2IDMaskList_enum pinSelectMask;
      switch (pinSelect)
      {
        case (PinNames_of_74HC595)Data_74HC595:
          pinSelectMask = (_pinName2IDMaskList_enum)_Data_PinIDMask_;
          this->_allPinStates = (_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
          break;
        case (PinNames_of_74HC595)Clock_74HC595:
          pinSelectMask = (_pinName2IDMaskList_enum)_Clock_PinIDMask_;
          this->_allPinStates = (_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
          break;
        case (PinNames_of_74HC595)Latch_74HC595:
          pinSelectMask = (_pinName2IDMaskList_enum)_Latch_PinIDMask_;
          this->_allPinStates = (_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
          break;
        case (PinNames_of_74HC595)Reset_74HC595:
          pinSelectMask = (_pinName2IDMaskList_enum)_Reset_PinIDMask_;
          this->_allPinStates = (_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
          break;
        case (PinNames_of_74HC595)OutputEnable_74HC595:
          pinSelectMask = (_pinName2IDMaskList_enum)_OutputEnable_PinIDMask_;
          this->_allPinStates = (_allPinStates & ~pinSelectMask) | ( pinSelectMask * newState );
          break;
        default:
          break;
      };
    };
  public:
    enum _pinName2IDMaskList_enum {
      _Empty_PinIDMask_ = _BlankPinMask,
      _Clock_PinIDMask_ = _clockPinMask, 
      _Data_PinIDMask_ = _dataPinMask, 
      _Latch_PinIDMask_ = _latchPinMask, 
      _Reset_PinIDMask_ = _resetPinMask, 
      _OutputEnable_PinIDMask_ = _outputEnablePinMask, 
    };
    BetterShiftRegisterControl(u_int16_t register_init_count, _pinName2IDMaskList_enum connected_Pins[5])
    {
      _init_BetterShiftRegisterControl_Private(register_init_count);
      std::cout << connected_Pins[0] << std::endl;
      std::cout << connected_Pins[1] << std::endl;
      std::cout << connected_Pins[2] << std::endl;
      std::cout << connected_Pins[3] << std::endl;
      std::cout << connected_Pins[4] << std::endl;
    }
    static u_int8_t createPinUsageConfig(bool dataPin, bool clockPin, bool latchPin, bool outputenablePin, bool resetPin);
    
    void setPinID(PinNames_of_74HC595 pinSelect, u_int16_t input_PinID);
    u_int16_t getPinID(PinNames_of_74HC595 pinSelect);

    void set_shift_register_outputs(u_int32_t registerSelect, u_int8_t newPinStates)
    {
      this->_registerPinState[ registerSelect ] = newPinStates;
    };
    void updateShiftRegister(ShiftOrder bitshiftorder)
    {
      volatile u_int16_t pinID_OE = getPinID((PinNames_of_74HC595)OutputEnable_74HC595);
      volatile u_int16_t pinID_CLK = getPinID((PinNames_of_74HC595)Clock_74HC595);
      volatile u_int16_t pinID_MR = getPinID((PinNames_of_74HC595)Reset_74HC595);
      volatile u_int16_t pinID_LATCH = getPinID((PinNames_of_74HC595)Latch_74HC595);
      volatile u_int16_t pinID_DS = getPinID((PinNames_of_74HC595)Data_74HC595);
      volatile u_int8_t byteBuffer;
      registerPinWrite((std::byte)pinID_CLK, LOW);
      registerPinWrite((std::byte)pinID_OE, HIGH);//disable output of chip
      registerPinWrite((std::byte)pinID_MR, HIGH);//keep Pin HIGH to not reset chip
      registerPinWrite((std::byte)pinID_LATCH, LOW);//disable latch
      //reset Chip if possible
      registerPinWrite((std::byte)pinID_LATCH, HIGH);//enable latch
      registerPinWrite((std::byte)pinID_CLK, LOW);
      registerPinWrite((std::byte)pinID_MR, LOW);
      registerPinWrite((std::byte)pinID_CLK, HIGH);
      registerPinWrite((std::byte)pinID_CLK, LOW);
      registerPinWrite((std::byte)pinID_MR, HIGH);
      registerPinWrite((std::byte)pinID_CLK, HIGH);
      registerPinWrite((std::byte)pinID_LATCH, LOW);//disable latch
      //push data into chip
      registerPinWrite((std::byte)pinID_LATCH, HIGH);//enable latch
      for (u_int32_t registerIndex = 0; registerIndex < _registerCount; registerIndex++)
      {
        byteBuffer = _registerPinState[ registerIndex ];
        //std::cout<<"registerIndex:"<< registerIndex <<std::endl;
        //std::cout<<"byteBuffer:"<< int8_to_binstr( byteBuffer ) <<std::endl;
        for (u_int8_t index = 0; index < 8; index++)
        {
          //std::cout<<"index:"<< (u_int32_t)index <<std::endl;
          u_int8_t bit_select_mask_LSB = 0b00000001<<index;
          u_int8_t bit_select_mask_MSB = 0b10000000>>index;
          
          //std::cout<<"bit_select_mask_LSB:"<< int8_to_binstr( bit_select_mask_LSB ) <<std::endl;
          //std::cout<<"bit_select_mask_MSB:"<< int8_to_binstr( bit_select_mask_MSB ) <<std::endl;
          volatile bool dataBit_LSB = (byteBuffer & bit_select_mask_LSB)==(bit_select_mask_LSB);
          volatile bool dataBit_MSB = (byteBuffer & bit_select_mask_MSB)==(bit_select_mask_MSB);
          volatile bool dataBit;
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
          registerPinWrite((std::byte)pinID_CLK, LOW);
          registerPinWrite((std::byte)pinID_DS, dataBit);
          registerPinWrite((std::byte)pinID_CLK, HIGH);
        };
      };
      registerPinWrite((std::byte)pinID_LATCH, LOW);//disable latch
      ;
      registerPinWrite((std::byte)pinID_OE, LOW);//enable output of chip
    };


    virtual void registerPinWrite(std::byte selectPinID, bool newState);
    /*
    {
      std::cout << "(Virtual Func) register_PIN:"<<"(ID:"<< selectPinID <<")" <<" == " << newState << std::endl;
    };
    */
};



#endif






