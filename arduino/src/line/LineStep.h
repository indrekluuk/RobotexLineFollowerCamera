//
// Created by indrek on 20.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H


#include "Arduino.h"


struct LineStep {
    int8_t direction;
    int8_t rowCount;
    int8_t rowIndex;
    int8_t rowPos;
    int8_t rowSegmentStart;
    int8_t rowSegmentEnd;

    inline void initStep(
        int8_t direction,
        int8_t rowIndex,
        int8_t rowCount,
        int8_t rowPos,
        int8_t rowSegmentStart,
        int8_t rowSegmentEnd
    ) __attribute__((always_inline));

    inline bool isStepConnected(LineStep & previousStep) __attribute__((always_inline));
    inline int8_t getMinPositionToEdge() __attribute__((always_inline));

    inline bool isSameSlant(LineStep & previousStep) __attribute__((always_inline));

};



void LineStep::initStep(
    int8_t direction,
    int8_t rowIndex,
    int8_t rowCount,
    int8_t rowPos,
    int8_t rowSegmentStart,
    int8_t rowSegmentEnd
) {
  this->direction = direction;
  this->rowCount = rowCount;
  this->rowIndex = rowIndex;
  this->rowPos = rowPos;
  this->rowSegmentStart = rowSegmentStart;
  this->rowSegmentEnd = rowSegmentEnd;
}


bool LineStep::isStepConnected(LineStep & previousStep) {
  if (previousStep.direction != 0 && direction != previousStep.direction) {
    return false;
  }
  int8_t prevMinToEdge = previousStep.getMinPositionToEdge();
  int8_t prevMinSegmentStart = previousStep.rowPos - prevMinToEdge;
  int8_t prevMinSegmentEnd = previousStep.rowPos + prevMinToEdge;
  return (rowPos >= prevMinSegmentStart - 2 && rowPos <= prevMinSegmentEnd + 2);
}


int8_t LineStep::getMinPositionToEdge() {
  int8_t toStart = rowPos - rowSegmentStart;
  int8_t toEnd = rowSegmentEnd - rowPos;
  return toStart < toEnd ? toStart : toEnd;
}


bool LineStep::isSameSlant(LineStep & previousStep) {
  int8_t diff = rowCount >> 1;
  int8_t min = rowCount - diff;
  int8_t max = rowCount + diff;
  return previousStep.rowCount >= min && previousStep.rowCount <= max;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
