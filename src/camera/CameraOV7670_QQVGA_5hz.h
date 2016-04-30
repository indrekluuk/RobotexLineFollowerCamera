//
// Created by indrek on 30.04.2016.
//

#ifndef _CAMERAOV7670_QQVGA_5HZ_H
#define _CAMERAOV7670_QQVGA_5HZ_H

#include "base/BufferedCameraOV7670.h"


// 160 x 120 @ 5Hz
class CameraOV7670_QQVGA_5hz : public BufferedCameraOV7670<160, 120> {


public:
  CameraOV7670_QQVGA_5hz(PixelFormat format) : BufferedCameraOV7670(format, FPS_5Hz) {};

  inline void readLine() override __attribute__((always_inline));

};


void CameraOV7670_QQVGA_5hz::readLine() {
  pixelBuffer.writeBufferPadding = 0;
  uint16_t bufferIndex = 0;

  waitForPixelClockLow();

  while (bufferIndex < getPixelBufferLength()) {
    while(!(PINB & OV7670_PCLOCK_PORTB));
    pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
    while(!(PINB & OV7670_PCLOCK_PORTB));
    pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
  }
}






#endif //_CAMERAOV7670_QQVGA_5HZ_H
