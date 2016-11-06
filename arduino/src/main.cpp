//
// Created by Indrek Luuk on 07.05.16.
//






#include <Arduino.h>
#include "Camera.h"
#include "Screen.h"
#include "databuffer/DataBufferSender.h"
#include "GrayScaleTable.h"
#include "ByteInversionTable.h"
#include "utils/Utils.h"




Camera camera;
Screen screen;
DataBufferSender dataBufferSender;



void processFrame();



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
    processFrame();
  }
}




void processLine(const uint8_t lineIndex);

void processFrame() {


  screen.resetFrame();
  camera.readFrame(processLine);

  /*
  Serial.print("Avg: ");
  Serial.print((int)colorAverage);
  Serial.print(" Thr: ");
  Serial.print((int)threshold);
  Serial.print(" Min: ");
  Serial.print((int)frameMin);
  Serial.print(" Max: ");
  Serial.print((int)frameMax);
  Serial.println();
  */
}





void processLine(const uint8_t lineIndex) {
  screen.screenLineStart();

  for (uint16_t i=2; i<camera.getPixelBufferLength() - 2; i+=2) {
  //for (uint16_t i=2; i<ll - 2; i+=2) {
    uint8_t greyScale = camera.getPixelByte(i);

    screen.sendPixelByte(graysScaleTableHigh[greyScale]);
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

    screen.sendPixelByte(graysScaleTableLow[greyScale]);
    asm volatile("nop");
    asm volatile("nop");

  }


  /*
  //for (uint16_t i=2; i<cameraOV7670.getPixelBufferLength() - 2; i+=4) {
  for (uint16_t i=2; i<lineLength - 2; i+=2) {
    uint8_t greyScale = buffer[i];
    screen.sendPixelByte(graysScaleTableHigh[greyScale]);
    lineTotal += greyScale;
    if (greyScale > rowMax) rowMax = greyScale;
    //asm volatile("nop");

    screen.sendPixelByte(graysScaleTableLow[greyScale]);
    if (greyScale < rowMin) rowMin = greyScale;
    //asm volatile("nop");
  }
  colorTotal += lineTotal;
  if (rowMax > frameMax) frameMax = rowMax;
  if (rowMin < frameMin) frameMin = rowMin;
  */


/*
  // screen greyscale/monochrome divider
  sendPixelByte(0);
  fullSendPixelDelay();
  sendPixelByte(0);
  fullSendPixelDelay();



  // process and display monochrome
  for (uint16_t i=2; i<cameraOV7670.getPixelBufferLength(); i+=8) {
    uint8_t monoChrome = byteInversionTable[cameraOV7670.getPixelByte(i)] > threshold ? 0xFF : 0x00;

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

    asm volatile("nop");

  }

*/
  screen.screenLineEnd();
}








