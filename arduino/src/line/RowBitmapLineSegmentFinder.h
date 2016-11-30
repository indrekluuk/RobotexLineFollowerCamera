//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"



class RowBitmapLineSegmentFinder {


    static const uint8_t ignoreRows = 5;
    static const uint8_t ignore2pixelsOnCornersRows = 10;
    static const uint8_t ignore1pixelOnCornersRows = 25;



    uint8_t rowIndex;
    uint8_t bitmapHigh;
    uint8_t bitmapLow;

    int8_t lineSegmentStart;
    int8_t lineSegmentEnd;
    int8_t linePos;
    bool  lineTouchesSeekSegment;

    int8_t lineBeforeSegmentStart;
    int8_t lineBeforeSegmentEnd;
    int8_t lineBeforePos;

    int8_t lineAfterSegmentStart;
    int8_t lineAfterSegmentEnd;
    int8_t lineAfterPos;

    int8_t lineSeekStart;
    int8_t lineSeekEnd;
    int8_t lineSeekPosition;

public:

    static const int8_t rowRange = 30;
    static const int8_t rowRangeMidPoint = rowRange >> 1;
    static const int8_t lineNotFound = -1;


    RowBitmapLineSegmentFinder(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow, int8_t lineSeekStart, int8_t lineSeekEnd);

    inline static const bool isInRange(int8_t linePos) __attribute__((always_inline));
    inline static const bool isLineNotFound(int8_t linePos) __attribute__((always_inline));
    inline static bool isOnEdge(int8_t position) __attribute__((always_inline));

    inline bool isLineNotFound() __attribute__((always_inline));
    inline int8_t getLinePosition() __attribute__((always_inline));
    inline int8_t getLineSegmentStart() __attribute__((always_inline));
    inline int8_t getLineSegmentEnd() __attribute__((always_inline));

    inline bool isLineBefore() __attribute__((always_inline));
    inline int8_t getLineBeforePosition() __attribute__((always_inline));
    inline int8_t getLineBeforeSegmentStart() __attribute__((always_inline));
    inline int8_t getLineBeforeSegmentEnd() __attribute__((always_inline));

    inline bool isLineAfter() __attribute__((always_inline));
    inline int8_t getLineAfterPosition() __attribute__((always_inline));
    inline int8_t getLineAfterSegmentStart() __attribute__((always_inline));
    inline int8_t getLineAfterSegmentEnd() __attribute__((always_inline));


    static uint8_t getIgnoreRowCount() {return ignoreRows;}

    inline int8_t getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

    inline static bool areSegmentsTouching(int8_t start1, int8_t end1, int8_t start2, int8_t end2) __attribute__((always_inline));

private:
    inline void processPixel(bool isActive, uint8_t index, int8_t &segmentStart) __attribute__((always_inline));
    inline void processLineSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));
    inline bool isHigherPrioritySegment(int8_t newLinePos, bool isNewSegmentTouchingSeekSegment) __attribute__((always_inline));
    inline bool isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));


};




