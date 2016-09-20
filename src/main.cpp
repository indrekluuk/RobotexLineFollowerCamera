//
// Created by Indrek Luuk on 07.05.16.
//

#define OV7670_HIGH_4_BITS_PIN_REG PIND
#define OV7670_HIGH_4_BITS_MASK 0b01110000

#define OV7670_LOW_4_BITS_PIN_REG PINC
#define OV7670_LOW_4_BITS_MASK 0b00001111



#include <arduino.h>
#include "screen/Adafruit_ST7735_mod.h"
#include "camera/buffered/BufferedCameraOV7670_QQVGA_10hz.h"
#include "databuffer/DataBufferSender.h"
#include "GrayScaleTable.h"
#include "ByteInversionTable.h"
#include "utils/Utils.h"



BufferedCameraOV7670_QQVGA_10hz cameraOV7670(CameraOV7670::PIXEL_YUV422);

int TFT_RST = 10;
int TFT_CS  = 9;
int TFT_DC  = 8;
// TFT_SPI_clock = 13 and TFT_SPI_data = 11
Adafruit_ST7735_mod tft = Adafruit_ST7735_mod(TFT_CS, TFT_DC, TFT_RST);


DataBufferSender dataBufferSender;



void processFrame();



void run() {
  Serial.begin(9600);
  cameraOV7670.init();
  cameraOV7670.reversePixelBits();
  cameraOV7670.setManualContrastCenter(0);
  cameraOV7670.setContrast(0xFF);

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  noInterrupts();

  dataBufferSender.newFrame();
  dataBufferSender.send(~0b11111011);

  while(true) {
    processFrame();
  }
}






inline void screenLineStart(void) __attribute__((always_inline));
inline void screenLineEnd(void) __attribute__((always_inline));
inline void sendPixelByte(uint8_t byte) __attribute__((always_inline));
inline void fullSendPixelDelay() __attribute__((always_inline));
inline void processLine() __attribute__((always_inline));



// Normally it is portrait screen. Use it as landscape
uint8_t screen_w = ST7735_TFTHEIGHT_18;
uint8_t screen_h = ST7735_TFTWIDTH;
uint8_t screenLineIndex;


uint16_t lineTotal = 0;
uint32_t colorTotal = 0;
uint32_t pixelCountInColorTotal = (cameraOV7670.getLineLength() * cameraOV7670.getLineCount()) / 2;
uint8_t threshold = 0;
uint8_t frameMin = 0xFF;
uint8_t frameMax = 0x00;



void processFrame() {
  cameraOV7670.waitForVsync();

  screenLineIndex = screen_h;

  colorTotal = 0;
  frameMin = 0xFF;
  frameMax = 0x00;


  uint8_t lineIndex = 0;
  while (lineIndex < cameraOV7670.getLineCount()) {
    cameraOV7670.readLine();
    processLine();
    lineIndex++;
  }


  uint8_t colorAverage = (colorTotal / pixelCountInColorTotal);
  threshold = colorAverage / 2;

  /*
  Serial.print("Avg: ");
  Serial.print((int)colorAverage);
  Serial.print(" Thr: ");
  Serial.print((int)threshold);
  Serial.print(" Min: ");
  Serial.print((int)frameMin);
  Serial.print(" Max: ");
  Serial.print((int)frameMax);
  Serial.println();
  */

}





void processLine() {
  screenLineStart();
  uint8_t rowMax = 0;
  uint8_t rowMin = 0xFF;

  // process and display greyscale
  lineTotal = 0;
  for (uint16_t i=2; i<cameraOV7670.getPixelBufferLength() - 2; i+=4) {
    uint8_t greyScale = cameraOV7670.getPixelByte(i);

    sendPixelByte(graysScaleTableHigh[greyScale]);
    lineTotal += greyScale;
    if (greyScale > rowMax) rowMax = greyScale;
    //asm volatile("nop");

    sendPixelByte(graysScaleTableLow[greyScale]);
    if (greyScale < rowMin) rowMin = greyScale;
    //asm volatile("nop");
  }
  colorTotal += lineTotal;
  if (rowMax > frameMax) frameMax = rowMax;
  if (rowMin < frameMin) frameMin = rowMin;


  // screen greyscale/monochrome divider
  sendPixelByte(0);
  fullSendPixelDelay();
  sendPixelByte(0);
  fullSendPixelDelay();



  // process and display monochrome
  for (uint16_t i=2; i<cameraOV7670.getPixelBufferLength(); i+=8) {
    uint8_t monoChrome = byteInversionTable[cameraOV7670.getPixelByte(i)] > threshold ? 0xFF : 0x00;

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

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

    sendPixelByte(monoChrome);

    asm volatile("nop");

  }


  screenLineEnd();


}




void screenLineStart()   {
  if (screenLineIndex > 0) screenLineIndex--;
  tft.startAddrWindow(screenLineIndex, 0, screenLineIndex, screen_w-1);
}

void screenLineEnd() {
  tft.endAddrWindow();
}

void sendPixelByte(uint8_t byte) {
  SPDR = byte;
}

void fullSendPixelDelay() {
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




