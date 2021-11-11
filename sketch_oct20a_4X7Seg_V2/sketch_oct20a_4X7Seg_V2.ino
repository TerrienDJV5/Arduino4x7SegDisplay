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


void setup() {
  Serial.begin(9600);
  
  pinMode(A3, INPUT);
}

//PORTC is Analog pins


void loop() {
  value = analogRead(A3);
  //displaySeg.showNormal(value);
  //displaySeg.showFromChar("-.-.-.-:'");
  displaySeg.showSimpleValue(count);
  //displaySeg.showSimpleValue(value);
  
  
  //Serial.println(value);
  //displaySeg.displayShow(value, 0, 1);
  //displaySeg.showNormal(value);
  lastValue = value;
  
  
  count += 0.01;
}
