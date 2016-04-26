
#include "screen/Adafruit_ST7735_mod.h"
#include "camera/OV7670Initializer.h"


OV7670Initializer cameraInitializer;

int TFT_RST = 10;
int TFT_CS  = 9;
int TFT_DC  = 8;
// TFT_SPI_clock = 13 and TFT_SPI_data = 11
Adafruit_ST7735_mod tft = Adafruit_ST7735_mod(TFT_CS, TFT_DC, TFT_RST);



/*
B (digital pin 8 to 13)
C (analog input pins)
D (digital pins 0 to 7)
*/
#define VSYNC_PORTD 0b00000100 // PIN 2
//#define HREF_PORTC 0b10000000 // PIN A7 - doesn't work!
#define PCLOCK_PORTB 0b00010000 // PIN 12
#define LOW_4_BITS_PORTC 0b00001111 // PIN A0..A3
#define HIGH_4_BITS_PORTD 0b11110000 // PIN 4..7





void setUpCamera() {

  // pin 3 to 8Mhz (camera clock)
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 1;
  OCR2B = 0;

  cameraInitializer.init();
}



void setUpScreen() {
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
}



void sleep(uint64_t milliseconds) {
  for (uint64_t d = 0; d<196*milliseconds; d++) {
    asm volatile("nop");
  }
}




void setup() {
  //Serial.begin(9600);
  setUpCamera();
  setUpScreen();
  noInterrupts();
}





void loop() {
  processFrame();
}





inline void waitForVsync(void) __attribute__((always_inline));

inline void readPixels_unrolled_x160(uint16_t byteIndex) __attribute__((always_inline));
inline void readPixels_unrolled_x10(uint16_t byteIndex) __attribute__((always_inline));
inline void readPixel_unrolled(uint16_t byteIndex) __attribute__((always_inline));
inline void readPixels_loop_line() __attribute__((always_inline));

inline void waitForPixelClockLow(void) __attribute__((always_inline));
inline void waitForPixelClockRisingEdge(void) __attribute__((always_inline));
inline uint8_t getPixelByte(void) __attribute__((always_inline));

inline void sendLineBufferToDisplay() __attribute__((always_inline));
inline void screenLineStart(void) __attribute__((always_inline));
inline void screenLineEnd(void) __attribute__((always_inline));

inline uint16_t rgbGreyScale(uint8_t greysCale) __attribute__((always_inline));
inline void sendPixelByte(uint8_t byte) __attribute__((always_inline));



uint8_t screen_w = ST7735_TFTWIDTH;
uint8_t screen_h = ST7735_TFTHEIGHT_18;
const uint8_t cameraPixelColCount = 160;
const uint8_t cameraPixelRowCount = 120;
uint8_t scanLine;
uint8_t lineBuffer[cameraPixelColCount * 2];

uint8_t graysScaleTableHigh[] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x10,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x21,
    0x21,
    0x21,
    0x21,
    0x21,
    0x21,
    0x21,
    0x21,
    0x29,
    0x29,
    0x29,
    0x29,
    0x29,
    0x29,
    0x29,
    0x29,
    0x31,
    0x31,
    0x31,
    0x31,
    0x31,
    0x31,
    0x31,
    0x31,
    0x39,
    0x39,
    0x39,
    0x39,
    0x39,
    0x39,
    0x39,
    0x39,
    0x42,
    0x42,
    0x42,
    0x42,
    0x42,
    0x42,
    0x42,
    0x42,
    0x4A,
    0x4A,
    0x4A,
    0x4A,
    0x4A,
    0x4A,
    0x4A,
    0x4A,
    0x52,
    0x52,
    0x52,
    0x52,
    0x52,
    0x52,
    0x52,
    0x52,
    0x5A,
    0x5A,
    0x5A,
    0x5A,
    0x5A,
    0x5A,
    0x5A,
    0x5A,
    0x63,
    0x63,
    0x63,
    0x63,
    0x63,
    0x63,
    0x63,
    0x63,
    0x6B,
    0x6B,
    0x6B,
    0x6B,
    0x6B,
    0x6B,
    0x6B,
    0x6B,
    0x73,
    0x73,
    0x73,
    0x73,
    0x73,
    0x73,
    0x73,
    0x73,
    0x7B,
    0x7B,
    0x7B,
    0x7B,
    0x7B,
    0x7B,
    0x7B,
    0x7B,
    0x84,
    0x84,
    0x84,
    0x84,
    0x84,
    0x84,
    0x84,
    0x84,
    0x8C,
    0x8C,
    0x8C,
    0x8C,
    0x8C,
    0x8C,
    0x8C,
    0x8C,
    0x94,
    0x94,
    0x94,
    0x94,
    0x94,
    0x94,
    0x94,
    0x94,
    0x9C,
    0x9C,
    0x9C,
    0x9C,
    0x9C,
    0x9C,
    0x9C,
    0x9C,
    0xA5,
    0xA5,
    0xA5,
    0xA5,
    0xA5,
    0xA5,
    0xA5,
    0xA5,
    0xAD,
    0xAD,
    0xAD,
    0xAD,
    0xAD,
    0xAD,
    0xAD,
    0xAD,
    0xB5,
    0xB5,
    0xB5,
    0xB5,
    0xB5,
    0xB5,
    0xB5,
    0xB5,
    0xBD,
    0xBD,
    0xBD,
    0xBD,
    0xBD,
    0xBD,
    0xBD,
    0xBD,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xC6,
    0xCE,
    0xCE,
    0xCE,
    0xCE,
    0xCE,
    0xCE,
    0xCE,
    0xCE,
    0xD6,
    0xD6,
    0xD6,
    0xD6,
    0xD6,
    0xD6,
    0xD6,
    0xD6,
    0xDE,
    0xDE,
    0xDE,
    0xDE,
    0xDE,
    0xDE,
    0xDE,
    0xDE,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF
};

