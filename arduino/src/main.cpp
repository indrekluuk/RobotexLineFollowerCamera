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
void processPixelsMonochrome();





void run() {
  Serial.begin(9600);
  camera.init();
  screen.init();

  noInterrupts();
  while(true) {
    camera.readFrame(processLine);
  }
}





uint8_t colorMin = 0xFF;
uint8_t colorMax = 0xFF;
uint8_t threshold = 0x80;
uint8_t monochromeLineHigh;
uint8_t monochromeLineLow;
uint8_t lineMin;
uint8_t lineMax;




void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);
  processPixelsGrayscale();
  processPixelsMonochrome();
  screen.screenLineEnd();

  uint8_t messageBuffer[3];
  messageBuffer[0] = lineIndex;
  messageBuffer[1] = monochromeLineHigh;
  messageBuffer[2] = monochromeLineLow;
  dataBufferSender.sendMessage(messageBuffer, 3);
}





void processPixelsGrayscale() {
  monochromeLineLow = 0;
  monochromeLineHigh = 0;
  lineMin = 0xFF;
  lineMax = 0;

  for (uint8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    uint8_t correctedPixel = byteInversionTable[pixelByte];
    monochromeLineLow |= correctedPixel > threshold ? 0x00 : monochromeBufferMask[i];
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

  for (uint8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    uint8_t correctedPixel = byteInversionTable[pixelByte];
    monochromeLineHigh |= correctedPixel > threshold ? 0x00 : monochromeBufferMask[i];
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

  if (lineMin < ((colorMin >> 1) + (colorMax >> 1))) {
    threshold = lineMin + ((lineMax - lineMin) >> 3);
    colorMin = lineMin;
    colorMax = lineMax;
  }
}




void processPixelsMonochrome() {
  for (uint8_t i=0; i<camera.getPixelBufferLength()/2; i++) {

    uint8_t byte = monochromeLineLow & monochromeBufferMask[i] ? 0x00 : 0xFF;

    screen.sendPixelByte(byte);

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

    screen.sendPixelByte(0);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
  }


  for (uint8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {

    uint8_t byte = monochromeLineHigh & monochromeBufferMask[i] ? 0x00 : 0xFF;

    screen.sendPixelByte(byte);

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

    screen.sendPixelByte(0);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
  }



}








