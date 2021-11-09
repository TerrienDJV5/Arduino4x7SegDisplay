//By Darrien Varrette


#include "ShiftSegDisplay.h"

ShiftSegDisplay displaySeg(A1,A2,A0);


float count = 0;





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
  //displaySeg.displayShow(count, 1, 100);
  //displaySeg.displayShow(count, 2, 100);
  //displaySeg.displayShow(count, 3, 100);
  //displaySeg.displayShow(count, 4, 100);
  
  //Serial.println(count);
  //displaySeg.showNormal(count);
  //displaySeg.showFloat(count);
  
  
  //displaySeg.showAsTime(count, count);
  //displaySeg.displayShow(count, 0);
  
  
  
  
  value = analogRead(A3);
  
  //displaySeg.showNormal(value);
  //displaySeg.showFromChar("-.-.-.-:'");
  displaySeg.showNormalV2(count);
  
  //Serial.println(value);
  //displaySeg.displayShow(value, 0, 1);
  //displaySeg.showNormal(value);
  lastValue = value;
  
  
  count += 0.01;
}
