//
// Created by indrek on 20.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H


#include "RowLinePosition.h"
#include "Arduino.h"



struct LineStep {

    static const int16_t slopeInvalid = 0x7FFF;

    int8_t direction;
    int8_t rowIndexStart;
    int8_t rowIndexEnd;
    int8_t linePos;
    int8_t lineSegmentStart;
    int8_t lineSegmentEnd;
    int16_t bottomSlope;
    int16_t topSlope;

    inline void initStep(
        int8_t direction,
        int8_t rowIndex,
        RowLinePosition & position
    ) __attribute__((always_inline));
    inline bool isPartOfStep(RowLinePosition & position) __attribute__((always_inline));
    inline void calculateBottomSlope(LineStep & fromStep) __attribute__((always_inline));
    inline void calculateTopSlope(LineStep & fromStep) __attribute__((always_inline));
    inline int16_t calculateSlope(int8_t fromRowIndex, int8_t fromPos, int8_t toRowIndex) __attribute__((always_inline));
    inline bool isBottomSlopeValid() __attribute__((always_inline));
    inline bool isTopSlopeValid() __attribute__((always_inline));

    inline void update(uint8_t rowIndex, RowLinePosition & position) __attribute__((always_inline));

    inline bool isStepConnected(LineStep & previousStep) __attribute__((always_inline));
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
  this->bottomSlope = slopeInvalid;
  this->topSlope = slopeInvalid;
}


bool LineStep::isPartOfStep(RowLinePosition & position) {
  return (lineSegmentStart == position.getLineSegmentStart()
            || lineSegmentEnd == position.getLineSegmentEnd()
            || position.getLinePosition() == linePos)
      && (linePos >= position.getLineSegmentStart() && linePos <= position.getLineSegmentEnd());
}


void LineStep::calculateBottomSlope(LineStep & fromStep) {
  bottomSlope = calculateSlope(fromStep.rowIndexStart, fromStep.linePos, rowIndexStart);
}

void LineStep::calculateTopSlope(LineStep & fromStep) {
  topSlope = calculateSlope(fromStep.rowIndexEnd, fromStep.linePos, rowIndexEnd);
}

int16_t LineStep::calculateSlope(int8_t fromRowIndex, int8_t fromPos, int8_t toRowIndex) {
  int16_t x = ((int16_t)(linePos - fromPos)) << 10;
  return x / (toRowIndex - fromRowIndex);
}


bool LineStep::isBottomSlopeValid() {
  return bottomSlope != slopeInvalid;
}


bool LineStep::isTopSlopeValid() {
  return topSlope != slopeInvalid;
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





#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESTEP_H
