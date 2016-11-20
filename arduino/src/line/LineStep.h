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
    int8_t minToEdge;

    inline void initStep(
        int8_t direction,
        int8_t rowIndex,
        int8_t rowCount,
        int8_t rowPos,
        int8_t rowSegmentStart,
        int8_t rowSegmentEnd
    ) __attribute__((always_inline));

    inline void update(int8_t rowSegmentStart, int8_t rowSegmentEnd) __attribute__((always_inline));

    inline bool isStepConnected(LineStep & previousStep __attribute__((always_inline));
    inline bool isSameSlant(LineStep & previousStep) __attribute__((always_inline));

private:
    inline int8_t getMinToEdge(int8_t start, int8_t end) __attribute__((always_inline));

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
  this->minToEdge = getMinToEdge(rowSegmentStart, rowSegmentEnd);
}


void LineStep::update(int8_t segmentStart, int8_t segmentEnd) {
  rowCount++;
  rowIndex++;
  int8_t toEdge = getMinToEdge(segmentStart, segmentEnd);
  if (toEdge < minToEdge) minToEdge = toEdge;
}


int8_t LineStep::getMinToEdge(int8_t segmentStart, int8_t segmentEnd) {
  int8_t toStart = rowPos - segmentStart;
  int8_t toEnd = segmentEnd - rowPos;
  return toStart < toEnd ? toStart : toEnd;
}


bool LineStep::isStepConnected(LineStep & previousStep) {
  if (previousStep.direction != 0 && direction != previousStep.direction) {
    return false;
  }
  int8_t prevMinSegmentStart = previousStep.rowPos - previousStep.minToEdge;
  int8_t prevMinSegmentEnd = previousStep.rowPos + previousStep.minToEdge;
  return (rowPos >= prevMinSegmentStart - 2 && rowPos <= prevMinSegmentEnd + 2);
}


bool LineStep::isSameSlant(LineStep & previousStep) {
  int8_t diff = rowCount >> 1;
  int8_t min = rowCount - diff;
  int8_t max = rowCount + diff;
  return previousStep.rowCount >= min && previousStep.rowCount <= max;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
