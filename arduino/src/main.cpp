//
// Created by Indrek Luuk on 07.05.16.
//






#include <Arduino.h>
#include "Camera.h"
#include "Screen.h"
#include "line/Line.h"
#include "databuffer/DataBufferSender.h"
#include "databuffer/messagebuffer/LineSegmentMessageBuffer.h"
#include "utils/Utils.h"
#include "ByteInversionTable.h"
#include "MonochromeBufferMask.h"
#include "capture/FrameCapture.h"



const uint8_t COMMAND_LINE_SEGMENT = 0x10;

#define FRAME_CAPTURE_MODE 0


Camera camera;
Screen screen;
Line<camera.getRowCount()> line;
FrameCapture<camera.getRowCount()> frameCapture;
DataBufferSender dataBufferSender;




void processLine(const uint8_t lineIndex);
void processGrayscale();
inline void processGrayScalePixel(int8_t &i, uint8_t &monochromeByte) __attribute__((always_inline));
void processMonochrome(const uint8_t & rowIndex, int8_t linePosition, int8_t altLine1, int8_t altLine2);
inline void processMonochromePixel(
    const uint8_t &rowIndex,
    int8_t &i,
    uint8_t &monochromeByte,
    int8_t lineStart,
    int8_t lineEnd,
    int8_t altLine1,
    int8_t altLine2) __attribute__((always_inline));



bool isLineMessageSent;

uint8_t frameMin;
uint8_t frameMax;
uint8_t frameSpreadThreshold = 0x80;
uint8_t lineThreshold = 0x80;
uint8_t monochromeLineHigh;
uint8_t monochromeLineLow;
uint8_t lineMin;
uint8_t lineMax;





void run() {
  Serial.begin(250000);
  camera.init();
  screen.init();

  noInterrupts();

  while(true) {
    frameMin = 0xFF;
    frameMax = 0x00;
    isLineMessageSent = false;
    line.resetLine();
    camera.readFrame(processLine);
    frameSpreadThreshold = ((frameMax - frameMin) >> 1) ;

#if FRAME_CAPTURE_MODE == 1
    frameCapture.sendCapturedFrame();
#endif
  }
}





void processLine(const uint8_t lineIndex) {
  screen.screenLineStart(lineIndex);
  processGrayscale();
  line.setRowBitmap(lineIndex, monochromeLineHigh, monochromeLineLow);
  int8_t linePosition = -1;
  int8_t altLine1 = -1;
  int8_t altLine2 = -1;
  if (line.isIdentifiedLine()) {
    linePosition = line.getIdentifiedLine();
  } else if (line.isLineTopFound() && (line.getLineTopRowIndex() + 5  > lineIndex)) {
    // make line top more visible;
    linePosition = line.getLineTopPosition();
  }
  if (line.isSplitDetectionLine()) {
    altLine1 = line.getFirstSplitDetectionLine();
    altLine2 = line.getSecondSplitDetectionLine();
  }
  processMonochrome(lineIndex, ((linePosition  * 5) >> 1) + 2, ((altLine1  * 5) >> 1) + 2, ((altLine2  * 5) >> 1) + 2);
  screen.screenLineEnd();

#if FRAME_CAPTURE_MODE == 1
  frameCapture.addRow(lineIndex, monochromeLineHigh, monochromeLineLow);
#endif

  if (!isLineMessageSent && line.isLineTopFound()) {
    LineSegmentMessageBuffer message;
    message.lineBottomIndex = (uint8_t)line.getLineBottomRowIndex();
    message.lineBottomPosition = (uint8_t)line.getLineBottomPosition();
    message.lineTopIndex = (uint8_t)line.getLineTopRowIndex();
    message.lineTopPosition = (uint8_t)line.getLineTopPosition();
    message.isEndOfLine = (uint8_t)line.getIsEndOfLine();
    dataBufferSender.sendMessage(COMMAND_LINE_SEGMENT, (uint8_t *)&message, sizeof(message));
    isLineMessageSent = true;
  }

  // if no line found then send dummy line at the top of the screen
  if (!isLineMessageSent && (lineIndex == (camera.getRowCount()-1))) {
    LineSegmentMessageBuffer message;
    message.lineBottomIndex = camera.getRowCount() - 2;
    message.lineBottomPosition = LineSegment::rowRangeMidPoint;
    message.lineTopIndex = camera.getRowCount() - 1;
    message.lineTopPosition = LineSegment::rowRangeMidPoint;
    message.isEndOfLine = true;
    dataBufferSender.sendMessage(COMMAND_LINE_SEGMENT, (uint8_t *)&message, sizeof(message));
    isLineMessageSent = true;
  }

}





