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
    int8_t rowPos;
    int8_t rowSegmentStart;
    int8_t rowSegmentEnd;

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
  this->rowPos = position.getLinePosition();
  this->rowSegmentStart = position.getLineSegmentStart();
  this->rowSegmentEnd = position.getLineSegmentEnd();
}


bool LineStep::isPartOfStep(RowLinePosition & position) {
  return (rowSegmentStart == position.getLineSegmentStart() || rowSegmentEnd == position.getLineSegmentEnd())
      && (rowPos >= position.getLineSegmentStart() && rowPos <= position.getLineSegmentEnd());
}



void LineStep::update(uint8_t rowIndex, RowLinePosition & position) {
  rowIndexEnd++;
}



bool LineStep::isStepConnected(LineStep & previousStep) {
  if (previousStep.direction != 0 && direction != previousStep.direction) {
    return false;
  }

  bool areSegmentsTouching = ((rowSegmentEnd - previousStep.rowSegmentStart >= -2)
                              && (previousStep.rowSegmentEnd - rowSegmentStart >= -2));
  return areSegmentsTouching;
  /*
  int8_t prevMinSegmentStart = previousStep.rowPos - previousStep.minToEdge;
  int8_t prevMinSegmentEnd = previousStep.rowPos + previousStep.minToEdge;
  return (rowPos >= prevMinSegmentStart - 2 && rowPos <= prevMinSegmentEnd + 2);
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
