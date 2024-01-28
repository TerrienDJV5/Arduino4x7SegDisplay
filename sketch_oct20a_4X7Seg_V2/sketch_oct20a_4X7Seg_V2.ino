//By Darrien Varrette


#include "Arduino.h"

//#include "ShiftSegDisplay.h"
#include "ShiftSegDisplayV2.h"


void ShiftSegDisplay::digitalPinWrite(__uint8_t selectPin, bool newState){
  //put arduino digitalWrite Here
  digitalWrite(selectPin, newState);
  //cout << "PIN#"<< selectPin <<":" << newState << endl;
};


ShiftSegDisplay displaySeg(34,35,36,37);
float countv = -5;

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
  displaySeg.showSimpleValue(countv,0);
  //displaySeg.showSimpleValue(value);
  
  
  
  valueFloat = float(value) / 1024;
  //Serial.println(value);
  //Serial.println(valueFloat);
  //Serial.println();
  lastValue = value;
  
  
  countv += 0.01;
  countv += valueFloat*10;
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
