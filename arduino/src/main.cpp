//
// Created by Indrek Luuk on 07.05.16.
//






#include <Arduino.h>
#include "Camera.h"
#include "Screen.h"
#include "databuffer/DataBufferSender.h"
#include "utils/Utils.h"
#include "ByteInversionTable.h"


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




uint8_t threshold = 0x80;
uint8_t scanLine = 30;
const uint8_t monochromeLineLength = 80;
uint8_t monochromeLine[monochromeLineLength];
int8_t lineRight;
int8_t lineLeft;



void processLine(const uint8_t lineIndex) {
  lineRight = -1;
  lineLeft = monochromeLineLength;

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
  return line < 0 || line >= monochromeLineLength ? 0x7F : static_cast<uint8_t >(line);
}


void processPixelsGrayscale() {
  uint8_t lineMin= 0xFF;

  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    uint8_t correctedPixel = byteInversionTable[pixelByte];
    monochromeLine[i] = correctedPixel > threshold ? 0x00 : 0xFF;
    /*
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
     */

    screen.sendGrayscalePixelLow(pixelByte);

    if (lineMin > correctedPixel) lineMin = correctedPixel;
    asm volatile("nop");
    /*
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
     */
  }

  threshold = lineMin + 20;
}




void processPixelsMonochrome(bool horizontalLine) {
  for (uint8_t i=0; i<monochromeLineLength/2; i++) {
    uint8_t byte = monochromeLine[i];

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
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

    screen.sendPixelByte(horizontalLine?0xFF:0);
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
  }

  for (uint8_t i=monochromeLineLength/2; i<monochromeLineLength; i++) {
    const uint8_t byte = monochromeLine[i];

    screen.sendPixelByte(monochromeLine[i]);

    if (byte && (lineLeft >= monochromeLineLength)) {
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
    asm volatile("nop");
    //asm volatile("nop");
    //asm volatile("nop");

    screen.sendPixelByte(horizontalLine?0xFF:0);
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
  }

}








