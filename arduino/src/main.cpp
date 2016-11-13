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





uint16_t colorMin = 0xFF;
uint16_t colorMax = 0xFF;
uint8_t threshold = 0x80;
uint16_t monochromeLine;




void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);
  processPixelsGrayscale();
  processPixelsMonochrome();
  screen.screenLineEnd();

  uint8_t messageBuffer[3];
  messageBuffer[0] = lineIndex;
  messageBuffer[1] = (monochromeLine >> 8) & 0xFF;
  messageBuffer[2] = monochromeLine & 0xFF;
  dataBufferSender.sendMessage(messageBuffer, 3);
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




void processPixelsMonochrome() {
  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {

    uint8_t byte = monochromeLine & monochromeBufferMask[i] ? 0x00 : 0xFF;

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
    /*
    asm volatile("nop");
     */
  }



}








