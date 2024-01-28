//By Darrien Varrette
//BetterShiftRegControl.h


#ifndef BetterShiftRegControl_h
#define BetterShiftRegControl_h

//please refer to "~/Data sheets and References Images/74hc595_function.jpg"
//used to set what pins are connected when class is defined
#define IC_P_DS 0b00000001
#define IC_P_SH_CP 0b00000010
#define IC_P_ST_CP 0b00000100
#define IC_P_MR 0b00001000
#define IC_P_OE 0b00100000

#include "BitManipulate.h"


#include <bitset>
#include <cstddef>

#include <iostream>

#include <string.h>

#include <sstream>

/*
std::string int8_to_binstr(__uint8_t value)
{
  std::string output = "00000000";
  __uint8_t select_mask = 0b10000000;
  for (__uint8_t index = 0; index<=7; index++)
  {
    __uint8_t shifted_mask = (select_mask>>index);
    if ((value & shifted_mask)==shifted_mask){
      output[index] = '1';
    }else{
      output[index] = '0';
    }
  }
  return output;
}
//*/

union Data {
  __uint8_t b[2];
  int value;
};

//enum BoolPinState {LOW = false, HIGH = true};
#define LOW false
#define HIGH true
//enum PinModeOptions {OUTPUT, INPUT, INPUT_PULLUP};
enum ShiftOrder {LSB_FIRST, MSB_FIRST};
enum PinNames_of_74HC595 {
  Data_74HC595,
  Clock_74HC595,
  Latch_74HC595,
  Reset_74HC595,
  OutputEnable_74HC595,
};


class BetterShiftRegControl
{
  protected:
  private:
    /*<-- Flags -->*/

    bool flushed_to_registers = false; //flag that true if register input state has been flushed :: -> if false the phyical Pins where not updated to match chages made by the "_set_registerPinState" function.
    bool pin_Data_connected = false;
    bool pin_Clock_connected = false;
    bool pin_Latch_connected = false;
    bool pin_OutputEnable_connected = false;
    bool pin_Reset_connected = false;
    /*<-- variables -->*/

    ShiftOrder _DataShiftOrder;

    __uint16_t _dataPinID;//GPIO ID of Pin connected to DS of 74HC595
    __uint16_t _clockPinID;//GPIO ID of Pin connected to SH_CP of 74HC595
    __uint16_t _latchPinID;//GPIO ID of Pin connected to ST_CP of 74HC595
    __uint16_t _outputEnablePinID;//GPIO ID of Pin connected to OE of 74HC595
    __uint16_t _resetPinID;//GPIO ID of Pin connected to MR(SRCLR) of 74HC595
    bool _pinState_data = LOW;
    bool _pinState_clock = LOW;
    bool _pinState_latch = LOW;
    bool _pinState_output = LOW;//default
    bool _pinState_reset = HIGH;//default
    __uint8_t _allPinStates = 0x00;//state of registers inputs
    __uint8_t _Connected_Pins_Mask = 0x00;

    const static __uint8_t _dataPinMask = 0b00000001;//Pin connected to DS of 74HC595
    const static __uint8_t _clockPinMask = 0b00000010;//Pin connected to SH_CP of 74HC595
    const static __uint8_t _latchPinMask = 0b00000100;//Pin connected to ST_CP of 74HC595
    const static __uint8_t _outputEnablePinMask = 0b00001000;//Pin connected to OE of 74HC595
    const static __uint8_t _resetPinMask = 0b00010000;//Pin connected to MR(SRCLR) of 74HC595
    const static __uint8_t _BlankPinMask = 0b00000000;

    __uint8_t registerInputState = 0b00000;//only uses 5 bits
    __uint32_t _registerCount;//default 1
    __uint8_t *_registerPinState;//[registerCount]
    /*<-- functions -->*/

    void _init_BetterShiftRegisterControl_Private(__uint16_t register_init_count);
    void _init_registerPinState();
    void _set_registerPinState(PinNames_of_74HC595 pinSelect, bool newState);
    void _flush_registerPinState();
    bool _get_registerPinState(PinNames_of_74HC595 pinSelect);
  public:
    /*
    */
    BetterShiftRegControl(__uint16_t register_init_count, __uint8_t connected_Pins_mask);
    ~BetterShiftRegControl()
    {
      free(this->_registerPinState);
      this->_registerPinState = NULL;
    };

    enum _pinName2IDMaskList_enum {
      _Empty_PinIDMask_ = _BlankPinMask,
      _Clock_PinIDMask_ = _clockPinMask, 
      _Data_PinIDMask_ = _dataPinMask, 
      _Latch_PinIDMask_ = _latchPinMask, 
      _Reset_PinIDMask_ = _resetPinMask, 
      _OutputEnable_PinIDMask_ = _outputEnablePinMask, 
    };
    
    
    static __uint8_t createPinUsageConfig(bool dataPin, bool clockPin, bool latchPin, bool outputenablePin, bool resetPin);
    
    void setPinID(PinNames_of_74HC595 pinSelect, __uint16_t input_PinID);
    
    __uint16_t getPinID(PinNames_of_74HC595 pinSelect);
    
    void set_shift_register_outputs(__uint32_t registerSelect, __uint8_t newPinStates);
    
    void updateShiftRegister(ShiftOrder bitshiftorder);
    
    void setShiftOrder(ShiftOrder bitshiftorder);
    
    virtual void registerPinWrite(__uint16_t selectPinID, bool newState);
    /*
    {
      std::cout << "(Virtual Func) register_PIN:"<<"(ID:"<< selectPinID <<")" <<" == " << newState << std::endl;
    };
    //*/
    
};



#endif






