//By Darrien Varrette
//ShiftSegDisplayV2.cpp


#include "ShiftSegDisplayV2.h"



void ShiftSegDisplay::shiftOut(__uint8_t dataPin, __uint8_t clockPin, ShiftOrder bitOrder, u_int8_t dataIn){
  u_int8_t useMask;
  if (bitOrder == LSB_FIRST ){
    useMask = (u_int8_t){0b00000001};
  } else if (bitOrder == MSB_FIRST ){
    useMask = (u_int8_t){0b10000000};
  }else{
    while (true){
      std::cout<< "Wrong Input Fool!" << std::endl;
    }
  }
  bool dpin;
  bool cpin;
  for (unsigned int i=0; i<8; i++){
    dpin = ((dataIn & useMask)!=0);
    cpin = LOW;//BoolPinState
    digitalPinWrite(clockPin, cpin);
    digitalPinWrite(dataPin, dpin);
    cpin = HIGH;//BoolPinState
    digitalPinWrite(clockPin, cpin);
    //shift data
    if (bitOrder == LSB_FIRST ){
      dataIn = dataIn >> 1;
    }
    if (bitOrder == MSB_FIRST ){
      dataIn = dataIn << 1;
    }
  }
}
void ShiftSegDisplay::writeShift2x(__uint8_t latchPin, __uint8_t dataPin, __uint8_t clockPin, __uint8_t shiftByte0, __uint8_t shiftByte1){
  digitalPinWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSB_FIRST, (u_int8_t)shiftByte1);//LSB_FIRST , MSB_FIRST //Used 0bAAAAANNN
  shiftOut(dataPin, clockPin, LSB_FIRST, (u_int8_t)shiftByte0);//LSB_FIRST , MSB_FIRST //Used 0bCCACACAC
  //return the latch pin high to signal chip that it
  //no longer needs to listen for information
  digitalPinWrite(latchPin, HIGH);
};
void ShiftSegDisplay::showL1L2L3Display(bool set_L1, bool set_L2, bool set_L3){
  shiftByte0 = __uint8_t{0b00000000};// //Used 0bCCACACAC
  shiftByte1 = __uint8_t{0b00000000};// //Used 0bAAAAANNN
  bit_Write(shiftByte1, 7-(2), set_L1);//A L1
  bit_Write(shiftByte1, 7-(4), set_L2);//B L2
  bit_Write(shiftByte1, 7-(1), set_L3);//C L3
  
  bit_Write(shiftByte0, 7-(0), HIGH);//CD1 //keep LOW if CDL1L2L3 is HIGH
  bit_Write(shiftByte0, 7-(1), HIGH);//CD2 //keep LOW if CDL1L2L3 is HIGH
  bit_Write(shiftByte0, 7-(3), LOW);//CDL1L2L3 //keep LOW if CD1|CD2|CD3|CD4 are HIGH
  bit_Write(shiftByte0, 7-(5), HIGH);//CD3 //keep LOW if CDL1L2L3 is HIGH
  bit_Write(shiftByte0, 7-(7), HIGH);//CD4 //keep LOW if CDL1L2L3 is HIGH
  writeShift2x(latchPin, dataPin, clockPin, shiftByte0, shiftByte1|extraOutPutPins);
  delay(1);
};


