

// https://github.com/ComputerNerd/ov7670-no-ram-arduino-uno

#ifndef _CAMERA_OV7670_h_
#define _CAMERA_OV7670_h_

#include "Arduino.h"
#include "Wire.h"
#include "CameraOV7670RegisterDefinitions.h"


class CameraOV7670 {


private:
  static const int i2cAddress = 0x21;
  static const RegisterData regsDefault[];
  static const RegisterData regsRGB565[];
  static const RegisterData regsYUV422[];
  static const RegisterData regsQQVGA[];
  static const RegisterData regsClock[];


public:

  CameraOV7670();
  void init();



private:
  void resetSettings();
  void setUpCamera();
  void setRegisters(const RegisterData *registerData);
  void setRegister(uint8_t addr, uint8_t val);
  uint8_t readRegister(uint8_t addr);
  void addBitsToRegister(uint8_t addr, uint8_t bits);

};


#endif // _CAMERA_OV7670_h_

