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




void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);

  if (lineIndex & 1 || true) {
    processPixelsGrayscale(lineIndex);
  } else {
    processPixelsMonochrome(lineIndex);
  }

  screen.screenLineEnd();
}


void processPixelsGrayscale(const uint8_t lineIndex) {
  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t greyScale = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(greyScale);
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

    screen.sendGrayscalePixelLow(greyScale);
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
  }
}

void processPixelsMonochrome(const uint8_t lineIndex) {
  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t monoChrome = byteInversionTable[camera.getPixelByte(i)] > 0x25 ? 0xFF : 0x00;

    screen.sendPixelByte(monoChrome);
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

    screen.sendPixelByte(monoChrome);
    //asm volatile("nop");

  }
}








