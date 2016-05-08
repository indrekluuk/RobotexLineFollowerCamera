
#include "CameraOV7670.h"



void CameraOV7670::init() {
  Wire.begin();
  initClock();
  setUpCamera();
}


void CameraOV7670::initClock() {
  // pin 3 to 8Mhz (camera clock)
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 1;
  OCR2B = 0;
}


void CameraOV7670::setUpCamera() {
  resetSettings();
  setRegisters(regsDefault);

  switch (pixelFormat) {
    default:
    case PIXEL_RGB565:
      setRegisters(regsRGB565);
      break;
    case PIXEL_BAYERRGB:
      setRegisters(regsBayerRGB);
      break;
    case PIXEL_YUV422:
      setRegisters(regsYUV422);
      break;
  }

  switch (resolution) {
    case RESOLUTION_VGA_640x480:
      setRegisters(regsVGA);
      break;
    case RESOLUTION_QVGA_320x240:
      setRegisters(regsQVGA);
      break;
    default:
    case RESOLUTION_QQVGA_160x120:
      setRegisters(regsQQVGA);
      break;
  }

  setRegister(REG_COM10, COM10_PCLK_HB); // disable pixel clock during blank lines
  setRegister(REG_CLKRC, 0x80 | internalClockPreScaler); // f = input / (val + 1)



}



void CameraOV7670::setManualContrastCenter(uint8_t contrastCenter) {
  setRegisterBitsAND(MTXS, 0x7F); // disable auto contrast
  setRegister(REG_CONTRAST_CENTER, contrastCenter);
}


void CameraOV7670::setContrast(uint8_t contrast) {
  // default 0x40
  setRegister(REG_CONTRAS, contrast);
}


void CameraOV7670::setBrightness(uint8_t birghtness) {
  setRegister(REG_BRIGHT, birghtness);
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


void CameraOV7670::setRegisterBitsOR(uint8_t addr, uint8_t bits) {
  uint8_t val = readRegister(addr);
  setRegister(addr, val | bits);
}

void CameraOV7670::setRegisterBitsAND(uint8_t addr, uint8_t bits) {
  uint8_t val = readRegister(addr);
  setRegister(addr, val & bits);
}





