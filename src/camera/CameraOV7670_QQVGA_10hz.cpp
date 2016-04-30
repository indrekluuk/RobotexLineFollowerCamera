//
// Created by indrek on 30.04.2016.
//

#include "CameraOV7670_QQVGA_10hz.h"


// shift everything by one since first pixel from camera is a half pixel
uint8_t CameraOV7670_QQVGA_10hz::pixelBuffer[CameraOV7670_QQVGA_10hz::pixelBufferLength + 1];


