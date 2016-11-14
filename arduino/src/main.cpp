//
// Created by Indrek Luuk on 07.05.16.
//






#include <Arduino.h>
#include "Camera.h"
#include "Screen.h"
#include "line/Line.h"
#include "databuffer/DataBufferSender.h"
#include "utils/Utils.h"
#include "ByteInversionTable.h"
#include "MonochromeBufferMask.h"


Camera camera;
Screen screen;
Line line;
DataBufferSender dataBufferSender;



void processLine(const uint8_t lineIndex);
void processGrayscale();
inline void processGrayScalePixel(uint8_t &i, uint8_t &monochromeByte) __attribute__((always_inline));
void processMonochrome();
inline void processMonochromePixel(uint8_t &i, uint8_t &monochromeByte, bool isLine) __attribute__((always_inline));




uint8_t frameMin;
uint8_t frameMax;
uint8_t frameSpreadThreshold = 0x80;
uint8_t lineThreshold = 0x80;
uint8_t monochromeLineHigh;
uint8_t monochromeLineLow;
uint8_t lineMin;
uint8_t lineMax;





void run() {
  Serial.begin(9600);
  camera.init();
  screen.init();

  noInterrupts();
  while(true) {
    frameMin = 0xFF;
    frameMax = 0x00;
    line.resetLine();
    camera.readFrame(processLine);
    frameSpreadThreshold = ((frameMax - frameMin) >> 1) ;
  }
}





void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);
  processGrayscale();
  //line.setRowBitmap(lineIndex, monochromeLineHigh, monochromeLineLow);
  processMonochrome();
  screen.screenLineEnd();

  uint8_t messageBuffer[3];
  messageBuffer[0] = lineIndex;
  messageBuffer[1] = monochromeLineHigh;
  messageBuffer[2] = monochromeLineLow;
  dataBufferSender.sendMessage(messageBuffer, 3);
}





void processGrayscale() {
  monochromeLineLow = 0;
  monochromeLineHigh = 0;
  lineMin = 0xFF;
  lineMax = 0;

  for (uint8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    processGrayScalePixel(i, monochromeLineLow);
  }

  for (uint8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    processGrayScalePixel(i, monochromeLineHigh);
  }

  uint8_t lineSpread = lineMax - lineMin;
  if (lineSpread > frameSpreadThreshold) {
    lineThreshold = lineMin + (lineSpread >> 2);
  }
  if (frameMin < lineMin) frameMin = lineMin;
  if (frameMax > lineMax) frameMax = lineMax;
}


void processGrayScalePixel(uint8_t &i, uint8_t &monochromeByte) {
  uint8_t pixelByte = camera.getPixelByte(i);

  screen.sendGrayscalePixelHigh(pixelByte);
  // asm volatile("nop");

  uint8_t correctedPixel = byteInversionTable[pixelByte];
  monochromeByte |= correctedPixel > lineThreshold ? 0x00 : monochromeBufferMask[i];

  screen.sendGrayscalePixelLow(pixelByte);
  // asm volatile("nop");

  if (lineMin > correctedPixel) lineMin = correctedPixel;
  if (lineMax < correctedPixel) lineMax = correctedPixel;
}






void processMonochrome() {
  //uint8_t pixelPos = (uint8_t)map(rowPos, -13, 13, 0, 80);
  for (uint8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    processMonochromePixel(i, monochromeLineLow, false);
  }
  for (uint8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    processMonochromePixel(i, monochromeLineHigh, false);
  }
}

void processMonochromePixel(uint8_t &i, uint8_t &monochromeByte, bool isLine) {
  uint8_t byte = monochromeByte & monochromeBufferMask[i] ? 0x00 : 0xFF;

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

  //screen.sendPixelByte(isLine ? 0xFF : 0);
  screen.sendPixelByte(0);
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

}









