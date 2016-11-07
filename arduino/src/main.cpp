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
void processPixelsGrayscale(const uint8_t lineIndex);
void processPixelsMonochrome(const uint8_t lineIndex);



void run() {
  Serial.begin(9600);
  camera.init();
  screen.init();

  /*
  char buf [] = "Hello World 2!";
  while(true) {
    dataBufferSender.sendMessage((uint8_t *)buf, strlen(buf));
    delay(5000);
  }
  */

  noInterrupts();
  while(true) {
    camera.readFrame(processLine);
  }
}


uint8_t threshold = 0x80;
const uint8_t monochromeBufferLength = 80;
uint8_t monochromeBuffer[monochromeBufferLength];



void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);
  processPixelsGrayscale(lineIndex);
  processPixelsMonochrome(lineIndex);
  screen.screenLineEnd();
}



void processPixelsGrayscale(const uint8_t lineIndex) {
  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    monochromeBuffer[i] = byteInversionTable[pixelByte] > threshold ? 0x00 : 0xFF;

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
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
  }
}

void processPixelsMonochrome(const uint8_t lineIndex) {
  for (uint8_t i=0; i<monochromeBufferLength; i++) {

    screen.sendPixelByte(monochromeBuffer[i]);
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
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");

  }
}








