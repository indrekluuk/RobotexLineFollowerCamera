//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "RowLinePosition.h"
#include <Arduino.h>




template <int8_t totalRowCount>
class Line {


    static const uint8_t totalSteps = 3;
    uint8_t stepCount;
    int8_t step[totalSteps];

    int8_t previousLinePos;
    int8_t previousLineSegmentStart;
    int8_t previousLineSegmentEnd;
    int8_t lineFirstRowIndex;
    int8_t lineFirstRowPos;
    int8_t lineLastRowIndex;
    int8_t lineLastRowPos;
    bool lineFound;



public:
    Line();

    void resetLine();
    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    static int8_t getTotalRowCount();
    bool isLineFound();
    int8_t getLineFirstRowIndex();
    int8_t getLineFirstRowPosition();
    int8_t getLineLastRowIndex();
    int8_t getLineLastRowPosition();


private:
    void processNewLinePosition(uint8_t rowIndex, int8_t linePos);
    void setLineFirstRow(uint8_t rowIndex, int8_t linePos);
    void setLineLastRow(uint8_t rowIndex, int8_t linePos);
    bool isTurnOnRow(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd);


};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  previousLinePos = 0;
  previousLineSegmentStart = -1;
  previousLineSegmentEnd = -1;
  lineFirstRowIndex = -1;
  lineFirstRowPos = 0;
  lineLastRowIndex = -1;
  lineLastRowPos = 0;
  lineFound = false;
  stepCount = 0;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lineFound) {

    RowLinePosition position(bitmapHigh, bitmapLow, previousLinePos);
    int8_t linePos = position.getLinePosition();
    int8_t lineSegmentStart = position.getLineSegmentStart();
    int8_t lineSegmentEnd = position.getLineSegmentEnd();
    processNewLinePosition(rowIndex, linePos);

    if (RowLinePosition::isLineNotFound(linePos) || isTurnOnRow(rowIndex, linePos, lineSegmentStart, lineSegmentEnd)) {
      if (lineFirstRowIndex >= 0) {
        setLineLastRow(rowIndex, previousLinePos);
      }
    } else {
      if (lineFirstRowIndex < 0) {
        setLineFirstRow(rowIndex, linePos);
      }
      if (rowIndex == totalRowCount - 1) {
        setLineLastRow(totalRowCount, linePos);
      }
    }

    previousLinePos = linePos;
    previousLineSegmentStart = lineSegmentStart;
    previousLineSegmentEnd = lineSegmentEnd;
    return linePos;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
void Line<totalRowCount>::processNewLinePosition(uint8_t rowIndex, int8_t linePos) {
  if (RowLinePosition::isInRange(linePos)) {
    if (lineFirstRowIndex >= 0) {
      /*
      if (linePos != previousLinePos) {
        if (stepCount < totalSteps) {
          step[stepCount] = linePos - previousLinePos;
          stepCount++;
        }
      }
       */
    } else {
      lineFirstRowIndex = rowIndex;
      lineFirstRowPos = linePos;
    }
  }
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineFirstRow(uint8_t rowIndex, int8_t linePos) {
  lineFirstRowIndex = rowIndex;
  lineFirstRowPos = linePos;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineLastRow(uint8_t rowIndex, int8_t linePos) {
  lineFound = true;
  lineLastRowIndex = rowIndex - (uint8_t)1;
  lineLastRowPos = linePos;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isTurnOnRow(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd) {
  if (lineFirstRowIndex < 0 || (rowIndex - lineFirstRowIndex < 2)) {
    return false;
  } else {
    return !((lineSegmentEnd - previousLineSegmentStart >= -2)
             && (previousLineSegmentEnd - lineSegmentStart >= -2));
    /*
    return 0; //(abs(lineCoefficient - minLineSlantCoefficient) > turnCoefficient)
           //|| (abs(lineCoefficient - maxLineSlantCoefficient) > turnCoefficient);
           */
  }
}



template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getTotalRowCount() {
  return totalRowCount;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isLineFound() {
  return lineFound;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstRowIndex() {
  return lineFirstRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstRowPosition() {
  return lineFirstRowPos;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastRowIndex() {
  return lineLastRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastRowPosition() {
  return lineLastRowPos;
}






#endif //ROBOTEXLINEFOLLOWERCAMERA_LINE_H
