//By Darrien Varrette
//ShiftSegDisplayV2.h



/* OLD
  ShiftSegDisplay.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ShiftSegDisplayV2_h
#define ShiftSegDisplayV2_h

#include "Arduino.h"//used for pin control
#include "BitManipulate.h"
#include "BetterShiftRegControl.h"//intagrate this

//typedef bitset<8> BYTE;
//typedef bitset<1> BOOLEAN;

//enum BoolPinState {LOW = false, HIGH = true};
//enum ShiftOrder {LSBFIRST, MSBFIRST};
#define INPUT 0x01
#define INPUT_PULLUP 0x05
#define INPUT_PULLDOWN 0x09
#define OUTPUT 0x03
#define OUTPUT_OPEN_DRAIN 0x13

//enum PinModeOptions {OUTPUT, INPUT, INPUT_PULLUP};

//#include "Arduino.h"

//add Display Modes
//  displayMode(0) = Normal
//  displayMode(1) = Time
//  displayMode(2) = temperature C
//  displayMode(3) = temperature F
//  displayMode(4) = Normal HEX
//add Used For The 3 Unused 74hc595 Pins

/*
  //used pins are 0b00101111 
  unsigned int j = 0b1111110000101010;//2 bytes(16-bit)
  //ground latchPin and hold low for as long as you are transmitting
  digitalWrite(latchPinT, LOW);
  shiftOut(dataPinT, clockPinT, LSBFIRST, j);//LSBFIRST , MSBFIRST
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalWrite(latchPinT, HIGH);
*/





//##|Connection
//01|Common Cathode Digit 1
//02|Common Cathode Digit 2
//03|Anode D
//04|Common Cathode Digit L1,L2,L3
//05|Anode E
//06|Common Cathode Digit 3
//07|Anode DP
//08|Common Cathode Digit 4
//09|NO Connection
//10|No Pin
//11|Anode F
//12|No Pin
//13|Anode C, L3
//14|Anode A, L1
//15|Anode G
//16|Anode B, L2

//000|111|22|33333333|44|555|666|777|  |   |   |88|   |9999| 10 |11| 12 |
//CD1|CD2|AD|CDL1L2L3|AE|CD3|ADP|CD4|  |NOC|NOP|AF|NOP|ACL3|AAL1|AG|ABL2|




class ShiftSegDisplay
{
  protected:
  private:
    bool pinModes_Setup = false;
    //(IC_P_DS|IC_P_SH_CP|IC_P_ST_CP)|(IC_P_MR)|(IC_P_OE)
    /*
    usablePins:
    IC_P_DS = DS of 74HC595
    IC_P_SH_CP = SH_CP of 74HC595
    IC_P_ST_CP = ST_CP of 74HC595
    IC_P_MR = MR of 74HC595
    IC_P_OE = OE of 74HC595
    */
    uint8_t _usablePins;
    BetterShiftRegControl *registerSIPO;
    static const u_int8_t charInputLength = 11;//11
    const u_int8_t extraData4Input = 2;//2
    
    const __uint8_t segscreenBIN[20] = {
      //abcdefg-
      __uint8_t{0b11111100},//0
      __uint8_t{0b01100000},//1
      __uint8_t{0b11011010},//2
      __uint8_t{0b11110010},//3
      __uint8_t{0b01100110},//4
      __uint8_t{0b10110110},//5
      __uint8_t{0b10111110},//6
      __uint8_t{0b11100000},//7
      __uint8_t{0b11111110},//8
      __uint8_t{0b11110110},//9
      __uint8_t{0b11101110},//A
      __uint8_t{0b00111110},//B
      __uint8_t{0b10011100},//C
      __uint8_t{0b01111010},//D
      __uint8_t{0b10011110},//E
      __uint8_t{0b10001110},//F
      __uint8_t{0b00000000},//None
      __uint8_t{0b00000010},//-
      __uint8_t{0b00111010},//o
      __uint8_t{0b00001010},//r
    };
    char segscreenchar[21] = "0123456789AbCdEF -or";
    __uint8_t shiftByte0;
    __uint8_t shiftByte1;
    __uint8_t extraOutPutPins;
    void shiftOut(__uint8_t dataPin, __uint8_t clockPin, ShiftOrder bitOrder, u_int8_t dataIn);
    void writeShift2x(__uint8_t latchPin, __uint8_t dataPin, __uint8_t clockPin, __uint8_t shiftByte0, __uint8_t shiftByte1);
    void showL1L2L3Display(bool set_L1, bool set_L2, bool set_L3);
    void init();
  public:
    __uint8_t latchPin;//Pin connected to ST_CP of 74HC595
    __uint8_t clockPin;//Pin connected to SH_CP of 74HC595
    __uint8_t dataPin;//Pin connected to DS of 74HC595
    __uint8_t resetPin;//Pin connected to MR of 74HC595
    __uint8_t outputEnablePin;//Pin connected to OE of 74HC595
    ShiftSegDisplay(__uint8_t dataPin, __uint8_t clockPin, __uint8_t latchPin, __uint8_t outputEnablePin)
    {
      this->_usablePins = (IC_P_DS|IC_P_SH_CP|IC_P_ST_CP|IC_P_OE);
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->latchPin = latchPin;
      this->clockPin = clockPin;
      this->dataPin = dataPin;
      this->outputEnablePin = outputEnablePin;
      this->init();
    };
    ~ShiftSegDisplay()
    {
      delete this->registerSIPO;
    }
  	void begin();
    
  	virtual void digitalPinWrite(__uint8_t selectPin, bool newState);
    virtual void hiddenPinMode(__uint8_t selectPin, __uint8_t newMode);
  	
    
    void showSimpleValue(float numberIN , int delayrepeat);
    void showFromChar(char charInput[charInputLength] , int delayrepeat);
    void masterSetDisplay(__uint8_t inputDigits[4], bool set_DP_, __uint8_t set_DP_POS_, bool set_L1_, bool set_L2_, bool set_L3_, __uint8_t extraOutPutPins);
};







#endif



