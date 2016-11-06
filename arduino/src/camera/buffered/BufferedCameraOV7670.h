//
// Created by indrek on 30.04.2016.
//

#ifndef _CAMERAOV7670LINEBUFFER_H
#define _CAMERAOV7670LINEBUFFER_H

#include "../base/CameraOV7670.h"



// Pixel receiving order from camera for downsampled pictures: Pixel_1_H, Pixel_1_L, Pixel_2_H, Pixel_2_L ...
// First byte from camera is half a pixel (lower byte of a pixel).
// Shift line data by 1 byte to correct for it.
// This means that first pixel in each line is actually broken.
template <typename TBuffer, TBuffer size>
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




// TBuffer type for buffer size. If buffer is smaller than 256 then uin8_t can be used otherwise use uin16_t
// Tx type for line length. If line length is smaller than 256 then uin8_t can be used otherwise use uin16_t
// Ty type for line count. If line length is smaller than 256 then uin8_t can be used otherwise use uin16_t
template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
class BufferedCameraOV7670 : public CameraOV7670 {

protected:

  static const Tx lineLength = x;
  static const Ty lineCount = y;
  static const TBuffer pixelBufferLength = ((TBuffer)x)*2;
  static OV7670PixelBuffer<TBuffer, ((TBuffer)x)*2> pixelBuffer;

public:
  BufferedCameraOV7670(Resolution resolution, PixelFormat format, uint8_t internalClockPreScaler) :
      CameraOV7670(resolution, format, internalClockPreScaler) {};

  virtual inline void readLine() __attribute__((always_inline));

  inline const Tx getLineLength() __attribute__((always_inline));
  inline const Ty getLineCount() __attribute__((always_inline));
  inline const uint8_t * getPixelBuffer() __attribute__((always_inline));
  inline const TBuffer getPixelBufferLength() __attribute__((always_inline));
  inline const uint8_t getPixelByte(TBuffer byteIndex) __attribute__((always_inline));


};



template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
OV7670PixelBuffer<TBuffer, ((TBuffer)x)*2> BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::pixelBuffer;




template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
const Tx BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::getLineLength() {
  return lineLength;
}


template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
const Ty BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::getLineCount() {
  return lineCount;
}


template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
const uint8_t * BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::getPixelBuffer() {
  return pixelBuffer.readBuffer;
};


template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
const TBuffer BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::getPixelBufferLength() {
  return pixelBufferLength;
}


template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
const uint8_t BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::getPixelByte(const TBuffer byteIndex) {
  return pixelBuffer.readBuffer[byteIndex];
}


template <typename TBuffer, typename Tx, Tx x, typename Ty, Ty y>
void BufferedCameraOV7670<TBuffer, Tx, x, Ty, y>::readLine() {

  pixelBuffer.writeBufferPadding = 0;
  TBuffer bufferIndex = 0;

  while (bufferIndex < getPixelBufferLength()) {
    waitForPixelClockRisingEdge();
    pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
    waitForPixelClockRisingEdge();
    pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
  }
}








#endif //_CAMERAOV7670LINEBUFFER_H
