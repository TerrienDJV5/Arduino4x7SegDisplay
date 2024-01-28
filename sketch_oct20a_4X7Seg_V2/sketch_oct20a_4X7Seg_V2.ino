//By Darrien Varrette


#include "Arduino.h"

//#include "ShiftSegDisplay.h"
#include "ShiftSegDisplayV2.h"


void ShiftSegDisplay::digitalPinWrite(__uint8_t selectPin, bool newState){
  //put arduino digitalWrite Here
  digitalWrite(selectPin, newState);
};
void ShiftSegDisplay::hiddenPinMode(__uint8_t selectPin, __uint8_t newMode){
  //put arduino pinMode Here
  pinMode(selectPin, newMode);
};

ShiftSegDisplay displaySeg(12,13,14,27);
//ShiftSegDisplay displaySeg(32,35,34,33);
float countv = -5;

int value;
int lastValue;
float valueFloat;

void setup() {
  Serial.begin(115200);
  displaySeg.begin();
  //pinMode(A3, INPUT);
}

//PORTC is Analog pins


void loop()
{
  value = 100;//analogRead(A3);
  //displaySeg.showFromChar("-.-.-.-.:'");
  displaySeg.showSimpleValue(countv,0);
  //displaySeg.showSimpleValue(value);
  Serial.println(countv);
  
  
  valueFloat = float(value) / 1024;
  //Serial.println(value);
  //Serial.println(valueFloat);
  //Serial.println();
  lastValue = value;
  
  
  countv += 0.01;
  countv += valueFloat*10;
}


//please Test Code on Real device


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
