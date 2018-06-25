#include "Max7219.h"

Max7219 segment = Max7219();

int i = 0;
void setup()
{
    segment.initSegment();
}
void loop()
{
    segment.displayNumber(i,4,1);
    segment.displayChangeRate(3600,i,8,4);
    i++;
    delay(1000);
    
}