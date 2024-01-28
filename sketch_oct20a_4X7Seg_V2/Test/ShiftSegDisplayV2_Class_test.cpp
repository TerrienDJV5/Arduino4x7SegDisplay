//By Darrien Varrette
//ShiftSegDisplayV2_Class_Test.cpp


#include "../ShiftSegDisplayV2.h"

void ShiftSegDisplay::digitalPinWrite(__uint8_t selectPin, bool newState){
  std::cout << "PIN#"<< selectPin <<":" << newState << std::endl;
};

ShiftSegDisplay displaySeg(1,2,3,4);




unsigned int count = 0;
int main()
{
  while (true)
  {
    displaySeg.showSimpleValue(count);
    count++;
  };
  return 0;
}
