
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
  uint8_t* rgbPixelBytes;


  // bytes from camera are out of sync by one byte
  uint16_t end = (cameraPixelColCount * 2) - 1;
  for (uint16_t i=1; i<end; i+=2) {
    greyScale = lineBuffer[i];
    rgbPixel = rgbGreyScale(greyScale);
    //rgbPixelBytes =

    //sendPixelByte((gray & 0xF8) | (gray >> 5));
    sendPixelByte(((uint8_t*)(&rgbPixel))[1]);
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
    //asm volatile("nop");
    //asm volatile("nop");


    //sendPixelByte((gray << 3) | (gray >> 3));
    sendPixelByte(((uint8_t*)(&rgbPixel))[0]);
    asm volatile("nop");
    asm volatile("nop");/*
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
*/

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




uint16_t rgbGreyScale(uint8_t greysCale) {
  switch (greysCale) {
    case 0: return 0x0;
    case 1: return 0x0;
    case 2: return 0x0;
    case 3: return 0x0;
    case 4: return 0x20;
    case 5: return 0x20;
    case 6: return 0x20;
    case 7: return 0x20;
    case 8: return 0x841;
    case 9: return 0x841;
    case 10: return 0x841;
    case 11: return 0x841;
    case 12: return 0x861;
    case 13: return 0x861;
    case 14: return 0x861;
    case 15: return 0x861;
    case 16: return 0x1082;
    case 17: return 0x1082;
    case 18: return 0x1082;
    case 19: return 0x1082;
    case 20: return 0x10A2;
    case 21: return 0x10A2;
    case 22: return 0x10A2;
    case 23: return 0x10A2;
    case 24: return 0x18C3;
    case 25: return 0x18C3;
    case 26: return 0x18C3;
    case 27: return 0x18C3;
    case 28: return 0x18E3;
    case 29: return 0x18E3;
    case 30: return 0x18E3;
    case 31: return 0x18E3;
    case 32: return 0x2104;
    case 33: return 0x2104;
    case 34: return 0x2104;
    case 35: return 0x2104;
    case 36: return 0x2124;
    case 37: return 0x2124;
    case 38: return 0x2124;
    case 39: return 0x2124;
    case 40: return 0x2945;
    case 41: return 0x2945;
    case 42: return 0x2945;
    case 43: return 0x2945;
    case 44: return 0x2965;
    case 45: return 0x2965;
    case 46: return 0x2965;
    case 47: return 0x2965;
    case 48: return 0x3186;
    case 49: return 0x3186;
    case 50: return 0x3186;
    case 51: return 0x3186;
    case 52: return 0x31A6;
    case 53: return 0x31A6;
    case 54: return 0x31A6;
    case 55: return 0x31A6;
    case 56: return 0x39C7;
    case 57: return 0x39C7;
    case 58: return 0x39C7;
    case 59: return 0x39C7;
    case 60: return 0x39E7;
    case 61: return 0x39E7;
    case 62: return 0x39E7;
    case 63: return 0x39E7;
    case 64: return 0x4208;
    case 65: return 0x4208;
    case 66: return 0x4208;
    case 67: return 0x4208;
    case 68: return 0x4228;
    case 69: return 0x4228;
    case 70: return 0x4228;
    case 71: return 0x4228;
    case 72: return 0x4A49;
    case 73: return 0x4A49;
    case 74: return 0x4A49;
    case 75: return 0x4A49;
    case 76: return 0x4A69;
    case 77: return 0x4A69;
    case 78: return 0x4A69;
    case 79: return 0x4A69;
    case 80: return 0x528A;
    case 81: return 0x528A;
    case 82: return 0x528A;
    case 83: return 0x528A;
    case 84: return 0x52AA;
    case 85: return 0x52AA;
    case 86: return 0x52AA;
    case 87: return 0x52AA;
    case 88: return 0x5ACB;
    case 89: return 0x5ACB;
    case 90: return 0x5ACB;
    case 91: return 0x5ACB;
    case 92: return 0x5AEB;
    case 93: return 0x5AEB;
    case 94: return 0x5AEB;
    case 95: return 0x5AEB;
    case 96: return 0x630C;
    case 97: return 0x630C;
    case 98: return 0x630C;
    case 99: return 0x630C;
    case 100: return 0x632C;
    case 101: return 0x632C;
    case 102: return 0x632C;
    case 103: return 0x632C;
    case 104: return 0x6B4D;
    case 105: return 0x6B4D;
    case 106: return 0x6B4D;
    case 107: return 0x6B4D;
    case 108: return 0x6B6D;
    case 109: return 0x6B6D;
    case 110: return 0x6B6D;
    case 111: return 0x6B6D;
    case 112: return 0x738E;
    case 113: return 0x738E;
    case 114: return 0x738E;
    case 115: return 0x738E;
    case 116: return 0x73AE;
    case 117: return 0x73AE;
    case 118: return 0x73AE;
    case 119: return 0x73AE;
    case 120: return 0x7BCF;
    case 121: return 0x7BCF;
    case 122: return 0x7BCF;
    case 123: return 0x7BCF;
    case 124: return 0x7BEF;
    case 125: return 0x7BEF;
    case 126: return 0x7BEF;
    case 127: return 0x7BEF;
    case 128: return 0x8410;
    case 129: return 0x8410;
    case 130: return 0x8410;
    case 131: return 0x8410;
    case 132: return 0x8430;
    case 133: return 0x8430;
    case 134: return 0x8430;
    case 135: return 0x8430;
    case 136: return 0x8C51;
    case 137: return 0x8C51;
    case 138: return 0x8C51;
    case 139: return 0x8C51;
    case 140: return 0x8C71;
    case 141: return 0x8C71;
    case 142: return 0x8C71;
    case 143: return 0x8C71;
    case 144: return 0x9492;
    case 145: return 0x9492;
    case 146: return 0x9492;
    case 147: return 0x9492;
    case 148: return 0x94B2;
    case 149: return 0x94B2;
    case 150: return 0x94B2;
    case 151: return 0x94B2;
    case 152: return 0x9CD3;
    case 153: return 0x9CD3;
    case 154: return 0x9CD3;
    case 155: return 0x9CD3;
    case 156: return 0x9CF3;
    case 157: return 0x9CF3;
    case 158: return 0x9CF3;
    case 159: return 0x9CF3;
    case 160: return 0xA514;
    case 161: return 0xA514;
    case 162: return 0xA514;
    case 163: return 0xA514;
    case 164: return 0xA534;
    case 165: return 0xA534;
    case 166: return 0xA534;
    case 167: return 0xA534;
    case 168: return 0xAD55;
    case 169: return 0xAD55;
    case 170: return 0xAD55;
    case 171: return 0xAD55;
    case 172: return 0xAD75;
    case 173: return 0xAD75;
    case 174: return 0xAD75;
    case 175: return 0xAD75;
    case 176: return 0xB596;
    case 177: return 0xB596;
    case 178: return 0xB596;
    case 179: return 0xB596;
    case 180: return 0xB5B6;
    case 181: return 0xB5B6;
    case 182: return 0xB5B6;
    case 183: return 0xB5B6;
    case 184: return 0xBDD7;
    case 185: return 0xBDD7;
    case 186: return 0xBDD7;
    case 187: return 0xBDD7;
    case 188: return 0xBDF7;
    case 189: return 0xBDF7;
    case 190: return 0xBDF7;
    case 191: return 0xBDF7;
    case 192: return 0xC618;
    case 193: return 0xC618;
    case 194: return 0xC618;
    case 195: return 0xC618;
    case 196: return 0xC638;
    case 197: return 0xC638;
    case 198: return 0xC638;
    case 199: return 0xC638;
    case 200: return 0xCE59;
    case 201: return 0xCE59;
    case 202: return 0xCE59;
    case 203: return 0xCE59;
    case 204: return 0xCE79;
    case 205: return 0xCE79;
    case 206: return 0xCE79;
    case 207: return 0xCE79;
    case 208: return 0xD69A;
    case 209: return 0xD69A;
    case 210: return 0xD69A;
    case 211: return 0xD69A;
    case 212: return 0xD6BA;
    case 213: return 0xD6BA;
    case 214: return 0xD6BA;
    case 215: return 0xD6BA;
    case 216: return 0xDEDB;
    case 217: return 0xDEDB;
    case 218: return 0xDEDB;
    case 219: return 0xDEDB;
    case 220: return 0xDEFB;
    case 221: return 0xDEFB;
    case 222: return 0xDEFB;
    case 223: return 0xDEFB;
    case 224: return 0xE71C;
    case 225: return 0xE71C;
    case 226: return 0xE71C;
    case 227: return 0xE71C;
    case 228: return 0xE73C;
    case 229: return 0xE73C;
    case 230: return 0xE73C;
    case 231: return 0xE73C;
    case 232: return 0xEF5D;
    case 233: return 0xEF5D;
    case 234: return 0xEF5D;
    case 235: return 0xEF5D;
    case 236: return 0xEF7D;
    case 237: return 0xEF7D;
    case 238: return 0xEF7D;
    case 239: return 0xEF7D;
    case 240: return 0xF79E;
    case 241: return 0xF79E;
    case 242: return 0xF79E;
    case 243: return 0xF79E;
    case 244: return 0xF7BE;
    case 245: return 0xF7BE;
    case 246: return 0xF7BE;
    case 247: return 0xF7BE;
    case 248: return 0xFFDF;
    case 249: return 0xFFDF;
    case 250: return 0xFFDF;
    case 251: return 0xFFDF;
    case 252: return 0xFFFF;
    case 253: return 0xFFFF;
    case 254: return 0xFFFF;
    case 255: return 0xFFFF;
  }
}


