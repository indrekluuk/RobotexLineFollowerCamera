//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"



class RowLinePosition {


    static const uint8_t ignoreRows = 5;
    static const uint8_t ignore2pixelsOnCornersRows = 10;
    static const uint8_t ignore1pixelOnCornersRows = 25;



    uint8_t rowIndex;
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


    RowLinePosition(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow, int8_t seekPos);

    inline static const bool isInRange(int8_t linePos) __attribute__((always_inline));
    inline static const bool isLineNotFound(int8_t linePos) __attribute__((always_inline));
    inline static bool isOnEdge(int8_t position) __attribute__((always_inline));
    inline bool isLineNotFound() __attribute__((always_inline));
    inline int8_t getLinePosition() __attribute__((always_inline));
    inline int8_t getLineSegmentStart() __attribute__((always_inline));
    inline int8_t getLineSegmentEnd() __attribute__((always_inline));

    static uint8_t getIgnoreRowCount() {return ignoreRows;}

    inline static int8_t getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

private:
    inline void processPixel(bool isActive, uint8_t index, int8_t &segmentStart) __attribute__((always_inline));
    inline void processLineSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));
    inline bool isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

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
  if (!isIgnoreSegment(segmentStart, segmentEnd)) {
    int8_t newLinePos = getLinePositionForSegment(segmentStart, segmentEnd);
    if (linePos == lineNotFound || (abs(lineSeekPos-newLinePos) < abs(lineSeekPos-linePos))) {
      linePos = newLinePos;
      lineSegmentStart = segmentStart;
      lineSegmentEnd = segmentEnd;
    }
  }
}


bool RowLinePosition::isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) {
  if (lineSeekPos != lineNotFound) {
    return false;
  }
  if (rowIndex < ignore2pixelsOnCornersRows) {
    return (segmentStart <= 2 || segmentStart >= rowRange - 2)
        && (segmentEnd <= 2 || segmentEnd >= rowRange - 2);
  } else if (rowIndex < ignore1pixelOnCornersRows) {
    return (segmentStart == 0 || segmentStart == rowRange)
           && (segmentEnd == 0 || segmentEnd == rowRange);
  } else {
    return false;
  }
}


int8_t RowLinePosition::getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) {
  if ((segmentStart != 0 && segmentEnd != rowRange)
      || (segmentStart == 0 && segmentEnd == rowRange)) {
    return (int8_t)((segmentEnd + segmentStart) >> 1);
  } else {
    if (segmentStart == 0) {
      return segmentStart;
    } else {
      return segmentEnd;
    }
  }
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
