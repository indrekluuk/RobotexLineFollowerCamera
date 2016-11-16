//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"



class RowLinePosition {

    uint8_t bitmapHigh;
    uint8_t bitmapLow;

public:

    static const int8_t rowRange = 30;
    static const int8_t rowRangeMidPoint = rowRange / 2;
    static const int8_t lineNotFound = -1;


    RowLinePosition(uint8_t bitmapHigh, uint8_t bitmapLow) : bitmapHigh(bitmapHigh), bitmapLow(bitmapLow) {
    };

    /*
    static const int8_t getRange() { return rowRange;};
    static const int8_t getRangeMidPoint() { return rowRangeMidPoint;};
*/
    static const bool isInRange(int8_t linePos) { return linePos >= 0 && linePos <= rowRange;};
    static const bool isLineNotFound(int8_t linePos) { return linePos == lineNotFound;};

    inline int8_t getLinePosition(int8_t seekPos) __attribute__((always_inline));
    inline void processPixel(bool isActive, uint8_t index, int8_t &line, int8_t &start, int8_t &seekPos) __attribute__((always_inline));
    inline int8_t processLineSegment(int8_t seekPos, int8_t prevLinePos, int8_t lineStart, int8_t lineEnd) __attribute__((always_inline));
};




int8_t RowLinePosition::getLinePosition(int8_t seekPos) {
  int8_t line = lineNotFound;
  int8_t start = lineNotFound;

  processPixel(bitmapLow  & (uint8_t)0b00000001, 0,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00000010, 2,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00000100, 4,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00001000, 6,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00010000, 8,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00100000, 10,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b01000000, 12, line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b10000000, 14, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000001, 16, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000010, 18, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000100, 20, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00001000, 22, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00010000, 24, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00100000, 26, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b01000000, 28, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b10000000, 30, line, start, seekPos);

  if (start != lineNotFound) {
    line = processLineSegment(seekPos, line, start, 30);
  }

  return line;
}



void RowLinePosition::processPixel(bool isActive, uint8_t index, int8_t &line, int8_t &start, int8_t &seekPos) {
  if (isActive) {
    if (start == lineNotFound) {
      start = index;
    }
  } else {
    if (start != lineNotFound) {
      line = processLineSegment(seekPos, line, start, index - (uint8_t)2);
    }
    start = lineNotFound;
  }
}



int8_t RowLinePosition::processLineSegment(int8_t seekPos, int8_t prevLinePos, int8_t lineStart, int8_t lineEnd) {
  int8_t newLinePos = (int8_t)((lineEnd + lineStart) >> 1);
  if (prevLinePos == lineNotFound || (abs(seekPos-newLinePos) < abs(seekPos-prevLinePos))) {
    return newLinePos;
  } else {
    return prevLinePos;
  }
}







#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
