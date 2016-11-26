//
// Created by indrek on 25.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H


#include <Arduino.h>



struct LineEdge{

    int8_t firstStepCount;

    int8_t currentStepCount;
    int8_t currentStepPosition;
    int8_t currentLinePositionToEdge;

    int8_t validStepCount;
    int8_t validStepDirection;
    int8_t allowedStepDifference;

    bool directionReversed;
    bool positionJump;
    bool stepLengthInvalid;

    inline void init(int8_t edgePos, int8_t linePos) __attribute__((always_inline));
    inline void update(int8_t position) __attribute__((always_inline));
    inline void calculateLinePositionToEdge(int8_t linePos) __attribute__((always_inline));
    inline void calculateLinePositionToEdgeDecreaseOnly(int8_t linePos) __attribute__((always_inline));
    inline int8_t getLinePositionFromEdge() __attribute__((always_inline));
    inline bool isContinues() __attribute__((always_inline));

};



void LineEdge::init(int8_t edgePos, int8_t linePos) {
  firstStepCount = -1;

  currentStepCount = 1;
  currentStepPosition = edgePos;
  calculateLinePositionToEdge(linePos);

  validStepCount = -1;
  validStepDirection = 0;
  allowedStepDifference = -1;
}


void LineEdge::update(int8_t edgePos) {
  if (currentStepPosition == edgePos) {
    currentStepCount++;
  } else {

    if (abs(currentStepPosition - edgePos) > 2) {
      positionJump = true;
    }

    int8_t direction = (edgePos > currentStepPosition) ? 1 : -1;

    if (firstStepCount < 0) {
      firstStepCount = currentStepCount;
      validStepDirection = direction;
    } else {

      if (validStepDirection != direction) {
        directionReversed = true;
      }

      if (validStepCount < 0) {
        validStepCount = currentStepCount;
        allowedStepDifference = validStepCount >> 2;
        if (allowedStepDifference < 2) allowedStepDifference = 2;
      } else {
        if ((currentStepCount > validStepCount + allowedStepDifference)
            || (currentStepCount < validStepCount - allowedStepDifference)) {
          stepLengthInvalid = true;
        }
      }
    }

    currentStepCount = 1;
    currentStepPosition = edgePos;
  }
}



void LineEdge::calculateLinePositionToEdge(int8_t linePos) {
  currentLinePositionToEdge = currentStepPosition - linePos;
}

void LineEdge::calculateLinePositionToEdgeDecreaseOnly(int8_t linePos) {
  int8_t newDiff = currentStepPosition - linePos;
  if (abs(newDiff) < abs(currentLinePositionToEdge)) currentLinePositionToEdge = newDiff;
}


int8_t LineEdge::getLinePositionFromEdge() {
  return currentStepPosition - currentLinePositionToEdge;
}


bool LineEdge::isContinues() {
  return !directionReversed && !positionJump && !stepLengthInvalid;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H
