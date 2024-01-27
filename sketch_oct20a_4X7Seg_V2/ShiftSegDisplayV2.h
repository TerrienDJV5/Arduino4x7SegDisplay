//By Darrien Varrette
//ShiftSegDisplayV2.h




/* OLD
  ShiftSegDisplay.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ShiftSegDisplayV2_h
#define ShiftSegDisplayV2_h


#include "BitManipulate.h"

//#include "ShiftSegDisplayV2.cpp"

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
 


//typedef bitset<8> BYTE;
//typedef bitset<1> BOOLEAN;
enum BoolPinState {LOW = false, HIGH = true};
enum ShiftOrder {LSBFIRST, MSBFIRST};
enum PinModeOptions {OUTPUT, INPUT, INPUT_PULLUP};

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



union Data {
  std::byte b[2];
  int value;
};



class ShiftSegDisplay
{
  private:
    static const u_int8_t charInputLength = u_int8_t(11);//11
    const u_int8_t extraData4Input = u_int8_t{2};//2
    
    const std::byte segscreenBIN[20] = {
      //abcdefg-
      std::byte{0b11111100},//0
      std::byte{0b01100000},//1
      std::byte{0b11011010},//2
      std::byte{0b11110010},//3
      std::byte{0b01100110},//4
      std::byte{0b10110110},//5
      std::byte{0b10111110},//6
      std::byte{0b11100000},//7
      std::byte{0b11111110},//8
      std::byte{0b11110110},//9
      std::byte{0b11101110},//A
      std::byte{0b00111110},//B
      std::byte{0b10011100},//C
      std::byte{0b01111010},//D
      std::byte{0b10011110},//E
      std::byte{0b10001110},//F
      std::byte{0b00000000},//None
      std::byte{0b00000010},//-
      std::byte{0b00111010},//o
      std::byte{0b00001010},//r
    };
    char segscreenchar[21] = "0123456789AbCdEF -or";
    std::byte shiftByte0;
    std::byte shiftByte1;
    std::byte extraOutPutPins;
    void shiftOut(std::byte dataPin, std::byte clockPin, ShiftOrder bitOrder, u_int8_t dataIn);
    void writeShift2x(std::byte latchPin, std::byte dataPin, std::byte clockPin, std::byte shiftByte0, std::byte shiftByte1);
    void showL1L2L3Display(bool set_L1, bool set_L2, bool set_L3);
    void delay(float time)
    {
      std::cout<<"delay(" << time << ")"<<std::endl;
    };
  public:
    std::byte latchPin;//Pin connected to ST_CP of 74HC595
    std::byte clockPin;//Pin connected to SH_CP of 74HC595
    std::byte dataPin;//Pin connected to DS of 74HC595
    std::byte OutputEnablePin;//Pin connected to DS of 74HC595
    ShiftSegDisplay(u_int8_t latchPin, u_int8_t clockPin, u_int8_t dataPin, u_int8_t OutputEnablePin)
    {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->latchPin = (std::byte)latchPin;
      this->clockPin = (std::byte)clockPin;
      this->dataPin = (std::byte)dataPin;
      this->OutputEnablePin = (std::byte)OutputEnablePin;
    };
  	void showSimpleValue();
    
  	virtual void digitalPinWrite(std::byte selectPin, bool newState);
    /*
    {
      std::cout << "(Virtual Func) PIN#"<< selectPin <<":" << newState << std::endl;
    };
    */
    //virtual void delay(unsigned int);
  	
    //add Display Modes
  	//Normal
  	//Time
    //temperature C
    //temperature F
    //Normal HEX
    //add Used For The 3 Unused 74hc595 Pins
    void showSimpleValue(float numberIN , int delayrepeat);
    void showFromChar(char charInput[charInputLength] , int delayrepeat);
    void masterSetDisplay(std::byte inputDigits[4], bool set_DP_, std::byte set_DP_POS_, bool set_L1_, bool set_L2_, bool set_L3_, std::byte extraOutPutPins);
};







#endif



