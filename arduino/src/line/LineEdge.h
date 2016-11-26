//
// Created by indrek on 25.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H


#include <Arduino.h>
#include "RowLinePosition.h"



struct LineEdge{

    int8_t firstStepCount;
    int8_t firstStepPosition;

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
    inline void update(int8_t edgePos) __attribute__((always_inline));
    inline void calculateLinePositionToEdge(int8_t linePos) __attribute__((always_inline));
    inline void calculateLinePositionToEdgeDecreaseOnly(int8_t linePos) __attribute__((always_inline));
    inline int8_t getLinePositionFromEdge() __attribute__((always_inline));
    inline bool isContinues() __attribute__((always_inline));

private:
    inline int8_t calculateAllowedDifference(int8_t stepCount) __attribute__((always_inline));
    inline void validateCurrentStepCount() __attribute__((always_inline));
    inline void validateCurrentStepCountBlowLimit() __attribute__((always_inline));
};



void LineEdge::init(int8_t edgePos, int8_t linePos) {
  firstStepCount = -1;
  firstStepPosition = -1;

  currentStepCount = RowLinePosition::isOnEdge(edgePos) ? -1 : 1;
  currentStepPosition = edgePos;
  calculateLinePositionToEdge(linePos);

  validStepCount = -1;
  validStepDirection = 0;
  allowedStepDifference = -1;

  directionReversed = false;
  positionJump = false;
  stepLengthInvalid = false;
}


void LineEdge::update(int8_t edgePos) {
  if (currentStepPosition == edgePos) {
    if (currentStepCount >= 0) {
      currentStepCount++;
      validateCurrentStepCountBlowLimit();
    }
  } else {
    if (abs(currentStepPosition - edgePos) > 2) {
      positionJump = true;
    }

    if (currentStepCount >= 0) {

      int8_t direction = (edgePos > currentStepPosition) ? 1 : -1;

      if (firstStepCount < 0) {
        firstStepCount = currentStepCount;
        firstStepPosition = currentStepPosition;
        validStepDirection = direction;
      } else {

        if (validStepDirection != direction) {
          directionReversed = true;
        }

        if (validStepCount < 0) {
          validStepCount = !RowLinePosition::isOnEdge(firstStepPosition) && firstStepCount > currentStepCount ?
                           firstStepCount : currentStepCount;
          allowedStepDifference = calculateAllowedDifference(validStepCount);
        }

        validateCurrentStepCount();
      }
    }

    currentStepCount = 1;
    currentStepPosition = edgePos;
  }
}


int8_t LineEdge::calculateAllowedDifference(int8_t stepCount) {
  int8_t allowedDifference = stepCount >> 2;
  if (allowedDifference < 2) allowedDifference = 2;
  return allowedDifference;
}



void LineEdge::validateCurrentStepCount() {
  if (validStepCount >= 0) {
    if ((currentStepCount > validStepCount + allowedStepDifference)
        || (currentStepCount < validStepCount - allowedStepDifference)) {
      stepLengthInvalid = true;
    }
  }
}


void LineEdge::validateCurrentStepCountBlowLimit() {
  if (validStepCount >= 0) {
    if ((currentStepCount > validStepCount + allowedStepDifference)) {
      stepLengthInvalid = true;
    }
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
