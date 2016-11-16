//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "RowLinePosition.h"
#include <Arduino.h>




template <int8_t totalRowCount>
class Line {

    static const int16_t turnCoefficient = 1025;

/*
    static const uint8_t lineStepCount = 3;
    uint8_t found;
    int8_t lineSteps[lineStepCount];
*/

    int8_t previousLinePos;
    int16_t previousLineSlantCoefficient;
    int16_t minLineSlantCoefficient;
    int16_t maxLineSlantCoefficient;
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
    int16_t processNewLinePosition(uint8_t rowIndex, int8_t linePos);
    void setLineFirstRow(uint8_t rowIndex, int8_t linePos);
    void setLineLastRow(uint8_t rowIndex, int8_t linePos);
    bool isTurnOnRow(uint8_t rowIndex, int16_t lineCoefficient);


};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  previousLinePos = 0;
  lineFirstRowIndex = -1;
  lineFirstRowPos = 0;
  lineLastRowIndex = -1;
  lineLastRowPos = 0;
  minLineSlantCoefficient = 0x7FFF;
  maxLineSlantCoefficient = -0x7FFF;
  lineFound = false;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lineFound) {

    RowLinePosition position(bitmapHigh, bitmapLow);
    int8_t linePos = position.getLinePosition(previousLinePos);
    uint16_t lineCoefficient = processNewLinePosition(rowIndex, linePos);

    if (RowLinePosition::isLineNotFound(linePos) || isTurnOnRow(rowIndex, lineCoefficient)) {
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
    previousLineSlantCoefficient = lineCoefficient;
    return linePos;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
int16_t Line<totalRowCount>::processNewLinePosition(uint8_t rowIndex, int8_t linePos) {
  if (RowLinePosition::isInRange(linePos)) {
    if (lineFirstRowIndex >= 0) {

      int16_t lineCoefficient = (((int16_t)(lineFirstRowPos - linePos)) << 10) / ((int16_t)rowIndex - (int16_t)lineFirstRowIndex);

      if (minLineSlantCoefficient > lineCoefficient) minLineSlantCoefficient = lineCoefficient;
      if (maxLineSlantCoefficient < lineCoefficient) maxLineSlantCoefficient = lineCoefficient;
      return lineCoefficient;
    } else {
      lineFirstRowIndex = rowIndex;
      lineFirstRowPos = linePos;
      return 0;
    }
  }
  return 0;
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
bool Line<totalRowCount>::isTurnOnRow(uint8_t rowIndex, int16_t lineCoefficient) {
  if (lineFirstRowIndex < 0 || (rowIndex - lineFirstRowIndex < 2)) {
    return false;
  } else {
    return (abs(lineCoefficient - minLineSlantCoefficient) > turnCoefficient)
           || (abs(lineCoefficient - maxLineSlantCoefficient) > turnCoefficient);
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
