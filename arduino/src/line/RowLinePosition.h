//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"



class RowLinePosition {

    uint8_t bitmapHigh;
    uint8_t bitmapLow;
    int8_t lineSegmentStart;
    int8_t lineSegmentEnd;
    int8_t lineSeekPos;
    int8_t linePos;

public:

    static const int8_t rowRange = 30;
    static const int8_t rowRangeMidPoint = rowRange / 2;
    static const int8_t lineNotFound = -1;


    RowLinePosition(uint8_t bitmapHigh, uint8_t bitmapLow, int8_t seekPos);

    inline static const bool isInRange(int8_t linePos) __attribute__((always_inline));
    inline static const bool isLineNotFound(int8_t linePos) __attribute__((always_inline));
    inline static bool isOnEdge(int8_t position) __attribute__((always_inline));
    inline bool isLineNotFound() __attribute__((always_inline));
    inline int8_t getLinePosition() __attribute__((always_inline));
    inline int8_t getLineSegmentStart() __attribute__((always_inline));
    inline int8_t getLineSegmentEnd() __attribute__((always_inline));

    inline static int8_t getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

private:
    inline void processPixel(bool isActive, uint8_t index, int8_t &segmentStart) __attribute__((always_inline));
    inline void processLineSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

};




void RowLinePosition::processPixel(bool isActive, uint8_t index, int8_t &segmentStart) {
  if (isActive) {
    if (segmentStart == lineNotFound) {
      segmentStart = index;
    }
  } else {
    if (segmentStart != lineNotFound) {
      processLineSegment(segmentStart, index - (uint8_t)2);
    }
    segmentStart = lineNotFound;
  }
}




void RowLinePosition::processLineSegment(int8_t segmentStart, int8_t segmentEnd) {
  int8_t newLinePos = getLinePositionForSegment(segmentStart, segmentEnd);
  if (linePos == lineNotFound || (abs(lineSeekPos-newLinePos) < abs(lineSeekPos-linePos))) {
    linePos = newLinePos;
    lineSegmentStart = segmentStart;
    lineSegmentEnd = segmentEnd;
  }
}


int8_t RowLinePosition::getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) {
  return (int8_t)((segmentEnd + segmentStart) >> 1);
}




const bool RowLinePosition::isInRange(int8_t linePos) {
  return linePos >= 0 && linePos <= rowRange;
}

bool RowLinePosition::isLineNotFound() {
  return isLineNotFound(linePos);
}

const bool RowLinePosition::isLineNotFound(int8_t linePos) {
  return linePos == lineNotFound;
}

bool RowLinePosition::isOnEdge(int8_t position) {
  return position == 0 || position == rowRange;
}

int8_t RowLinePosition::getLinePosition() {
  return linePos;
}

int8_t RowLinePosition::getLineSegmentStart() {
  return lineSegmentStart;
}

int8_t RowLinePosition::getLineSegmentEnd() {
  return lineSegmentEnd;
}






#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
