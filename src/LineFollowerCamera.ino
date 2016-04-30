
#include "screen/Adafruit_ST7735_mod.h"
#include "camera/CameraOV7670_QQVGA_10hz.h"
#include "camera/CameraOV7670_QQVGA.h"
#include "GrayScaleTable.h"



//CameraOV7670_QQVGA cameraOV7670(CameraOV7670::PIXEL_YUV422, CameraOV7670::FPS_5_Hz);
CameraOV7670_QQVGA_10hz cameraOV7670(CameraOV7670::PIXEL_YUV422);

int TFT_RST = 10;
int TFT_CS  = 9;
int TFT_DC  = 8;
// TFT_SPI_clock = 13 and TFT_SPI_data = 11
Adafruit_ST7735_mod tft = Adafruit_ST7735_mod(TFT_CS, TFT_DC, TFT_RST);



void sleep(uint64_t milliseconds) {
  for (uint64_t d = 0; d<196*milliseconds; d++) {
    asm volatile("nop");
  }
}


void setup() {
  //Serial.begin(9600);
  cameraOV7670.init();
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  noInterrupts();
}



void loop() {
  processFrame();
}



inline void sendLineBufferToDisplay() __attribute__((always_inline));
inline void screenLineStart(void) __attribute__((always_inline));
inline void screenLineEnd(void) __attribute__((always_inline));
inline void sendPixelByte(uint8_t byte) __attribute__((always_inline));



// Normally it is portrait screen. Use it as landscape
uint8_t screen_w = ST7735_TFTHEIGHT_18;
uint8_t screen_h = ST7735_TFTWIDTH;
uint8_t screenLineIndex;


void processFrame() {
  cameraOV7670.waitForVsync();

  screenLineIndex = screen_h;

      uint8_t lineIndex = 0;
  while (lineIndex < cameraOV7670.getLineCount()) {
    cameraOV7670.readLine();
    sendLineBufferToDisplay();
    lineIndex++;
  }
}



void sendLineBufferToDisplay() {
  screenLineStart();

  // bytes from camera are out of sync by one byte
  for (uint16_t i=0; i<cameraOV7670.getPixelBufferLength(); i+=2) {
    uint8_t greyScale = cameraOV7670.getPixelByte(i);

    sendPixelByte(graysScaleTableHigh[greyScale]);
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

    sendPixelByte(graysScaleTableLow[greyScale]);
    asm volatile("nop");
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

