//
// Created by Indrek Luuk on 07.05.16.
//






#include <Arduino.h>
#include "Camera.h"
#include "Screen.h"
#include "databuffer/DataBufferSender.h"
#include "utils/Utils.h"
#include "ByteInversionTable.h"
#include "MonochromeBufferMask.h"


Camera camera;
Screen screen;
DataBufferSender dataBufferSender;



void processLine(const uint8_t lineIndex);
void processPixelsGrayscale();
void processPixelsMonochrome(bool horizontalLine);
uint8_t getLine();



void run() {
  Serial.begin(9600);
  camera.init();
  screen.init();

  noInterrupts();
  while(true) {
    camera.readFrame(processLine);
  }
}




uint16_t colorMin = 0xFF;
uint16_t colorMax = 0xFF;
uint8_t threshold = 0x80;
uint8_t scanLine = 30;
uint16_t monochromeLine;
int8_t lineRight;
int8_t lineLeft;



void processLine(const uint8_t lineIndex) {
  lineRight = -1;
  lineLeft = camera.getPixelBufferLength();

  screen.screenLineStart(lineIndex);
  processPixelsGrayscale();
  processPixelsMonochrome(lineIndex == scanLine);
  screen.screenLineEnd();

  if (lineIndex == scanLine){
    uint8_t aa[3];
    uint8_t line = getLine();
    aa[0] = line;
    aa[1] = ((uint8_t)lineRight) & 0x7F;
    aa[2] = ((uint8_t)lineLeft) & 0x7F;
    dataBufferSender.sendMessage(aa, 3);
  }
}


uint8_t getLine() {
  int8_t line = (40 - lineRight) < (lineLeft - 40) ? lineRight : lineLeft;
  return line < 0 || line >= camera.getPixelBufferLength() ? 0x7F : static_cast<uint8_t >(line);
}




void processPixelsGrayscale() {
  monochromeLine = 0;
  uint8_t lineMin = 0xFF;
  uint8_t lineMax = 0;

  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    uint8_t correctedPixel = byteInversionTable[pixelByte];
    monochromeLine |= correctedPixel > threshold ? 0x00 : monochromeBufferMask[i];
    /*
    asm volatile("nop");
     */

    screen.sendGrayscalePixelLow(pixelByte);

    if (lineMin > correctedPixel) lineMin = correctedPixel;
    if (lineMax < correctedPixel) lineMax = correctedPixel;
    /*
    asm volatile("nop");
     */
  }

  if (lineMin < ((colorMin + colorMax) / 2)) {
    threshold = lineMin + ((lineMax - lineMin) / 10);
    colorMin = lineMin;
    colorMax = lineMax;
  }
}




void processPixelsMonochrome(bool horizontalLine) {
  for (uint8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    uint8_t byte = monochromeLine & monochromeBufferMask[i] ? 0x00 : 0xFF;

    screen.sendPixelByte(byte);

    if (byte) {
      lineRight = i;
    }

    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    screen.sendPixelByte(horizontalLine?0xFF:0);
    /*
    asm volatile("nop");
     */
  }

  for (uint8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    uint8_t byte = monochromeLine & monochromeBufferMask[i] ? 0x00 : 0xFF;

    screen.sendPixelByte(byte);

    if (byte && (lineLeft >= camera.getPixelBufferLength())) {
      lineLeft = i;
    }

    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    screen.sendPixelByte(horizontalLine?0xFF:0);
    /*
    asm volatile("nop");
     */
  }

}








