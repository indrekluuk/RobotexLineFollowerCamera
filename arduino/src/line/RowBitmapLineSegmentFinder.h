//
// Created by indrek on 13.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H
#define ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H


#include "Arduino.h"
#include "LineSegment.h"



class RowBitmapLineSegmentFinder {

    // Ignore possible noise.
    // First rows can be noisi. Sometimes wheel is visible from the corner.
    static const uint8_t ignoreRows = 5;
    static const uint8_t ignore2pixelsOnCornersRows = 10;
    static const uint8_t ignore1pixelOnCornersRows = 25;

    uint8_t rowIndex;
    uint8_t bitmapHigh;
    uint8_t bitmapLow;

    LineSegment lineSegment1;
    LineSegment lineSegment2;
    LineSegment * lineSeekSegment;

public:


    RowBitmapLineSegmentFinder(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow, LineSegment * lineSeekSegment);

    inline bool isLineFound() __attribute__((always_inline));
    inline LineSegment & getFoundLineSegment() __attribute__((always_inline));
    static uint8_t getIgnoreRowCount() {return ignoreRows;}


private:
    inline void processPixel(bool isActive, uint8_t index, int8_t &segmentStart) __attribute__((always_inline));
    inline void processLineSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));
    inline bool isHigherPrioritySegment(LineSegment & lineSegment) __attribute__((always_inline));
    inline bool isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));

};




void RowBitmapLineSegmentFinder::processPixel(bool isActive, uint8_t index, int8_t &segmentStart) {
  if (isActive) {
    if (segmentStart == LineSegment::lineNotFound) {
      segmentStart = index;
    }
  } else {
    if (segmentStart != LineSegment::lineNotFound) {
      processLineSegment(segmentStart, index - (uint8_t)2);
    }
    segmentStart = LineSegment::lineNotFound;
  }
}






void RowBitmapLineSegmentFinder::processLineSegment(int8_t segmentStart, int8_t segmentEnd) {
  if (!isIgnoreSegment(segmentStart, segmentEnd)) {
    LineSegment newLineSegment(segmentStart, segmentEnd, lineSeekSegment);

    if (lineSegment1.isLineNotFound()) {
      lineSegment1 = newLineSegment;
    } else {
      if (isHigherPrioritySegment(newLineSegment)) {
        lineSegment1 = newLineSegment;
      }
    }
  }
}




bool RowBitmapLineSegmentFinder::isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) {
  // if seek range is set then no need to ignore
  if (lineSeekSegment != nullptr) {
    return false;
  }

  // ignore segments that start and end in the corner
  if (rowIndex < ignore2pixelsOnCornersRows) {
    return (segmentStart <= 2 || segmentStart >= LineSegment::rowRange - 2)
        && (segmentEnd <= 2 || segmentEnd >= LineSegment::rowRange - 2);
  } else if (rowIndex < ignore1pixelOnCornersRows) {
    return (segmentStart == 0 || segmentStart == LineSegment::rowRange)
           && (segmentEnd == 0 || segmentEnd == LineSegment::rowRange);
  } else {
    return false;
  }
}





bool RowBitmapLineSegmentFinder::isHigherPrioritySegment(LineSegment & lineSegment) {
  // 1. Segments touching
  // 2. if both segment touching then the one closest to mid-screen
  // 3. if neither segment touching then closest to last seek point

  if (lineSegment1.isTouchingSeekSegment() != lineSegment.isTouchingSeekSegment()) {
    return lineSegment.isTouchingSeekSegment();
  } else {
    if (lineSegment.isTouchingSeekSegment()) {
      return (abs(LineSegment::rowRangeMidPoint-lineSegment.getLinePosition())
              < abs(LineSegment::rowRangeMidPoint-lineSegment1.getLinePosition()));
    } else {
      int8_t pos = lineSeekSegment == nullptr ? LineSegment::rowRangeMidPoint : lineSeekSegment->getCenter();
      return (abs(pos-lineSegment.getLinePosition())
              < abs(pos-lineSegment1.getLinePosition()));
    }
  }
}




bool RowBitmapLineSegmentFinder::isLineFound() {
  return !lineSegment1.isLineNotFound();
}


LineSegment & RowBitmapLineSegmentFinder::getFoundLineSegment() {
  return lineSegment1;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H



