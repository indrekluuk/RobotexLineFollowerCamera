//
// Created by indrek on 25.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H


#include <Arduino.h>
#include "RowBitmapLineSegmentFinder.h"



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
    int8_t stepFailedAtRow;
    int8_t filedRowDirection;

    inline void reset() __attribute__((always_inline));
    inline bool isInitialized() __attribute__((always_inline));
    inline void init(int8_t edgePos, int8_t linePos) __attribute__((always_inline));
    inline void resetFirstStepTo(int8_t edgePos, int8_t linePos) __attribute__((always_inline));
    inline void update(int8_t rowIndex, int8_t edgePos) __attribute__((always_inline));
    inline void calculateLinePositionToEdge(int8_t linePos) __attribute__((always_inline));
    inline void calculateLinePositionToEdgeDecreaseOnly(int8_t linePos) __attribute__((always_inline));
    inline int8_t getLinePositionFromEdge() __attribute__((always_inline));

    inline void setFailedWithReversedDirection(int8_t rowIndex) __attribute__((always_inline));
    inline void setFailedWithPositionJump(int8_t rowIndex) __attribute__((always_inline));
    inline void setFailedWithInvalidStepLength(int8_t rowIndex) __attribute__((always_inline));
    inline void setStepFailed(int8_t rowIndex, bool isDirectionRevers, bool isPositionJump, bool isStepLengthInvalid) __attribute__((always_inline));
    inline bool isOppositeDirection(LineEdge &otherEdge) __attribute__((always_inline));
    inline bool isContinues() __attribute__((always_inline));
    inline int8_t getFailedAtRow() __attribute__((always_inline));
    inline bool isPositionJump() __attribute__((always_inline));
    inline int8_t getFailedRowDirection() __attribute__((always_inline));

private:
    inline int8_t calculateAllowedDifference(int8_t stepCount) __attribute__((always_inline));
    inline bool isCurrentStepCountValid() __attribute__((always_inline));
    inline bool isCurrentStepCountBlowLimit() __attribute__((always_inline));
};




void LineEdge::reset() {
  init(-1, -1);
}


bool LineEdge::isInitialized() {
  return currentStepPosition >= 0;
}


void LineEdge::init(int8_t edgePos, int8_t linePos) {
  firstStepCount = -1;
  firstStepPosition = -1;

  currentStepCount = LineSegment::isOnEdge(edgePos) ? -1 : 1;
  currentStepPosition = edgePos;
  calculateLinePositionToEdge(linePos);

  validStepCount = -1;
  validStepDirection = 0;
  allowedStepDifference = -1;

  directionReversed = false;
  positionJump = false;
  stepLengthInvalid = false;
  stepFailedAtRow = -1;
}




void LineEdge::resetFirstStepTo(int8_t edgePos, int8_t linePos) {
  if (currentStepPosition != edgePos) {
    init(edgePos, linePos);
  }
}



void LineEdge::update(int8_t rowIndex, int8_t edgePos) {
  if (currentStepPosition == edgePos) {
    if (currentStepCount >= 0) {
      currentStepCount++;
      if (!isCurrentStepCountBlowLimit()) {
        setFailedWithInvalidStepLength(rowIndex);
      }
    }
  } else {
    if (abs(currentStepPosition - edgePos) > 2) {
      setFailedWithPositionJump(rowIndex);
    }

    if (currentStepCount >= 0) {

      int8_t direction = (edgePos > currentStepPosition) ? 1 : -1;

      if (firstStepCount < 0) {
        firstStepCount = currentStepCount;
        firstStepPosition = currentStepPosition;
        validStepDirection = direction;
      } else {

        if (validStepDirection != direction) {
          setFailedWithReversedDirection(rowIndex);
        }

        if (validStepCount < 0) {
          validStepCount = !LineSegment::isOnEdge(firstStepPosition) && firstStepCount > currentStepCount ?
                           firstStepCount : currentStepCount;
          allowedStepDifference = calculateAllowedDifference(validStepCount);
        }

        if (!isCurrentStepCountValid()) {
          setFailedWithInvalidStepLength(rowIndex);
        }
      }
    }

    currentStepCount = 1;
    currentStepPosition = edgePos;
  }
}


int8_t LineEdge::calculateAllowedDifference(int8_t stepCount) {
  int8_t allowedDifference = stepCount >> 2;
  if (allowedDifference < 5) allowedDifference = 5;
  return allowedDifference;
}



bool LineEdge::isCurrentStepCountValid() {
  if (validStepCount >= 0) {
    if ((currentStepCount > validStepCount + allowedStepDifference)
        || (currentStepCount < validStepCount - allowedStepDifference)) {
      return false;
    }
  }
  return true;
}


bool LineEdge::isCurrentStepCountBlowLimit() {
  if (validStepCount >= 0) {
    if ((currentStepCount > validStepCount + allowedStepDifference)) {
      return false;
    }
  }
  return true;
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


void LineEdge::setFailedWithReversedDirection(int8_t rowIndex) {
  setStepFailed(rowIndex, true, false, false);
}

void LineEdge::setFailedWithPositionJump(int8_t rowIndex) {
  setStepFailed(rowIndex, false, true, false);
}

void LineEdge::setFailedWithInvalidStepLength(int8_t rowIndex) {
  setStepFailed(rowIndex, false, false, true);
}

void LineEdge::setStepFailed(int8_t rowIndex, bool isDirectionRevers, bool isPositionJump, bool isStepLengthInvalid) {
  if (stepFailedAtRow <0) {
    stepFailedAtRow = rowIndex;
    directionReversed = isDirectionRevers;
    positionJump = isPositionJump;
    stepLengthInvalid = isStepLengthInvalid;
    filedRowDirection = isDirectionRevers ? -validStepDirection : validStepDirection;
  }
}



bool LineEdge::isOppositeDirection(LineEdge &otherEdge) {
  return validStepDirection != 0
         && otherEdge.validStepDirection != 0
         && validStepDirection != otherEdge.validStepDirection;
}




bool LineEdge::isContinues() {
  return stepFailedAtRow < 0;
}


int8_t LineEdge::getFailedAtRow() {
  return stepFailedAtRow;
}


bool LineEdge::isPositionJump() {
  return positionJump;
}


int8_t LineEdge::getFailedRowDirection() {
  return filedRowDirection;
}


#endif //ROBOTEXLINEFOLLOWERCAMERA_LINEEDGE_H