void processGrayscale() {
  monochromeLineLow = 0;
  monochromeLineHigh = 0;
  lineMin = 0xFF;
  lineMax = 0;

  for (int8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    processGrayScalePixel(i, monochromeLineLow);
  }

  for (int8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    processGrayScalePixel(i, monochromeLineHigh);
  }

  uint8_t lineSpread = lineMax - lineMin;
  if (lineSpread > frameSpreadThreshold) {
    lineThreshold = lineMin + (lineSpread >> 1);
  }
  if (frameMin < lineMin) frameMin = lineMin;
  if (frameMax > lineMax) frameMax = lineMax;
}


void processGrayScalePixel(int8_t &i, uint8_t &monochromeByte) {
  uint8_t pixelByte = camera.getPixelByte(i);

  screen.sendGrayscalePixelHigh(pixelByte);
  // asm volatile("nop");

  uint8_t correctedPixel = byteInversionTable[pixelByte];
  monochromeByte |= correctedPixel > lineThreshold ? 0x00 : monochromeBufferMask[i];

  screen.sendGrayscalePixelLow(pixelByte);
  // asm volatile("nop");

  if (lineMin > correctedPixel) lineMin = correctedPixel;
  if (lineMax < correctedPixel) lineMax = correctedPixel;
}






void processMonochrome(const uint8_t & rowIndex, int8_t linePosition, int8_t altLine1, int8_t altLine2) {
  int8_t lineStart;
  int8_t lineEnd;
  if (linePosition < 0) {
    lineStart = -1;
    lineEnd = -1;
  } else {
    lineStart = linePosition > 1 ? linePosition - 2 : 0;
    lineEnd = linePosition +2;
  }

  for (int8_t i=0; i<camera.getPixelBufferLength()/2; i++) {
    processMonochromePixel(rowIndex, i, monochromeLineLow, lineStart, lineEnd, altLine1, altLine2);
  }
  for (int8_t i=camera.getPixelBufferLength()/2; i<camera.getPixelBufferLength(); i++) {
    processMonochromePixel(rowIndex, i, monochromeLineHigh, lineStart, lineEnd, altLine1, altLine2);
  }
}



void processMonochromePixel(
    const uint8_t &rowIndex,
    int8_t &i,
    uint8_t &monochromeByte,
    int8_t lineStart,
    int8_t lineEnd,
    int8_t altLine1,
    int8_t altLine2
) {
  uint8_t monochromeMask = monochromeBufferMask[i];
  if (monochromeByte & monochromeMask) {
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    screen.sendPixelByte(0);
  } else {
    screen.sendPixelByte((0xAA & monochromeMask ? 0xFD : 0xFF));
  }

  if (altLine1 >= 0 || altLine2 >=0) {
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    screen.sendPixelByte(altLine2 == i || altLine1 == i ? 0xFF : 0);
  } else {
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    if (i < lineStart) {
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      screen.sendPixelByte(0);
    } else {
      screen.sendPixelByte(i > lineEnd ? 0 : 0xFF);
    }
  }


  /*
  // 16 pixel lines
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  screen.sendPixelByte((rowIndex & 0x0F) == 0 ? 0xFF: 0);
   */

}









