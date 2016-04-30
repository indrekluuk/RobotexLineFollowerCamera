
#include "CameraOV7670.h"



CameraOV7670::CameraOV7670() {
}


void CameraOV7670::init() {
  Wire.begin();
  setUpCamera();
}



void CameraOV7670::setUpCamera() {
  resetSettings();
  setRegisters(regsDefault);
  //setRegisters(regsRGB565);
  setRegisters(regsYUV422);
  setRegisters(regsQQVGA);
  setRegisters(regsClock);
}




void CameraOV7670::resetSettings() {
  setRegister(REG_COM7, COM7_RESET);
  delay(500);
}


void CameraOV7670::setRegisters(const RegisterData *programMemPointer) {
  while (true) {
    RegisterData regData = {
        addr: pgm_read_byte(&(programMemPointer->addr)),
        val: pgm_read_byte(&(programMemPointer->val))
    };
    if (regData.addr == 0xFF) {
      break;
    } else {
      setRegister(regData.addr, regData.val);
      programMemPointer++;
    }
  }
}

void CameraOV7670::setRegister(uint8_t addr, uint8_t val) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(addr);
  Wire.write(val);
  Wire.endTransmission();
}



uint8_t CameraOV7670::readRegister(uint8_t addr) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(i2cAddress, 1);
  return Wire.read();
}


void CameraOV7670::addBitsToRegister(uint8_t addr, uint8_t bits) {
  uint8_t val = readRegister(addr);
  setRegister(addr, val | bits);
}



