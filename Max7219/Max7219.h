#include <SPI.h>

#define MAX7219_DECODE_MODE 0x09
#define MAX7219_INTENSITY 0x0A
#define MAX7219_SCAN_LIMIT 0x0B
#define MAX7219_SHUTDOWN 0x0C
#define MAX7219_DISPLAY_TEST 0x0F

class Max7219
{
  public:
    Max7219();
    void initSegment(); // initailize 7-segment
    void displayNumber(int num, char first, char last);//display int number
    void displayChangeRate(int opening, int price, char first, char last);//display Change rate of two number

  private:
    char font[11] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b,0x80};
    void sendSPI(char addr, char data); //send SPI data to address
};