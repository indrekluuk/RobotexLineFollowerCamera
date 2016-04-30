//
// Created by indrek on 30.04.2016.
//

#ifndef _CAMERAOV7670LINEBUFFER_H
#define _CAMERAOV7670LINEBUFFER_H

#include "CameraOV7670.h"


template <uint16_t x, uint16_t y>
class BufferedCameraOV7670 : public CameraOV7670 {

protected:
  static const uint16_t lineLength = x;
  static const uint16_t lineCount = y;
  static const uint16_t pixelBufferLength = x*2;
  static uint8_t pixelBuffer[];

public:
  BufferedCameraOV7670(PixelFormat format) : CameraOV7670(format) {};

  virtual void readLine() = 0;

  inline uint16_t getLineLength() __attribute__((always_inline));
  inline uint16_t getLineCount() __attribute__((always_inline));
  inline uint16_t getPixelBufferLength() __attribute__((always_inline));
  inline uint8_t getPixelByte(uint16_t byteIndex) __attribute__((always_inline));


};


// shift everything by one since first pixel from camera is a half pixel
template <uint16_t x, uint16_t y>
uint8_t BufferedCameraOV7670<x, y>::pixelBuffer[BufferedCameraOV7670<x, y>::pixelBufferLength + 1];





template <uint16_t x, uint16_t y>
uint16_t BufferedCameraOV7670<x, y>::getLineLength() {
  return lineLength;
}

template <uint16_t x, uint16_t y>
uint16_t BufferedCameraOV7670<x, y>::getLineCount() {
  return lineCount;
}

template <uint16_t x, uint16_t y>
uint16_t BufferedCameraOV7670<x, y>::getPixelBufferLength() {
  return pixelBufferLength;
}

template <uint16_t x, uint16_t y>
uint8_t BufferedCameraOV7670<x, y>::getPixelByte(uint16_t byteIndex) {
  return pixelBuffer[byteIndex];
}




#endif //_CAMERAOV7670LINEBUFFER_H
