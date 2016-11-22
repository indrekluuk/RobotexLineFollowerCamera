//
// Created by indrek on 20.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H


#include "RowLinePosition.h"
#include "Arduino.h"



struct LineStep {
    int8_t direction;
    int8_t rowIndexStart;
    int8_t rowIndexEnd;
    int8_t linePos;
    int8_t lineSegmentStart;
    int8_t lineSegmentEnd;

    inline void initStep(
        int8_t direction,
        int8_t rowIndex,
        RowLinePosition & position
    ) __attribute__((always_inline));


    inline bool isPartOfStep(RowLinePosition & position) __attribute__((always_inline));

    inline void update(uint8_t rowIndex, RowLinePosition & position) __attribute__((always_inline));

    inline bool isStepConnected(LineStep & previousStep) __attribute__((always_inline));
    inline bool isSameSlant(LineStep & previousStep) __attribute__((always_inline));

};



void LineStep::initStep(
    int8_t direction,
    int8_t rowIndex,
    RowLinePosition & position
) {
  this->direction = direction;
  this->rowIndexStart = rowIndex;
  this->rowIndexEnd = rowIndex;
  this->linePos = position.getLinePosition();
  this->lineSegmentStart = position.getLineSegmentStart();
  this->lineSegmentEnd = position.getLineSegmentEnd();
}


bool LineStep::isPartOfStep(RowLinePosition & position) {
  return (lineSegmentStart == position.getLineSegmentStart() || lineSegmentEnd == position.getLineSegmentEnd())
      && (linePos >= position.getLineSegmentStart() && linePos <= position.getLineSegmentEnd());
}



void LineStep::update(uint8_t rowIndex, RowLinePosition & position) {
  rowIndexEnd++;
}



bool LineStep::isStepConnected(LineStep & previousStep) {
  if (previousStep.direction != 0 && direction != previousStep.direction) {
    return false;
  }

  bool areSegmentsTouching = ((lineSegmentEnd - previousStep.lineSegmentStart >= -2)
                              && (previousStep.lineSegmentEnd - lineSegmentStart >= -2));
  return areSegmentsTouching;
  /*
  int8_t prevMinSegmentStart = previousStep.linePos - previousStep.minToEdge;
  int8_t prevMinSegmentEnd = previousStep.linePos + previousStep.minToEdge;
  return (linePos >= prevMinSegmentStart - 2 && linePos <= prevMinSegmentEnd + 2);
   */
}


bool LineStep::isSameSlant(LineStep & previousStep) {
  /*
  int8_t diff = rowCount >> 1;
  int8_t min = rowCount - diff;
  int8_t max = rowCount + diff;
  return previousStep.rowCount >= min && previousStep.rowCount <= max;
   */
  return true;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
