//By Darrien Varrette


#include "ShiftSegDisplay.h"

ShiftSegDisplay displaySeg(A1,A2,A0);


float count = -5;





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
