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
void processPixelsMonochrome(bool horozonatlLine);



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
const uint8_t monochromeLineLength = 80;
uint8_t monochromeLine[monochromeLineLength];
union {
    struct {
        int8_t right;
        int8_t left;
    };
    uint8_t data[2];
} line;



void processLine(const uint8_t lineIndex) {
  line.right = -1;
  line.left = 0x1F;

  screen.screenLineStart(lineIndex);
  processPixelsGrayscale();
  processPixelsMonochrome(lineIndex == 30);
  screen.screenLineEnd();

  if (lineIndex == 30){
    dataBufferSender.sendMessage(line.data, 2);
  }
}



void processPixelsGrayscale() {
  for (uint8_t i=0; i<camera.getPixelBufferLength(); i++) {
    uint8_t pixelByte = camera.getPixelByte(i);

    screen.sendGrayscalePixelHigh(pixelByte);

    monochromeLine[i] = byteInversionTable[pixelByte] > threshold ? 0x00 : 0xFF;
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




void processPixelsMonochrome(bool horozonatlLine) {
  for (uint8_t i=0; i<monochromeLineLength/2; i++) {
    uint8_t byte = monochromeLine[i];

    screen.sendPixelByte(byte);

    if (byte) {
      line.right = i;
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

    screen.sendPixelByte(horozonatlLine?0xFF:0);
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

    if (byte && line.left >= monochromeLineLength) {
      line.left = i;
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

    screen.sendPixelByte(horozonatlLine?0xFF:0);
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








