//
// Created by indrek on 6.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_CAMERA_H
#define ROBOTEXLINEFOLLOWERCAMERA_CAMERA_H


// pre-define OV7670_PIXEL_BYTE since we only use 7 bits
#define OV7670_PIXEL_BYTE ((PIND & 0b01110000) | (PINC & 0b00001111))


#include <Arduino.h>
#include "camera/buffered/BufferedCameraOV7670_QQVGA_10hz.h"



class Camera {

    static BufferedCameraOV7670_QQVGA_10hz cameraOV7670;

public:
    using ProcessLineCallback = void (const uint8_t lineIndex, const uint8_t * buffer, const uint16_t lineLength);

    void init();
    void readFrame(ProcessLineCallback * processLineCallback);


    inline const uint16_t getPixelBufferLength() __attribute__((always_inline));
    inline const uint8_t getPixelByte(uint16_t byteIndex) __attribute__((always_inline));

};


BufferedCameraOV7670_QQVGA_10hz Camera::cameraOV7670(CameraOV7670::PIXEL_YUV422);



void Camera::init() {
  cameraOV7670.init();
  cameraOV7670.reversePixelBits();
  cameraOV7670.setManualContrastCenter(0);
  cameraOV7670.setContrast(0xFF);
}



void Camera::readFrame(ProcessLineCallback * processLineCallback) {
  uint8_t lineIndex = 0;
  cameraOV7670.waitForVsync();
  while (lineIndex < cameraOV7670.getLineCount()) {
    cameraOV7670.readLine();
    processLineCallback(lineIndex, cameraOV7670.getPixelBuffer(), cameraOV7670.getPixelBufferLength());
    lineIndex++;
  }
}


const uint16_t Camera::getPixelBufferLength() {
  return cameraOV7670.getPixelBufferLength();
}

const uint8_t Camera::getPixelByte(uint16_t byteIndex) {
  return cameraOV7670.getPixelByte(byteIndex);
}


#endif //ROBOTEXLINEFOLLOWERCAMERA_CAMERA_H