uint8_t graysScaleTableLow[] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x20,
    0x20,
    0x20,
    0x20,
    0x41,
    0x41,
    0x41,
    0x41,
    0x61,
    0x61,
    0x61,
    0x61,
    0x82,
    0x82,
    0x82,
    0x82,
    0xA2,
    0xA2,
    0xA2,
    0xA2,
    0xC3,
    0xC3,
    0xC3,
    0xC3,
    0xE3,
    0xE3,
    0xE3,
    0xE3,
    0x04,
    0x04,
    0x04,
    0x04,
    0x24,
    0x24,
    0x24,
    0x24,
    0x45,
    0x45,
    0x45,
    0x45,
    0x65,
    0x65,
    0x65,
    0x65,
    0x86,
    0x86,
    0x86,
    0x86,
    0xA6,
    0xA6,
    0xA6,
    0xA6,
    0xC7,
    0xC7,
    0xC7,
    0xC7,
    0xE7,
    0xE7,
    0xE7,
    0xE7,
    0x08,
    0x08,
    0x08,
    0x08,
    0x28,
    0x28,
    0x28,
    0x28,
    0x49,
    0x49,
    0x49,
    0x49,
    0x69,
    0x69,
    0x69,
    0x69,
    0x8A,
    0x8A,
    0x8A,
    0x8A,
    0xAA,
    0xAA,
    0xAA,
    0xAA,
    0xCB,
    0xCB,
    0xCB,
    0xCB,
    0xEB,
    0xEB,
    0xEB,
    0xEB,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x2C,
    0x2C,
    0x2C,
    0x2C,
    0x4D,
    0x4D,
    0x4D,
    0x4D,
    0x6D,
    0x6D,
    0x6D,
    0x6D,
    0x8E,
    0x8E,
    0x8E,
    0x8E,
    0xAE,
    0xAE,
    0xAE,
    0xAE,
    0xCF,
    0xCF,
    0xCF,
    0xCF,
    0xEF,
    0xEF,
    0xEF,
    0xEF,
    0x10,
    0x10,
    0x10,
    0x10,
    0x30,
    0x30,
    0x30,
    0x30,
    0x51,
    0x51,
    0x51,
    0x51,
    0x71,
    0x71,
    0x71,
    0x71,
    0x92,
    0x92,
    0x92,
    0x92,
    0xB2,
    0xB2,
    0xB2,
    0xB2,
    0xD3,
    0xD3,
    0xD3,
    0xD3,
    0xF3,
    0xF3,
    0xF3,
    0xF3,
    0x14,
    0x14,
    0x14,
    0x14,
    0x34,
    0x34,
    0x34,
    0x34,
    0x55,
    0x55,
    0x55,
    0x55,
    0x75,
    0x75,
    0x75,
    0x75,
    0x96,
    0x96,
    0x96,
    0x96,
    0xB6,
    0xB6,
    0xB6,
    0xB6,
    0xD7,
    0xD7,
    0xD7,
    0xD7,
    0xF7,
    0xF7,
    0xF7,
    0xF7,
    0x18,
    0x18,
    0x18,
    0x18,
    0x38,
    0x38,
    0x38,
    0x38,
    0x59,
    0x59,
    0x59,
    0x59,
    0x79,
    0x79,
    0x79,
    0x79,
    0x9A,
    0x9A,
    0x9A,
    0x9A,
    0xBA,
    0xBA,
    0xBA,
    0xBA,
    0xDB,
    0xDB,
    0xDB,
    0xDB,
    0xFB,
    0xFB,
    0xFB,
    0xFB,
    0x1C,
    0x1C,
    0x1C,
    0x1C,
    0x3C,
    0x3C,
    0x3C,
    0x3C,
    0x5D,
    0x5D,
    0x5D,
    0x5D,
    0x7D,
    0x7D,
    0x7D,
    0x7D,
    0x9E,
    0x9E,
    0x9E,
    0x9E,
    0xBE,
    0xBE,
    0xBE,
    0xBE,
    0xDF,
    0xDF,
    0xDF,
    0xDF,
    0xFF,
    0xFF,
    0xFF,
    0xFF
};


