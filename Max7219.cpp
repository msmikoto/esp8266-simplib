#include <SPI.h>
#include <Arduino.h>
#include "Max7219.h"

Max7219::Max7219() {}

void Max7219::sendSPI(char addr, char data)
{
  digitalWrite(SS, LOW);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite(SS, HIGH);
}

void Max7219::initSegment()
{
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  sendSPI(MAX7219_DECODE_MODE, 0x00);
  sendSPI(MAX7219_INTENSITY, 0x08); //led intensity
  sendSPI(MAX7219_SCAN_LIMIT, 0x07);
  sendSPI(MAX7219_SHUTDOWN, 0x01);
  sendSPI(MAX7219_DISPLAY_TEST, 0x00);

  for (char i = 1; i <= 0x08; i++)
  {
    sendSPI(i, 0x00);
  }
}

void Max7219::displayNumber(int num, char first, char last)
{
  int del = 1;
  for (int i = first; i > last; i--)
  {
    del = del * 10;
  }
  int work = num;
  bool zero_flag = 0;
  for (int i = first; i >= last; i--)
  {
    if (work / del)
      zero_flag = 1;

    if (zero_flag)
      sendSPI(i, font[work / del]);
    else
      sendSPI(i, 0x00);

    work = work % del;
    del = del / 10;
  }
}
void Max7219::displayChangeRate(int sum, int value,char first, char last)
{
  if (sum < value)
  {
    sendSPI(first, 0x25);
    displayNumber((value - sum) * 100 / sum, first-1, last);
  }
  else
  {
    sendSPI(first, 0x13);
    displayNumber((sum - value) * 100 / sum, first-1, last);
  }
} 