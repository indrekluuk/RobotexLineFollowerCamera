//
// Created by indrek on 30.04.2016.
//

#include "CameraOV7670_QQVGA_10hz.h"


// shift everything by one since first pixel from camera is a half pixel
uint8_t CameraOV7670_QQVGA_10hz::pixelBuffer[CameraOV7670_QQVGA_10hz::pixelBufferLength + 1];


CameraOV7670_QQVGA_10hz::CameraOV7670_QQVGA_10hz(PixelFormat format) : CameraOV7670(format) {
}



uint16_t CameraOV7670_QQVGA_10hz::getLineLength() {
  return lineLength;
}

uint16_t CameraOV7670_QQVGA_10hz::getLineCount() {
  return lineCount;
}


void CameraOV7670_QQVGA_10hz::readLine() {
  // shift everything by one since first pixel from camera is a half pixel
  pixelBuffer[0] = 0;
  waitForPixelClockLow();
  readPixels_unrolled_x160(1);
}




