//By Darrien Varrette


//#include "ShiftSegDisplay.h"
#include "ShiftSegDisplayV2.cpp"

class ShiftSegDisplayArduino : public ShiftSegDisplay
{
  public:
    ShiftSegDisplayArduino(u_int8_t latchPin, u_int8_t clockPin, u_int8_t dataPin) {
      // Use 'this->' to make the difference between the
      // 'pin' attribute of the class and the 
      // local variable 'pin' created from the parameter.
      this->latchPin = (byte)latchPin;
      this->clockPin = (byte)clockPin;
      this->dataPin = (byte)dataPin;
      init();
    };
    void init() {
      //pinMode(latchPin, OUTPUT);
      //pinMode(clockPin, OUTPUT);
      //pinMode(dataPin, OUTPUT);
      // Always try to avoid duplicate code.
    };
    void digitalPinWrite(byte selectPin, bool newState){
      //put arduino digitalWrite Here
      cout << "PIN#"<< selectPin <<":" << newState << endl;
    };
    
};

//ShiftSegDisplay displaySeg;
ShiftSegDisplayArduino displaySeg(A1,A2,A3);


//ShiftSegDisplay displaySeg(A1,A2,A0);


float count = -5;







int value;
int lastValue;
float valueFloat;

void setup() {
  Serial.begin(9600);
  
  pinMode(A3, INPUT);
}

//PORTC is Analog pins


void loop() {
  value = analogRead(A3);
  //displaySeg.showFromChar("-.-.-.-.:'");
  displaySeg.showSimpleValue(count);
  //displaySeg.showSimpleValue(value);
  
  
  
  valueFloat = float(value) / 1024;
  //Serial.println(value);
  //Serial.println(valueFloat);
  //Serial.println();
  lastValue = value;
  
  
  count += 0.01;
  count += valueFloat*10;
}





void binLead(byte var) {
  for (byte test = 0b10000000; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  };
  Serial.println();
};

void printarray(byte* arrayIN){
  for (byte i=0;i<=3;i++){
    Serial.print(byte(arrayIN[i]));
    Serial.print(" ");
  };
  Serial.println();
};
