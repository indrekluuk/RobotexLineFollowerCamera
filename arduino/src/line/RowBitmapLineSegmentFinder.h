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

    uint8_t currentRowIndex;


    LineSegment firstLineSegment;
    LineSegment firstLineSegmentPreviousRow;

    LineSegment secondLineSegment;
    LineSegment secondLineSegmentPreviousRow;


public:


    RowBitmapLineSegmentFinder();

    void reset();
    void nextRow(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow, LineSegment seekSegment);
    void nextRow(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);


    inline bool isLineFound() __attribute__((always_inline));
    inline bool isSingleLineFound() __attribute__((always_inline));
    inline LineSegment & getSingleLine() __attribute__((always_inline));
    inline bool isLineSplit() __attribute__((always_inline));
    inline LineSegment & getFirstLine() __attribute__((always_inline));
    inline LineSegment & getSecondLine() __attribute__((always_inline));

    static uint8_t getIgnoreRowCount() {return ignoreRows;}


private:
    inline void processPixel(bool isActive, uint8_t index, int8_t &segmentStart) __attribute__((always_inline));
    inline void processLineSegment(int8_t segmentStart, int8_t segmentEnd) __attribute__((always_inline));
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
    LineSegment newLineSegment(segmentStart, segmentEnd);

    if (!firstLineSegmentPreviousRow.isLineFound()) {

      // for the first line find closest to the mid-point
      if (!firstLineSegment.isLineFound() ||
          (abs(LineSegment::rowRangeMidPoint-newLineSegment.getCenter())
           < abs(LineSegment::rowRangeMidPoint-firstLineSegment.getCenter()))) {
        firstLineSegment = newLineSegment;
      }

    } else {

      if (newLineSegment.touchesSegment(firstLineSegmentPreviousRow)) {
        if (!firstLineSegment.isLineFound() ||
            // if second line is already detected then choose the one closest to the middle if another split occurs
            (secondLineSegmentPreviousRow.isLineFound() && (abs(LineSegment::rowRangeMidPoint-newLineSegment.getCenter())
             < abs(LineSegment::rowRangeMidPoint-firstLineSegment.getCenter())))
            ) {
          firstLineSegment = newLineSegment;
        } else if (!secondLineSegmentPreviousRow.isLineFound() && !secondLineSegment.isLineFound()) {
          secondLineSegment = newLineSegment;
        }
      }
      if (secondLineSegmentPreviousRow.isLineFound()
          && !secondLineSegment.isLineFound()
          && newLineSegment.touchesSegment(secondLineSegmentPreviousRow)) {
        secondLineSegment = newLineSegment;
      }

    }
  }
}




bool RowBitmapLineSegmentFinder::isIgnoreSegment(int8_t segmentStart, int8_t segmentEnd) {
  // if line is already found no need to ignore. next segment must be attached to previous one
  if (firstLineSegmentPreviousRow.isLineFound()) {
    return false;
  }

  // ignore segments that start and end in the same corner
  if (segmentStart < 15 && segmentEnd > 15) {
    return false;
  } else if (currentRowIndex < ignore2pixelsOnCornersRows) {
    return (segmentStart <= 2 || segmentStart >= LineSegment::rowRange - 2)
        && (segmentEnd <= 2 || segmentEnd >= LineSegment::rowRange - 2);
  } else if (currentRowIndex < ignore1pixelOnCornersRows) {
    return (segmentStart == 0 || segmentStart == LineSegment::rowRange)
           && (segmentEnd == 0 || segmentEnd == LineSegment::rowRange);
  } else {
    return false;
  }
}



bool RowBitmapLineSegmentFinder::isLineFound() {
  return firstLineSegment.isLineFound() || secondLineSegment.isLineFound();
}


bool RowBitmapLineSegmentFinder::isSingleLineFound() {
  return firstLineSegment.isLineFound() != secondLineSegment.isLineFound();
}


LineSegment & RowBitmapLineSegmentFinder::getSingleLine() {
  return firstLineSegment.isLineFound() ? firstLineSegment : secondLineSegment;
}


bool RowBitmapLineSegmentFinder::isLineSplit() {
  return firstLineSegment.isLineFound() && secondLineSegment.isLineFound();
}


LineSegment & RowBitmapLineSegmentFinder::getFirstLine() {
  return firstLineSegment;
}


LineSegment & RowBitmapLineSegmentFinder::getSecondLine() {
  return secondLineSegment;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_ROWLINEPOSITION_H



