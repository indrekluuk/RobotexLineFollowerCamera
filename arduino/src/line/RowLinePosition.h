//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"



class RowLinePosition {

    static const int8_t rowRange = 13;
    static const int8_t lineNotFound = (rowRange * 2) + 2;


    uint8_t bitmapHigh;
    uint8_t bitmapLow;

public:
    RowLinePosition(uint8_t bitmapHigh, uint8_t bitmapLow) : bitmapHigh(bitmapHigh), bitmapLow(bitmapLow) {
    };

    static const int8_t getRowRange() { return rowRange;};
    static const bool isInRange(int8_t linePos) { return abs(linePos) <= rowRange;};
    static const bool isLineNotFound(int8_t linePos) { return linePos == lineNotFound;};

    inline int8_t getLinePosition(int8_t seekPos) __attribute__((always_inline));
    inline void processPixel(bool isActive, uint8_t index, int8_t &line, int8_t &start, int8_t &seekPos) __attribute__((always_inline));
    inline int8_t processLineSegment(int8_t seekPos, int8_t prevLinePos, int8_t lineStart, int8_t lineEnd) __attribute__((always_inline));
};




int8_t RowLinePosition::getLinePosition(int8_t seekPos) {
  seekPos += rowRange;
  int8_t line = lineNotFound;
  int8_t start = lineNotFound;

  processPixel(bitmapLow  & (uint8_t)0b00000010, 0,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00000100, 2,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00001000, 4,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00010000, 6,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b00100000, 8,  line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b01000000, 10, line, start, seekPos);
  processPixel(bitmapLow  & (uint8_t)0b10000000, 12, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000001, 14, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000010, 16, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00000100, 18, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00001000, 20, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00010000, 22, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b00100000, 24, line, start, seekPos);
  processPixel(bitmapHigh & (uint8_t)0b01000000, 26, line, start, seekPos);

  if (start != lineNotFound) {
    line = processLineSegment(seekPos, line, start, rowRange*2);
  }

  return lineNotFound == line ? lineNotFound : (line) - rowRange;
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
  if (abs(seekPos-newLinePos) < abs(seekPos-prevLinePos)) {
    return newLinePos;
  } else {
    return prevLinePos;
  }
}







#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
