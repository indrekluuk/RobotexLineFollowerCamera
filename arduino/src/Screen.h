//
// Created by indrek on 6.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_SCREEN_H
#define ROBOTEXLINEFOLLOWERCAMERA_SCREEN_H


#include "Arduino.h"
#include "screen/Adafruit_ST7735_mod.h"
#include "GrayScaleTable.h"



#define TFT_RST 10
#define TFT_CS 9
#define TFT_DC 8


class Screen {

    // TFT_SPI_clock = 13 and TFT_SPI_data = 11
    Adafruit_ST7735_mod tft = Adafruit_ST7735_mod(TFT_CS, TFT_DC, TFT_RST);


    // Normally it is portrait screen. Use it as landscape
    static const uint8_t screen_w = ST7735_TFTHEIGHT_18;
    static const uint8_t screen_h = ST7735_TFTWIDTH;

public:
    void init();

    inline const uint8_t getLineCount() __attribute__((always_inline));
    inline const uint8_t getLineLength() __attribute__((always_inline));

    inline void screenLineStart(const uint8_t lineIndex) __attribute__((always_inline));
    inline void screenLineEnd(void) __attribute__((always_inline));
    inline void sendPixelByte(const uint8_t byte) __attribute__((always_inline));
    inline void sendGrayscalePixelHigh(const uint8_t byte) __attribute__((always_inline));
    inline void sendGrayscalePixelLow(const uint8_t byte) __attribute__((always_inline));



    void fullSendPixelDelay();
};





void Screen::init() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
}


const uint8_t Screen::getLineCount() {
  return screen_h;
}

const uint8_t Screen::getLineLength() {
  return screen_w;
}


void Screen::screenLineStart(const uint8_t lineIndex) {
  const uint8_t screenLineIndex = screen_h - lineIndex - 1;
  tft.startAddrWindow(screenLineIndex, 0, screenLineIndex, screen_w - 1);
}

void Screen::screenLineEnd() {
  tft.endAddrWindow();
}

void Screen::sendPixelByte(const uint8_t byte) {
  SPDR = byte;
}

void Screen::sendGrayscalePixelHigh(const uint8_t byte) {
  sendPixelByte(graysScaleTableHigh[byte]);
}

void Screen::sendGrayscalePixelLow(const uint8_t byte) {
  sendPixelByte(graysScaleTableLow[byte]);
}




void Screen::fullSendPixelDelay() {
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_SCREEN_H