//add Display Modes
//Normal
//Time
//temperature C
//temperature F
//Normal HEX
//add Used For The 3 Unused 74hc595 Pins
void ShiftSegDisplay::showSimpleValue(float numberIN , int delayrepeat=0)
{
  char modeSet[3] = ":'";
  modeSet[0] = ' ';
  modeSet[1] = ' ';
  u_int8_t cstrLength = (charInputLength-extraData4Input);
  char cstr[cstrLength];
  char cstrNew[cstrLength];
  double doubleNumber = double(numberIN);
  
  //i need to add leading spaces for INT Mode
  //for cleaner look
  if (int(numberIN)==numberIN){
    std::ostringstream n_str;
    n_str << numberIN;
    strncpy(cstr, n_str.str().c_str(), cstrLength);
    //itoa(numberIN, cstr, cstrLength);
  }
  else{
    std::ostringstream n_str;
    n_str.precision(3);
    n_str << doubleNumber;
    strncpy(cstr, n_str.str().c_str(), cstrLength);
    //dtostrf(doubleNumber, cstrLength ,3 ,cstr);
  };
  
  u_int8_t i2 = 0;
  for (u_int8_t i=0; i<=cstrLength; i++){
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
  //Serial.println(cstr);
  //Serial.println(cstrNew);
  char charInput[charInputLength] = "          ";// = "-.8.5.1.:'";//SDSDSDSD {L1L2} L3
  for (u_int8_t i=0; i<=sizeof(cstrNew)-1; i++){
    charInput[i] = cstrNew[i];
  };
  for (u_int8_t i=0; i<=sizeof(modeSet)-1; i++){
    charInput[i+sizeof(cstrNew)-1] = modeSet[i];
  };
  
  //To convert a number to scientific
  //  notation, place or move the decimal
  //  point of a number until the coefficient
  //  of the number is greater than 1 and less than 10.
  //Record down the coefficient (a) and 
  //  count the number of steps the 
  //  decimal point was moved.
  //The number of steps moved (n) is taken as the exponent.
  
  if (numberIN>=9999.0){
    char errorChar[11] = "E.r.o.r.:'";
    showFromChar(errorChar , delayrepeat);
  } else {
    //Serial.println(charInput);
    showFromChar(charInput , delayrepeat);
  };
};

void ShiftSegDisplay::showFromChar(char charInput[charInputLength] , int delayrepeat)
{
  //charInput = "-.8.5.1.:'";//SDSDSDSD {L1L2} L3
  // { |.|*|:}
  char modeL1L2[5] = " .*:";
  // { |'}
  char modeL3[3] = " '";
  // {0|1|2|3|4|5|6|7|8|9|A|b|C|d|E|F| |-|o|r}
  char modeSeg[21] = "0123456789AbCdEF -or";
  // { |.}
  char modeDec[3] = " .";
  bool set_DP = (charInput[1]==modeDec[1]|charInput[3]==modeDec[1] | charInput[5]==modeDec[1] | charInput[7]==modeDec[1]);//TrueHIGH , FalseLOW
  bool set_L1 = (charInput[8]==modeL1L2[2])|(charInput[8]==modeL1L2[3]);//TrueHIGH , FalseLOW
  bool set_L2 = (charInput[8]==modeL1L2[1])|(charInput[8]==modeL1L2[3]);//TrueHIGH , FalseLOW
  bool set_L3 = (charInput[9]==modeL3[1]);//TrueHIGH , FalseLOW  //Used for temperature
  __uint8_t set_DP_POS = __uint8_t{0b0000};
  bit_Write(set_DP_POS, 3 , (charInput[1]==modeDec[1]));
  bit_Write(set_DP_POS, 2 , (charInput[3]==modeDec[1]));
  bit_Write(set_DP_POS, 1 , (charInput[5]==modeDec[1]));
  bit_Write(set_DP_POS, 0 , (charInput[7]==modeDec[1]));
  __uint8_t numb[4] = {__uint8_t{0}, __uint8_t{0}, __uint8_t{0}, __uint8_t{0}};
  for (u_int32_t i=0; i<=sizeof(modeSeg)-1; i++)
  {
    if (charInput[0]==modeSeg[i])
    {
      numb[0] = (__uint8_t)i;
    };
    if (charInput[2]==modeSeg[i])
    {
      numb[1] = (__uint8_t)i;
    };
    if (charInput[4]==modeSeg[i])
    {
      numb[2] = (__uint8_t)i;
    };
    if (charInput[6]==modeSeg[i])
    {
      numb[3] = (__uint8_t)i;
    };
  };
  
  __uint8_t set_extraPins = __uint8_t{0b000};//LOW,LOW,LOW
  for (int i = 0; i <= delayrepeat; i++)
  {
    masterSetDisplay(numb, set_DP, set_DP_POS, set_L1, set_L2, set_L3, set_extraPins);
  };
};

void ShiftSegDisplay::masterSetDisplay(__uint8_t inputDigits[4], bool set_DP_, __uint8_t set_DP_POS_, bool set_L1_, bool set_L2_, bool set_L3_, __uint8_t extraOutPutPins)
{
  __uint8_t shiftByte0 = __uint8_t{0b00000000};// //Used 0bCCACACAC
  __uint8_t shiftByte1 = __uint8_t{0b00000000};// //Used 0bAAAAANNN
  u_int8_t cSelect = u_int8_t{0b00000000};//|1|2|L1L2L3|3|4|  //Used 11111NNN
  //TrueHIGH , FalseLOW
  bool set_DP = set_DP_;
  u_int8_t set_DP_POS = (u_int8_t)set_DP_POS_;
  bool set_L1 = set_L1_;
  bool set_L2 = set_L2_;
  bool set_L3 = set_L3_;//Used for temperature
  if (set_DP==false){set_DP_POS = u_int8_t{0b0000};};
  if (set_DP_POS==u_int8_t{0b0000}){set_DP = false;};
  u_int8_t setByteNumber;
  u_int8_t setLastByteNumber;
  u_int8_t setByteNumberP[2];
  u_int8_t setLastByteNumberP[2];
  u_int8_t delaymul;
  
  u_int8_t numb[4];
  numb[0] = (u_int8_t)inputDigits[0];
  numb[1] = (u_int8_t)inputDigits[1];
  numb[2] = (u_int8_t)inputDigits[2];
  numb[3] = (u_int8_t)inputDigits[3];
  //DP
  bool statDP[4] = {!bit_Read(set_DP_POS, 3-(0)), !bit_Read(set_DP_POS, 3-(1)), !bit_Read(set_DP_POS, 3-(2)), !bit_Read(set_DP_POS, 3-(3))};
  if (set_L1|set_L2|set_L3){
    showL1L2L3Display(set_L1, set_L2, set_L3);
  };
  for (int i = 0; i <= 3; i++) {
    setByteNumber = (u_int8_t)segscreenBIN[numb[i]];
    //000|111|22|33333333|44|555|666|777|  |   |   |88|   |9999| 10 |11| 12 |
    //CD1|CD2|AD|CDL1L2L3|AE|CD3|ADP|CD4|  |NOC|NOP|AF|NOP|ACL3|AAL1|AG|ABL2|
    //|00101010|--1-1111|
    //|shiftByte0|shiftByte1|
    shiftByte0 = __uint8_t{0b00000000};// //Used 0bCCACACAC
    shiftByte1 = __uint8_t{0b00000000};// //Used 0bAAAAANNN
    bit_Write
(shiftByte1, 7-(2), bit_Read(setByteNumber,7-(0)));//A L1
    bit_Write
(shiftByte1, 7-(4), bit_Read(setByteNumber,7-(1)));//B L2
    bit_Write
(shiftByte1, 7-(1), bit_Read(setByteNumber,7-(2)));//C L3
    bit_Write
(shiftByte0, 7-(2), bit_Read(setByteNumber,7-(3)));//D
    bit_Write
(shiftByte0, 7-(4), bit_Read(setByteNumber,7-(4)));//E
    bit_Write
(shiftByte1, 7-(0), bit_Read(setByteNumber,7-(5)));//F
    bit_Write
(shiftByte1, 7-(3), bit_Read(setByteNumber,7-(6)));//G
    bit_Write
(shiftByte0, 7-(6), (!statDP[i] and set_DP));//DP
    
    delaymul = 0;
    bit_Write
(cSelect, 7-(2), HIGH);
    if ((numb[0] == numb[i]) and (statDP[0] == statDP[i])) {bit_Write
(cSelect, 7-(0), LOW);delaymul += 1;} else {bit_Write
(cSelect, 7-(0), HIGH);};
    if ((numb[1] == numb[i]) and (statDP[1] == statDP[i])) {bit_Write
(cSelect, 7-(1), LOW);delaymul += 1;} else {bit_Write
(cSelect, 7-(1), HIGH);};
    bit_Write
(cSelect, 7-(2), HIGH);
    if ((numb[2] == numb[i]) and (statDP[2] == statDP[i])) {bit_Write
(cSelect, 7-(3), LOW);delaymul += 1;} else {bit_Write
(cSelect, 7-(3), HIGH);};
    if ((numb[3] == numb[i]) and (statDP[3] == statDP[i])) {bit_Write
(cSelect, 7-(4), LOW);delaymul += 1;} else {bit_Write
(cSelect, 7-(4), HIGH);};
    
    bit_Write
(shiftByte0, 7-(0), bit_Read(cSelect,7-(0)));//CD1 //keep LOW if CDL1L2L3 is HIGH
    bit_Write
(shiftByte0, 7-(1), bit_Read(cSelect,7-(1)));//CD2 //keep LOW if CDL1L2L3 is HIGH
    bit_Write
(shiftByte0, 7-(3), bit_Read(cSelect,7-(2)));//CDL1L2L3 //keep LOW if CD1|CD2|CD3|CD4 are HIGH
    bit_Write
(shiftByte0, 7-(5), bit_Read(cSelect,7-(3)));//CD3 //keep LOW if CDL1L2L3 is HIGH
    bit_Write
(shiftByte0, 7-(7), bit_Read(cSelect,7-(4)));//CD4 //keep LOW if CDL1L2L3 is HIGH
    
    writeShift2x(latchPin, dataPin, clockPin, shiftByte0, shiftByte1|extraOutPutPins);
    delay(4 / delaymul);
    //setLastByteNumber = setByteNumber;
  };
};