void processFrame() {
  waitForVsync();

  uint8_t pixelRowIndex = 0;
  scanLine = screen_w;

  while (pixelRowIndex < cameraPixelRowCount) {
    waitForPixelClockLow();

    // 2.5 FPS or less:
    //readPixels_loop_line();

    // 5 FPS
    //#define PIXEL_CLOCK_WAITING 1
    //readPixels_loop_line();

    // 10 FPS
    #define PIXEL_CLOCK_WAITING 2
    readPixels_unrolled_x160(0);

    sendLineBufferToDisplay();
    pixelRowIndex++;
  }


}







void waitForVsync()   {
  while(!(PIND & VSYNC_PORTD));
}


#define READ_PIXEL_X160_STEP 20
void readPixels_unrolled_x160(uint16_t byteIndex) {
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 0);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 1);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 2);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 3);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 4);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 5);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 6);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 7);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 8);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 9);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 10);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 11);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 12);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 13);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 14);
  readPixels_unrolled_x10(byteIndex + READ_PIXEL_X160_STEP * 15);
}

#define READ_PIXEL_X10_STEP 2
void readPixels_unrolled_x10(uint16_t byteIndex) {
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 0);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 1);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 2);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 3);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 4);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 5);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 6);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 7);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 8);
  readPixel_unrolled(byteIndex + READ_PIXEL_X10_STEP * 9);
}



void readPixel_unrolled(uint16_t byteIndex) {
  waitForPixelClockRisingEdge();
  lineBuffer[byteIndex + 0] = getPixelByte();
  waitForPixelClockRisingEdge();
  lineBuffer[byteIndex + 1] = getPixelByte();
}



void readPixels_loop_line() {
  uint8_t *buff = lineBuffer;
  uint8_t *buffEnd = buff+ cameraPixelColCount*2;
  while (buff < buffEnd) {
    waitForPixelClockRisingEdge();
    *buff = getPixelByte();
    buff++;
    waitForPixelClockRisingEdge();
    *buff = getPixelByte();
    buff++;
  }
}


void waitForPixelClockLow() {
  while(PINB & PCLOCK_PORTB);
}


void waitForPixelClockRisingEdge() {
#if PIXEL_CLOCK_WAITING == 1
  while(!(PINB & PCLOCK_PORTB));
#elif PIXEL_CLOCK_WAITING == 2
  asm volatile("nop");
#else
  while(PINB & PCLOCK_PORTB);
  while(!(PINB & PCLOCK_PORTB));
#endif
}




uint8_t getPixelByte() {
  return (PINC & LOW_4_BITS_PORTC) | (PIND & HIGH_4_BITS_PORTD);
}




void sendLineBufferToDisplay() {
  screenLineStart();

  uint8_t greyScale;
  uint16_t rgbPixel;


  // bytes from camera are out of sync by one byte
  for (uint16_t i=1; i<(cameraPixelColCount * 2) - 1; i+=2) {
    greyScale = lineBuffer[i];

    //sendPixelByte((gray & 0xF8) | (gray >> 5));
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

  sendPixelByte(0);
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

  screenLineEnd();
}


void screenLineStart()   {
  if (scanLine > 0) scanLine--;
  tft.startAddrWindow(scanLine, 0, scanLine, screen_h-1);
}


void screenLineEnd() {
  tft.endAddrWindow();
}


void sendPixelByte(uint8_t byte) {
  SPDR = byte;
}