void RowBitmapLineSegmentFinder::processPixel(bool isActive, uint8_t index, int8_t &segmentStart) {
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




void RowBitmapLineSegmentFinder::processLineSegment(int8_t segmentStart, int8_t segmentEnd) {
  if (!isIgnoreSegment(segmentStart, segmentEnd)) {
    int8_t newLinePos = getLinePositionForSegment(segmentStart, segmentEnd);
    bool newSegmentTouchesSeekSegment = areSegmentsTouching(segmentStart, segmentEnd, lineSeekStart,lineSeekEnd);
    if (linePos == lineNotFound) {
      linePos = newLinePos;
      lineSegmentStart = segmentStart;
      lineSegmentEnd = segmentEnd;
      lineTouchesSeekSegment = newSegmentTouchesSeekSegment;
    } else {

      if (isHigherPrioritySegment(newLinePos, newSegmentTouchesSeekSegment)) {
        lineBeforeSegmentStart = lineSegmentStart;
        lineBeforeSegmentEnd = lineSegmentEnd;
        lineBeforePos = linePos;

        linePos = newLinePos;
        lineSegmentStart = segmentStart;
        lineSegmentEnd = segmentEnd;
        lineTouchesSeekSegment = newSegmentTouchesSeekSegment;
      } else if (lineAfterPos == lineNotFound) {
        lineAfterPos = newLinePos;
        lineAfterSegmentStart = segmentStart;
        lineAfterSegmentEnd = segmentEnd;
      }
    }
  }
}


bool RowBitmapLineSegmentFinder::isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) {
  if (lineSeekStart != lineNotFound) {
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



bool RowBitmapLineSegmentFinder::isHigherPrioritySegment(int8_t newLinePos, bool isNewSegmentTouchingSeekSegment) {

  // 1. Segments touching
  // 2. if both segment touching then the one closest to mid-screen
  // 3. if neither segment touching then closest to last seek point

  if (lineTouchesSeekSegment != isNewSegmentTouchingSeekSegment) {
    return isNewSegmentTouchingSeekSegment;
  } else {
    if (isNewSegmentTouchingSeekSegment) {
      return (abs(rowRangeMidPoint-newLinePos) < abs(rowRangeMidPoint-linePos));
    } else {
      return (abs(lineSeekPosition-newLinePos) < abs(lineSeekPosition-linePos));
    }
  }
}




bool RowBitmapLineSegmentFinder::areSegmentsTouching(int8_t start1, int8_t end1, int8_t start2, int8_t end2) {
  return ((end1 - start2 >= -2) && (end2- start1 >= -2));
}




int8_t RowBitmapLineSegmentFinder::getLinePositionForSegment(int8_t segmentStart, int8_t segmentEnd) {
  if (segmentStart > 0 && segmentEnd < rowRange) {
    return (int8_t)((segmentEnd + segmentStart) >> 1);
  } else if (segmentStart == 0 && segmentEnd == rowRange) {
    if (lineSeekStart == lineNotFound) {
      return rowRangeMidPoint;
    } else {
      return ((lineSeekStart + lineSeekEnd)>>1) > rowRangeMidPoint ? segmentEnd : segmentStart;
    }
  } else {
    if (segmentStart == 0) {
      return segmentStart;
    } else {
      return segmentEnd;
    }
  }
}




const bool RowBitmapLineSegmentFinder::isInRange(int8_t linePos) {
  return linePos >= 0 && linePos <= rowRange;
}

bool RowBitmapLineSegmentFinder::isLineNotFound() {
  return isLineNotFound(linePos);
}

const bool RowBitmapLineSegmentFinder::isLineNotFound(int8_t linePos) {
  return linePos == lineNotFound;
}

bool RowBitmapLineSegmentFinder::isOnEdge(int8_t position) {
  return position == 0 || position == rowRange;
}

int8_t RowBitmapLineSegmentFinder::getLinePosition() {
  return linePos;
}

int8_t RowBitmapLineSegmentFinder::getLineSegmentStart() {
  return lineSegmentStart;
}

int8_t RowBitmapLineSegmentFinder::getLineSegmentEnd() {
  return lineSegmentEnd;
}


bool RowBitmapLineSegmentFinder::isLineBefore() {
  return !isLineNotFound(lineBeforePos);
}

int8_t RowBitmapLineSegmentFinder::getLineBeforePosition() {
  return lineBeforePos;
}

int8_t RowBitmapLineSegmentFinder::getLineBeforeSegmentStart() {
  return lineBeforeSegmentStart;
}

int8_t RowBitmapLineSegmentFinder::getLineBeforeSegmentEnd() {
  return lineBeforeSegmentEnd;
}



bool RowBitmapLineSegmentFinder::isLineAfter() {
  return !isLineNotFound(lineAfterPos);
}

int8_t RowBitmapLineSegmentFinder::getLineAfterPosition() {
  return lineAfterPos;
}

int8_t RowBitmapLineSegmentFinder::getLineAfterSegmentStart() {
  return lineAfterSegmentStart;
}

int8_t RowBitmapLineSegmentFinder::getLineAfterSegmentEnd() {
  return lineAfterSegmentEnd;
}





#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
