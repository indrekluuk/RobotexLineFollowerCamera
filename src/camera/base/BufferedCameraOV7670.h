//
// Created by indrek on 30.04.2016.
//

#ifndef _CAMERAOV7670LINEBUFFER_H
#define _CAMERAOV7670LINEBUFFER_H

#include "CameraOV7670.h"



// Pixel receiving order from camera: Pixel_1_H, Pixel_1_L, Pixel_2_H, Pixel_2_L ...
// First byte from camera is half a pixel (lower byte of a pixel).
// Shift line data data by 1 byte to correct it.
// This means that first pixel in each line is actually broken.
template <uint16_t size>
union OV7670PixelBuffer {
  struct {
    uint8_t writeBufferPadding;
    uint8_t writeBuffer[size];
  };
  struct {
    uint8_t readBuffer[size];
    uint8_t readBufferPadding;
  };
};




template <uint16_t x, uint16_t y>
class BufferedCameraOV7670 : public CameraOV7670 {

protected:
  static const uint16_t lineLength = x;
  static const uint16_t lineCount = y;
  static const uint16_t pixelBufferLength = x*2;
  static OV7670PixelBuffer<x*2> pixelBuffer;

public:
  BufferedCameraOV7670(PixelFormat format, FramesPerSecond fps) : CameraOV7670(format, fps) {};

  virtual void readLine() = 0;

  inline uint16_t getLineLength() __attribute__((always_inline));
  inline uint16_t getLineCount() __attribute__((always_inline));
  inline uint16_t getPixelBufferLength() __attribute__((always_inline));
  inline uint8_t getPixelByte(uint16_t byteIndex) __attribute__((always_inline));


};



template <uint16_t x, uint16_t y>
OV7670PixelBuffer<x*2> BufferedCameraOV7670<x, y>::pixelBuffer;




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
  return pixelBuffer.readBuffer[byteIndex];
}




#endif //_CAMERAOV7670LINEBUFFER_H
