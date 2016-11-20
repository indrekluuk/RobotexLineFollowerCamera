//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "RowLinePosition.h"
#include <Arduino.h>




template <int8_t totalRowCount>
class Line {

    static const uint8_t stepBufferSize = 4;
    struct Step {
        int8_t direction;
        int8_t rowCount;
        int8_t rowIndex;
        int8_t rowPos;
    } lastSteps [stepBufferSize];
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
    inline void resetStep(Step & step, int8_t direction) __attribute__((always_inline));
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
    int8_t getTurnPosition(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd);


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

  stepBufferIndex = 0;
  stepCount = 0;
  resetStep(lastSteps[0], 0);
  resetStep(lastSteps[1], 0);
  resetStep(lastSteps[2], 0);
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetStep(Step & step, int8_t direction) {
  step.direction = direction;
  step.rowCount = 0;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lineFound) {

    RowLinePosition position(bitmapHigh, bitmapLow, previousLinePos);
    int8_t linePos = position.getLinePosition();
    int8_t lineSegmentStart = position.getLineSegmentStart();
    int8_t lineSegmentEnd = position.getLineSegmentEnd();
    processNewLinePosition(rowIndex, linePos);

    if (RowLinePosition::isLineNotFound(linePos)) {
      if (lineFirstRowIndex >= 0) {
        setLineLastRow(rowIndex, previousLinePos);
        linePos = RowLinePosition::lineNotFound;
      }
    } else {
      int8_t turnPos = getTurnPosition(rowIndex, linePos, lineSegmentStart, lineSegmentEnd);
      if (turnPos >= 0) {
        if (lineFirstRowIndex >= 0) {
          setLineLastRow(rowIndex - 1, turnPos);
          linePos = RowLinePosition::lineNotFound;
        }
      } else {
        if (lineFirstRowIndex < 0) {
          setLineFirstRow(rowIndex, linePos);
        }
        if (rowIndex == totalRowCount - 1) {
          setLineLastRow(totalRowCount, linePos);
        }
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

      int8_t currentStepDirection = linePos - previousLinePos;
      if (currentStepDirection == 0) {
        lastSteps[stepBufferIndex].rowCount++;
      } else {
        stepCount++;
        stepBufferIndex++;
        stepBufferIndex &= (uint8_t)(stepBufferSize-1);
        resetStep(lastSteps[stepBufferIndex], currentStepDirection < 0 ? (int8_t)-1 : (int8_t)1);
        lastSteps[stepBufferIndex].rowIndex = rowIndex;
        lastSteps[stepBufferIndex].rowPos = linePos;
      }

    } else {
      lineFirstRowIndex = rowIndex;
      lineFirstRowPos = linePos;
      stepCount = 1;
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
int8_t Line<totalRowCount>::getTurnPosition(uint8_t rowIndex, int8_t linePos, int8_t lineSegmentStart, int8_t lineSegmentEnd) {
  if (lineFirstRowIndex < 0 || (rowIndex - lineFirstRowIndex < 2)) {
    return -1;
  } else {
    bool areSegmentsTouching = ((lineSegmentEnd - previousLineSegmentStart >= -2)
                                && (previousLineSegmentEnd - lineSegmentStart >= -2));
    if (!areSegmentsTouching) {
      return -1;
    }

    if (stepCount > 3) {
      Step &step1 = lastSteps[(stepBufferIndex - 1) & 0x03];
      Step &step2 = lastSteps[(stepBufferIndex - 2) & 0x03];
      if (step1.direction != step2.direction || step1.rowCount != step2.rowCount) {
        return step2.rowPos;
      }
    }
  }
  return -1;
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
