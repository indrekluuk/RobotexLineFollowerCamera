//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "LineStep.h"
#include "RowLinePosition.h"
#include <Arduino.h>



template <int8_t totalRowCount>
class Line {

    static const uint8_t stepBufferSize = 4;
    LineStep lastSteps [stepBufferSize];
    uint8_t stepBufferIndex;
    uint8_t stepCount;

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
    void processNewLinePosition(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd);
    void setLineFirstRow(uint8_t rowIndex, int8_t linePos);
    void setLineLastRow(LineStep &step);
    LineStep * getLastStepBeforeTurn();
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  previousLinePos = RowLinePosition::rowRangeMidPoint;
  previousLineSegmentStart = -1;
  previousLineSegmentEnd = -1;
  lineFirstRowIndex = -1;
  lineFirstRowPos = 0;
  lineLastRowIndex = -1;
  lineLastRowPos = 0;
  lineFound = false;

  stepBufferIndex = 0;
  stepCount = 0;
  lastSteps[stepBufferIndex].initStep(
      0,
      0,
      -1,
      RowLinePosition::lineNotFound,
      RowLinePosition::lineNotFound,
      RowLinePosition::lineNotFound);
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lineFound) {

    RowLinePosition position(bitmapHigh, bitmapLow, previousLinePos);
    int8_t linePos = position.getLinePosition();
    int8_t lineSegmentStart = position.getLineSegmentStart();
    int8_t lineSegmentEnd = position.getLineSegmentEnd();
    processNewLinePosition(rowIndex, linePos, lineSegmentStart, lineSegmentEnd);

    int8_t currentDetectedLinePosition = lastSteps[stepBufferIndex].rowPos;
    if (RowLinePosition::isLineNotFound(linePos)) {
      if (lineFirstRowIndex >= 0) {
        setLineLastRow(lastSteps[stepBufferIndex]);
        currentDetectedLinePosition = RowLinePosition::lineNotFound;
      }
    } else {
      LineStep *lastStep = getLastStepBeforeTurn();
      if (lastStep) {
        if (lineFirstRowIndex >= 0) {
          setLineLastRow(*lastStep);
          currentDetectedLinePosition = RowLinePosition::lineNotFound;
        }
      } else {
        if (lineFirstRowIndex < 0) {
          setLineFirstRow(rowIndex, linePos);
        }
        if (rowIndex == totalRowCount - 1) {
          setLineLastRow(lastSteps[stepBufferIndex]);
        }
      }
    }
    previousLinePos = linePos;
    previousLineSegmentStart = lineSegmentStart;
    previousLineSegmentEnd = lineSegmentEnd;
    return currentDetectedLinePosition;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
void Line<totalRowCount>::processNewLinePosition(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd) {
  if (RowLinePosition::isInRange(linePos)) {
    if (lineFirstRowIndex >= 0) {

      int8_t segmentPos = lastSteps[stepBufferIndex].rowPos;
      int8_t stepSegmentStart = lastSteps[stepBufferIndex].rowSegmentStart;
      int8_t stepSegmentEnd = lastSteps[stepBufferIndex].rowSegmentEnd;
      if ((stepSegmentStart == lineSegmentStart || stepSegmentEnd == lineSegmentEnd)
          && (segmentPos >= lineSegmentStart && segmentPos <= lineSegmentEnd)) {
        lastSteps[stepBufferIndex].update(lineSegmentStart, lineSegmentEnd);
      } else {
        stepCount++;
        stepBufferIndex++;
        stepBufferIndex &= (uint8_t)(stepBufferSize-1);
        lastSteps[stepBufferIndex].initStep(
            ((linePos - previousLinePos) < 0) ? (int8_t)-1 : (int8_t)1,
            rowIndex,
            1,
            linePos,
            lineSegmentStart,
            lineSegmentEnd);
      }

    } else {
      lineFirstRowIndex = rowIndex;
      lineFirstRowPos = linePos;
      stepCount = 1;
      lastSteps[stepBufferIndex].initStep(
          0,
          rowIndex,
          1,
          linePos,
          lineSegmentStart,
          lineSegmentEnd);
    }
  }
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineFirstRow(uint8_t rowIndex, int8_t linePos) {
  lineFirstRowIndex = rowIndex;
  lineFirstRowPos = linePos;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineLastRow(LineStep &step) {
  lineFound = true;
  lineLastRowIndex = step.rowIndex;
  lineLastRowPos = step.rowPos;
}


template <int8_t totalRowCount>
LineStep * Line<totalRowCount>::getLastStepBeforeTurn() {
  if (stepCount <= 1) {
    return nullptr;
  } else {
    LineStep &step0 = lastSteps[stepBufferIndex];
    LineStep &step1 = lastSteps[(stepBufferIndex - 1) & 0x03];

    if (!step0.isStepConnected(step1)) {
      return &step1;
    }

    if (stepCount > 2) {
      LineStep &step2 = lastSteps[(stepBufferIndex - 2) & 0x03];
      return (!step1.isSameSlant(step2)) ? &step2 : nullptr;
    } else {
      return nullptr;
    }
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
