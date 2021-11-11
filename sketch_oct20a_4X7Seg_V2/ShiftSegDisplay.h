//By Darrien Varrette

/*
  ShiftSegDisplay.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ShiftSegDisplay_h
#define ShiftSegDisplay_h

#include "Arduino.h"

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
  byte b[2];
  int value;
};



class ShiftSegDisplay
{
  private:
    byte latchPin;//Pin connected to ST_CP of 74HC595
    byte clockPin;//Pin connected to SH_CP of 74HC595
    byte dataPin;//Pin connected to DS of 74HC595
    static const byte charInputLength = 11;
    const byte extraData4Input = 2;
    
    const byte segscreenBIN[18] = {
      //abcdefg-
      0b11111100,//0
      0b01100000,//1
      0b11011010,//2
      0b11110010,//3
      0b01100110,//4
      0b10110110,//5
      0b10111110,//6
      0b11100000,//7
      0b11111110,//8
      0b11110110,//9
      0b11101110,//A
      0b00111110,//B
      0b10011100,//C
      0b01111010,//D
      0b10011110,//E
      0b10001110,//F
      0b00000000,//None
      0b00000010,//-
    };
    char segscreenchar[18] = "0123456789AbCdEF ";
    byte shiftByte0;
    byte shiftByte1;
    byte extraOutPutPins;
    void writeShift2x(byte latchPin, byte dataPin, byte clockPin, byte shiftByte0, byte shiftByte1){
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, shiftByte1);//LSBFIRST , MSBFIRST //Used 0bAAAAANNN
      shiftOut(dataPin, clockPin, LSBFIRST, shiftByte0);//LSBFIRST , MSBFIRST //Used 0bCCACACAC
      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
    };
    void showDPDisplay(byte set_DP_POS){//Is Now Unused!
      shiftByte0 = 0b00000000;// //Used 0bCCACACAC
      shiftByte1 = 0b00000000;// //Used 0bAAAAANNN
      bitWrite(shiftByte1, 7-(2), LOW);//A L1
      bitWrite(shiftByte1, 7-(4), LOW);//B L2
      bitWrite(shiftByte1, 7-(1), LOW);//C L3
      bitWrite(shiftByte0, 7-(2), LOW);//D
      bitWrite(shiftByte0, 7-(4), LOW);//E
      bitWrite(shiftByte1, 7-(0), LOW);//F
      bitWrite(shiftByte1, 7-(3), LOW);//G
      bitWrite(shiftByte0, 7-(6), HIGH);//DP
      
      bitWrite(shiftByte0, 7-(0), !bitRead(set_DP_POS, 3-(0)));//CD1 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(1), !bitRead(set_DP_POS, 3-(1)));//CD2 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(3), LOW);//CDL1L2L3 //keep LOW if CD1|CD2|CD3|CD4 are HIGH
      bitWrite(shiftByte0, 7-(5), !bitRead(set_DP_POS, 3-(2)));//CD3 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(7), !bitRead(set_DP_POS, 3-(3)));//CD4 //keep LOW if CDL1L2L3 is HIGH
      writeShift2x(latchPin, dataPin, clockPin, shiftByte0, shiftByte1|extraOutPutPins);
      delay(1);
    };
    void showL1L2L3Display(boolean set_L1, boolean set_L2, boolean set_L3){
      shiftByte0 = 0b00000000;// //Used 0bCCACACAC
      shiftByte1 = 0b00000000;// //Used 0bAAAAANNN
      bitWrite(shiftByte1, 7-(2), set_L1);//A L1
      bitWrite(shiftByte1, 7-(4), set_L2);//B L2
      bitWrite(shiftByte1, 7-(1), set_L3);//C L3
      
      bitWrite(shiftByte0, 7-(0), HIGH);//CD1 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(1), HIGH);//CD2 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(3), LOW);//CDL1L2L3 //keep LOW if CD1|CD2|CD3|CD4 are HIGH
      bitWrite(shiftByte0, 7-(5), HIGH);//CD3 //keep LOW if CDL1L2L3 is HIGH
      bitWrite(shiftByte0, 7-(7), HIGH);//CD4 //keep LOW if CDL1L2L3 is HIGH
      writeShift2x(latchPin, dataPin, clockPin, shiftByte0, shiftByte1|extraOutPutPins);
      delay(1);
    };
    byte int2array(int numbin, byte (& myarray)[4]) {
      byte num3 = numbin % 10;
      byte num2 = ((numbin - num3) / 10) % 10;
      byte num1 = ((numbin - num3 - num2) / 100) % 10;
      byte num0 = ((numbin - num3 - num2 - num1) / 1000) % 10;
      myarray[0] = num0;
      myarray[1] = num1;
      myarray[2] = num2;
      myarray[3] = num3;
    };
  public:
    void showSimpleValue();
    ShiftSegDisplay(byte latchPin, byte clockPin, byte dataPin) {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->latchPin = latchPin;
      this->clockPin = clockPin;
      this->dataPin = dataPin;
      init();
    };
    void init() {
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
      // Always try to avoid duplicate code.
    };
    
    
    
    
    //add Display Modes
    //Normal
    //Time
    //temperature C
    //temperature F
    //Normal HEX
    //add Used For The 3 Unused 74hc595 Pins
    void showSimpleValue(float numberIN , int delayrepeat=0){
      char modeSet[3] = ":'";
      byte cstrLength = (charInputLength-extraData4Input);
      char cstr[cstrLength];
      char cstrNew[cstrLength];
      double doubleNumber = double(numberIN);

      //i need to add leading spaces for INT Mode
      //for cleaner look
      if (int(numberIN)==numberIN){
        itoa(numberIN, cstr, cstrLength);
      }
      else{
        dtostrf(doubleNumber, cstrLength ,3 ,cstr);
      };
      
      byte i2 = 0;
      for (byte i=0; i<=cstrLength; i++){
        if (cstr[i]==' '){
          continue;
        };
        if (cstr[i]=='.'){
          cstrNew[i2-1] = cstr[i];
        }
        else {
          cstrNew[i2] = cstr[i];
          cstrNew[i2+1] = ' ';
          i2=i2+2;
        };
        if (not(i2<=cstrLength-1)){
          break;
        };
      };
      Serial.println(cstr);
      Serial.println(cstrNew);
      char charInput[charInputLength] = "          ";// = "-.8.5.1.:'";//SDSDSDSD {L1L2} L3
      for (byte i=0; i<=sizeof(cstrNew)-1; i++){
        charInput[i] = cstrNew[i];
      };
      for (byte i=0; i<=sizeof(modeSet)-1; i++){
        charInput[i+sizeof(cstrNew)-1] = modeSet[i];
      };
      Serial.println(charInput);
      showFromChar(charInput , delayrepeat);
    };
    
    void showFromChar(char charInput[charInputLength] , int delayrepeat=0){
      //charInput = "-.8.5.1.:'";//SDSDSDSD {L1L2} L3
      // { |.|*|:}
      char modeL1L2[5] = " .*:";
      // { |'}
      char modeL3[3] = " '";
      // {0|1|2|3|4|5|6|7|8|9|A|b|C|d|E|F| |-}
      char modeSeg[19] = "0123456789AbCdEF -";
      // { |.}
      char modeDec[3] = " .";
      boolean set_DP = (charInput[1]==modeDec[1]|charInput[3]==modeDec[1] | charInput[5]==modeDec[1] | charInput[7]==modeDec[1]);//TrueHIGH , FalseLOW
      boolean set_L1 = (charInput[7]==modeL1L2[1])|(charInput[7]==modeL1L2[3]);//TrueHIGH , FalseLOW
      boolean set_L2 = (charInput[7]==modeL1L2[2])|(charInput[7]==modeL1L2[3]);//TrueHIGH , FalseLOW
      boolean set_L3 = (charInput[8]==modeL3[1]);//TrueHIGH , FalseLOW  //Used for temperature
      byte set_DP_POS = 0b0000;
      bitWrite(set_DP_POS, 3 , (charInput[1]==modeDec[1]));
      bitWrite(set_DP_POS, 2 , (charInput[3]==modeDec[1]));
      bitWrite(set_DP_POS, 1 , (charInput[5]==modeDec[1]));
      bitWrite(set_DP_POS, 0 , (charInput[7]==modeDec[1]));
      byte numb[4] = {0, 0, 0, 0};
      for (unsigned int i=0; i<=sizeof(modeSeg)-1; i++){
        if (charInput[0]==modeSeg[i]){
          numb[0] = i;
        };
        if (charInput[2]==modeSeg[i]){
          numb[1] = i;
        };
        if (charInput[4]==modeSeg[i]){
          numb[2] = i;
        };
        if (charInput[6]==modeSeg[i]){
          numb[3] = i;
        };
      };
      
      
      byte set_extraPins = 0b000;//LOW,LOW,LOW
      for (int i = 0; i <= delayrepeat; i++) {
        masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
      };
    };
    
    
    void showNormal(float numberIN, int delayrepeat=0){//Will Not Be Used!(bad method)
      boolean set_DP = LOW;//TrueHIGH , FalseLOW
      boolean set_L1 = LOW;//TrueHIGH , FalseLOW
      boolean set_L2 = LOW;//TrueHIGH , FalseLOW
      boolean set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      byte set_DP_POS = 0b0000;
      
      int intPVal = int(numberIN);
      /*
      Serial.print("Float numberIN: ");
      Serial.println(numberIN);
      Serial.print("intPVal: ");
      Serial.println(intPVal);
      Serial.print("decPVal: ");
      Serial.println(decPVal);
      */
      
      byte numbINT[4] = {0, 0, 0, 0};
      int2array(intPVal, numbINT);
      
      byte numb[4] = {0, 0, 0, 0};
      byte cit = 0;
      for (int occ = 0; occ <= 3-1; occ++) {
        if (numbINT[occ]==0){
          cit+=1;
        }else{break;};
      };
      
      set_DP_POS = 0b0000;
      
      boolean clearMyZero = false;
      int cZ_INT = 0;
      for (int occ = 0; occ <= 2; occ++) {
        if ((!clearMyZero)&(numbINT[occ]==0)){
          numbINT[occ] = 16;
          cZ_INT += 1;
        }
        else {
          clearMyZero = true;
        }
        numb[occ] = numbINT[occ];
      };
      //Serial.println("showNormal");
      for (int occ = 0; occ <= 3; occ++) {
        numb[occ] = numbINT[occ];
      }
      //Normal
      set_L1 = LOW;//TrueHIGH , FalseLOW
      set_L2 = LOW;//TrueHIGH , FalseLOW
      set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      
      byte set_extraPins = 0b000;//LOW,LOW,LOW
      for (int i = 0; i <= delayrepeat; i++) {
        masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
      };
    };
    void showFloat(float numberIN, int delayrepeat=0){//Will Not Be Used!(bad method)
      //not working
      boolean set_DP = HIGH;//TrueHIGH , FalseLOW
      boolean set_L1 = LOW;//TrueHIGH , FalseLOW
      boolean set_L2 = LOW;//TrueHIGH , FalseLOW
      boolean set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      byte set_DP_POS = 0b0000;
      int intPVal = int(numberIN);
      int decPVal = int((numberIN*10000 - intPVal*10000));
      byte numbINT[4] = {0, 0, 0, 0};
      byte numbDEC[4] = {0, 0, 0, 0};
      int2array(decPVal, numbDEC);
      int2array(intPVal, numbINT);
      byte numb[4] = {0, 0, 0, 0};
      byte cit = 0;
      for (int occ = 0; occ <= 3-1; occ++) {
        if (numbINT[occ]==0){
          cit+=1;
        }else{break;};
      };


      
      boolean clearMyZero = false;
      int cZ_INT = 0;
      for (int occ = 0; occ <= 3; occ++) {
        if ((!clearMyZero)&(numbINT[occ]==0)){
          numbINT[occ] = 16;
          cZ_INT += 1;
        }
        else {
          clearMyZero = true;
        }
      };
      int cZ_DEC = 0;
      for (int occ = 0; occ <= (3-cZ_INT); occ++) {
        int occ1 = cZ_INT + occ;
        numb[occ] = numbINT[occ1];
      };
      for (int occ = 0; occ <= 3-(3-cZ_INT); occ++) {
        numb[occ + (3-cZ_INT)+1] = numbDEC[occ];
      };
      
      set_DP_POS = 0b0000;
      bitWrite(set_DP_POS, (cZ_INT), HIGH);
      if (decPVal==0){set_DP = LOW;};
      //Normal
      set_L1 = LOW;//TrueHIGH , FalseLOW
      set_L2 = LOW;//TrueHIGH , FalseLOW
      set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      
      byte set_extraPins = 0b000;//LOW,LOW,LOW
      for (int i = 0; i <= delayrepeat; i++) {
        masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
      };
    };
    void showAsTime(float numberIN_0, float numberIN_1, int delayrepeat=0){//Will Not Be Used!(bad method)
      //not working
      boolean set_DP = HIGH;//TrueHIGH , FalseLOW
      boolean set_L1 = HIGH;//TrueHIGH , FalseLOW
      boolean set_L2 = HIGH;//TrueHIGH , FalseLOW
      boolean set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      byte set_DP_POS = 0b0000;
      int intPVal_0 = int(numberIN_0);
      int decPVal_0 = int((numberIN_0*10000 - intPVal_0*10000));
      int intPVal_1 = int(numberIN_1);
      int decPVal_1 = int((numberIN_1*10000 - intPVal_1*10000));
      byte numbINT_0[4] = {0, 0, 0, 0};
      byte numbDEC_0[4] = {0, 0, 0, 0};
      int2array(decPVal_0, numbDEC_0);
      int2array(intPVal_0, numbINT_0);
      byte numbINT_1[4] = {0, 0, 0, 0};
      byte numbDEC_1[4] = {0, 0, 0, 0};
      int2array(decPVal_1, numbDEC_1);
      int2array(intPVal_1, numbINT_1);
      
      byte numb_0[2] = {0, 0};
      byte numb_1[2] = {0, 0};
      byte cit_0 = 0;
      byte cit_1 = 0;
      for (int occ = 0; occ <= 1; occ++) {
        if (numbINT_0[occ]==0){
          cit_0+=1;
        }else{break;};
      };
      for (int occ = 0; occ <= 1; occ++) {
        if (numbINT_1[occ]==0){
          cit_1+=1;
        }else{break;};
      };


      
      boolean clearMyZero = false;
      int cZ_INT_0 = 0;
      for (int occ = 0; occ <= 3; occ++) {
        if ((!clearMyZero)&(numbINT_0[occ]==0)){
          numbINT_0[occ] = 16;
          cZ_INT_0 += 1;
        }
        else {
          clearMyZero = true;
        }
      };
      int cZ_DEC_0 = 0;
      for (int occ = 0; occ <= (3-cZ_INT_0); occ++) {
        int occ1 = cZ_INT_0 + occ;
        numb_0[occ] = numbINT_0[occ1];
      };
      for (int occ = 0; occ <= 3-(3-cZ_INT_0); occ++) {
        numb_0[occ + (3-cZ_INT_0)+1] = numbDEC_0[occ];
      };
      
      
      clearMyZero = false;
      int cZ_INT_1 = 0;
      for (int occ = 0; occ <= 3; occ++) {
        if ((!clearMyZero)&(numbINT_1[occ]==0)){
          numbINT_1[occ] = 16;
          cZ_INT_1 += 1;
        }
        else {
          clearMyZero = true;
        }
      };
      int cZ_DEC_1 = 0;
      for (int occ = 0; occ <= (3-cZ_INT_1); occ++) {
        int occ1 = cZ_INT_1 + occ;
        numb_1[occ] = numbINT_1[occ1];
      };
      for (int occ = 0; occ <= 3-(3-cZ_INT_1); occ++) {
        numb_1[occ + (3-cZ_INT_1)+1] = numbDEC_1[occ];
      };
      
      byte numb[4] = {0, 0, 0, 0};
      
      set_DP_POS = 0b0000;
      bitWrite(set_DP_POS, (cZ_INT_0), HIGH);
      bitWrite(set_DP_POS, (2+cZ_INT_1), HIGH);
      if (decPVal_0==0 and decPVal_1==0){set_DP = LOW;};
      
      
      //Normal
      set_L1 = HIGH;//TrueHIGH , FalseLOW
      set_L2 = HIGH;//TrueHIGH , FalseLOW
      set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      
      byte set_extraPins = 0b000;//LOW,LOW,LOW
      for (int i = 0; i <= delayrepeat; i++) {
        masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
      };
    };
    
    
    void displayShow(float numberIN, byte displayMode, int delayrepeat=0){//Will Not Be Used!(bad method)
      boolean set_DP = HIGH;//TrueHIGH , FalseLOW
      boolean set_L1 = LOW;//TrueHIGH , FalseLOW
      boolean set_L2 = HIGH;//TrueHIGH , FalseLOW
      boolean set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      byte set_DP_POS = 0b0000;
      
      int intPVal = int(numberIN);
      int decPVal = int((numberIN - intPVal)*10000);
      float count = intPVal;
      /*
      Serial.print("Float numberIN: ");
      Serial.println(numberIN);
      Serial.print("intPVal: ");
      Serial.println(intPVal);
      Serial.print("decPVal: ");
      Serial.println(decPVal);
      */
      
      byte numbINT[4] = {0, 0, 0, 0};
      byte numbDEC[4] = {0, 0, 0, 0};
      int2array(decPVal, numbDEC);
      int2array(intPVal, numbINT);
      
      byte numb[4] = {0, 0, 0, 0};
      byte cit = 0;
      for (int occ = 0; occ <= 3; occ++) {
        if (numbINT[occ]==0){
          cit+=1;
        }else{break;};
      }
      //Serial.println(4-cit);
      
      set_DP_POS = 0b0000;
      bitWrite(set_DP_POS, (cit-1), HIGH);
      
      boolean clearMyZero = false;
      int cZ_INT = 0;
      int cZ_DEC = 0;
      for (int occ = 0; occ <= 3; occ++) {
        if ((!clearMyZero)&(numbINT[occ]==0)){
          numbINT[occ] = 16;
          cZ_INT += 1;
        }
        else {
          clearMyZero = true;
        }
        numb[occ] = numbINT[occ];
      };
      
      clearMyZero = false;
      for (int occT = 0; occT <= 3; occT++) {
        int occ = 3-occT;
        if ((!clearMyZero)&(numbDEC[occ]==0)){
          numbDEC[occ] = 16;
          cZ_DEC += 1;
        }
        else {
          clearMyZero = true;
        }
        numb[occ] = numbDEC[occ];
      };
      
      for (int occ = (4-cit); occ <= 3; occ++) {
        numb[occ] = numbDEC[occ-(5-cit)];
      };
      for (int occ = 0; occ <= (4-cit); occ++) {
        numb[occ] = numbINT[3-occ];
        //Serial.println(occ+4-cit);
      };
      
      if (decPVal==0){
        set_DP = LOW;
      };
      
      if (displayMode == 1){
        //Time
        set_DP = LOW;//TrueHIGH , FalseLOW
        set_L1 = HIGH;//TrueHIGH , FalseLOW
        set_L2 = HIGH;//TrueHIGH , FalseLOW
        set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      };
      if (displayMode == 2){
        //temperature C
        set_L1 = LOW;//TrueHIGH , FalseLOW
        set_L2 = LOW;//TrueHIGH , FalseLOW
        set_L3 = HIGH;//TrueHIGH , FalseLOW  //Used for temperature
        numb[0] = numb[0];
        numb[1] = numb[1];
        numb[2] = numb[2];
        numb[3] = 12;
        //set_DP_POS = set_DP_POS << 1;
        bitWrite(set_DP_POS, 0, bitRead(set_DP_POS, 4));
        bitWrite(set_DP_POS, 0, LOW);
      };
      if (displayMode == 3){
        //temperature F
        set_L1 = LOW;//TrueHIGH , FalseLOW
        set_L2 = LOW;//TrueHIGH , FalseLOW
        set_L3 = HIGH;//TrueHIGH , FalseLOW  //Used for temperature
        numb[0] = numb[0];
        numb[1] = numb[1];
        numb[2] = numb[2];
        numb[3] = 15;
        //set_DP_POS = set_DP_POS << 1;
        bitWrite(set_DP_POS, 0, bitRead(set_DP_POS, 4));
        bitWrite(set_DP_POS, 0, LOW);
      };
      if (displayMode == 4){
        //Normal HEX
        set_DP = LOW;//TrueHIGH , FalseLOW
        set_L1 = LOW;//TrueHIGH , FalseLOW
        set_L2 = LOW;//TrueHIGH , FalseLOW
        set_L3 = LOW;//TrueHIGH , FalseLOW  //Used for temperature
      };
      byte set_extraPins = 0b000;//LOW,LOW,LOW
      for (int i = 0; i <= delayrepeat; i++) {
        masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
      };
    };
    

    void masterSetDisplay(byte inputDigits[4], boolean set_DP_, byte set_DP_POS_, boolean set_L1_, boolean set_L2_, boolean set_L3_, byte extraOutPutPins){
      byte shiftByte0 = 0b00000000;// //Used 0bCCACACAC
      byte shiftByte1 = 0b00000000;// //Used 0bAAAAANNN
      byte cSelect = 0b00000000;//|1|2|L1L2L3|3|4|  //Used 11111NNN
      
      //TrueHIGH , FalseLOW
      boolean set_DP = set_DP_;
      byte set_DP_POS = set_DP_POS_;
      boolean set_L1 = set_L1_;
      boolean set_L2 = set_L2_;
      boolean set_L3 = set_L3_;//Used for temperature
      if (set_DP==false){set_DP_POS = 0b0000;};
      if (set_DP_POS==0b0000){set_DP = false;};
      
      byte setByteNumber;
      byte setLastByteNumber;
      byte setByteNumberP[2];
      byte setLastByteNumberP[2];
      byte delaymul;
      
      byte* numb = inputDigits;
      //DP
      byte statDP[4] = {!bitRead(set_DP_POS, 3-(0)), !bitRead(set_DP_POS, 3-(1)), !bitRead(set_DP_POS, 3-(2)), !bitRead(set_DP_POS, 3-(3))};
      if (set_L1|set_L2|set_L3){
        showL1L2L3Display(set_L1, set_L2, set_L3);
      };
      for (int i = 0; i <= 3; i++) {
        setByteNumber = segscreenBIN[numb[i]];
        //000|111|22|33333333|44|555|666|777|  |   |   |88|   |9999| 10 |11| 12 |
        //CD1|CD2|AD|CDL1L2L3|AE|CD3|ADP|CD4|  |NOC|NOP|AF|NOP|ACL3|AAL1|AG|ABL2|
        //|00101010|--1-1111|
        //|shiftByte0|shiftByte1|
        shiftByte0 = 0b00000000;// //Used 0bCCACACAC
        shiftByte1 = 0b00000000;// //Used 0bAAAAANNN
        bitWrite(shiftByte1, 7-(2), bitRead(setByteNumber,7-(0)));//A L1
        bitWrite(shiftByte1, 7-(4), bitRead(setByteNumber,7-(1)));//B L2
        bitWrite(shiftByte1, 7-(1), bitRead(setByteNumber,7-(2)));//C L3
        bitWrite(shiftByte0, 7-(2), bitRead(setByteNumber,7-(3)));//D
        bitWrite(shiftByte0, 7-(4), bitRead(setByteNumber,7-(4)));//E
        bitWrite(shiftByte1, 7-(0), bitRead(setByteNumber,7-(5)));//F
        bitWrite(shiftByte1, 7-(3), bitRead(setByteNumber,7-(6)));//G
        bitWrite(shiftByte0, 7-(6), (!statDP[i] and set_DP));//DP
        
        delaymul = 0;
        bitWrite(cSelect, 7-(2), HIGH);
        if ((numb[0] == numb[i]) and (statDP[0] == statDP[i])) {bitWrite(cSelect, 7-(0), LOW);delaymul += 1;} else {bitWrite(cSelect, 7-(0), HIGH);};
        if ((numb[1] == numb[i]) and (statDP[1] == statDP[i])) {bitWrite(cSelect, 7-(1), LOW);delaymul += 1;} else {bitWrite(cSelect, 7-(1), HIGH);};
        bitWrite(cSelect, 7-(2), HIGH);
        if ((numb[2] == numb[i]) and (statDP[2] == statDP[i])) {bitWrite(cSelect, 7-(3), LOW);delaymul += 1;} else {bitWrite(cSelect, 7-(3), HIGH);};
        if ((numb[3] == numb[i]) and (statDP[3] == statDP[i])) {bitWrite(cSelect, 7-(4), LOW);delaymul += 1;} else {bitWrite(cSelect, 7-(4), HIGH);};
        
        bitWrite(shiftByte0, 7-(0), bitRead(cSelect,7-(0)));//CD1 //keep LOW if CDL1L2L3 is HIGH
        bitWrite(shiftByte0, 7-(1), bitRead(cSelect,7-(1)));//CD2 //keep LOW if CDL1L2L3 is HIGH
        bitWrite(shiftByte0, 7-(3), bitRead(cSelect,7-(2)));//CDL1L2L3 //keep LOW if CD1|CD2|CD3|CD4 are HIGH
        bitWrite(shiftByte0, 7-(5), bitRead(cSelect,7-(3)));//CD3 //keep LOW if CDL1L2L3 is HIGH
        bitWrite(shiftByte0, 7-(7), bitRead(cSelect,7-(4)));//CD4 //keep LOW if CDL1L2L3 is HIGH
        
        writeShift2x(latchPin, dataPin, clockPin, shiftByte0, shiftByte1|extraOutPutPins);
        delay(4 / delaymul);
        setLastByteNumber = setByteNumber;
      };
    };
};

#endif







//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

/*


// Do this for MSBFIRST serial
int data = 500;
// shift out highbyte
shiftOut(dataPin, clock, MSBFIRST, (data >> 8));
// shift out lowbyte
shiftOut(dataPin, clock, MSBFIRST, data);

// Or do this for LSBFIRST serial
data = 500;
// shift out lowbyte
shiftOut(dataPin, clock, LSBFIRST, data);
// shift out highbyte
shiftOut(dataPin, clock, LSBFIRST, (data >> 8));







//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  //count up routine
  for (int j = 0; j < 256; j++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, j);
    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
*/
