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

    static const int16_t D_SLOPE = 20;

    struct StepBuffer {
        LineStep firstStep;
        LineStep secondStep;
        LineStep step2;
        LineStep step3;
        LineStep stepBufferLast;
    } steps;
    LineStep * previousStep;
    LineStep * currentStep;
    LineStep * lastStep;
    int8_t previousLinePos;

    int16_t slopeMax;
    int16_t slopeMin;


public:
    Line();

    void resetLine();
    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    static int8_t getTotalRowCount();
    bool isLineIdentified();
    int8_t getLineFirstRowIndex();
    int8_t getLineFirstPosition();
    int8_t getLineLastRowIndex();
    int8_t getLineLastPosition();


private:
    bool updateLineStep(uint8_t rowIndex, RowLinePosition & position);
    inline LineStep * getNextStep() __attribute__((always_inline));
    inline void checkSlopeForMinMax(int16_t slope) __attribute__((always_inline));
    inline bool isTurn(LineStep & nextStep) __attribute__((always_inline));
    inline bool isSlopeInRange(int16_t slope) __attribute__((always_inline));
    inline void setLastStep(LineStep * step) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  previousLinePos = RowLinePosition::rowRangeMidPoint;
  previousStep = nullptr;
  currentStep = nullptr;
  lastStep = nullptr;
  slopeMin = 0x7FFF;
  slopeMax = -0x7FFF;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lastStep) {
    RowLinePosition position(bitmapHigh, bitmapLow, previousLinePos);
    int8_t currentDetectedLinePosition = RowLinePosition::lineNotFound;

    if (position.isLineNotFound()) {
      if (currentStep != nullptr) {
        setLastStep(currentStep);
      }
    } else {
      if (updateLineStep(rowIndex, position)) {
        currentDetectedLinePosition = currentStep->linePos;
        if (rowIndex == totalRowCount - 1) {
          setLastStep(currentStep);
        }
      } else {
        currentDetectedLinePosition = RowLinePosition::lineNotFound;
        setLastStep(currentStep);
      }
    }

    previousLinePos = position.getLinePosition();
    return currentDetectedLinePosition;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
bool Line<totalRowCount>::updateLineStep(uint8_t rowIndex, RowLinePosition & position) {

  if (!currentStep) {
    steps.firstStep.initStep(
        0,
        rowIndex,
        position);
    currentStep = &steps.firstStep;
    return true;

  } else {
    if (currentStep->isPartOfStep(position)) {
      currentStep->update(rowIndex, position);
      if (currentStep != &steps.firstStep) {
        currentStep->calculateTopSlope(steps.firstStep);
      }
      return true;

    } else {
      LineStep * nextStep = getNextStep();

      nextStep->initStep(
          ((position.getLinePosition() - currentStep->linePos) < 0) ? (int8_t)-1 : (int8_t)1,
          rowIndex,
          position);

      // Step start position slope can be calculated starting from third step.
      // Second step is the first one with fully visible bottom.
      if (nextStep > &steps.secondStep) {
        nextStep->calculateBottomSlope(steps.secondStep);
        if (currentStep == &steps.secondStep) {
          checkSlopeForMinMax(nextStep->bottomSlope);
        }
      }
      nextStep->calculateTopSlope(steps.firstStep);

      if (nextStep->isStepConnected(*currentStep) && !isTurn(*nextStep)) {
        if (currentStep->isBottomSlopeValid()) {
          checkSlopeForMinMax(currentStep->bottomSlope);
        }
        if (currentStep->isTopSlopeValid()) {
          checkSlopeForMinMax(currentStep->topSlope);
        }
        previousStep = currentStep;
        currentStep = nextStep;
        return true;
      } else {
        return false;
      }
    }
  }
}



template <int8_t totalRowCount>
bool Line<totalRowCount>::isTurn(LineStep & nextStep) {
  if (nextStep.isBottomSlopeValid() && !isSlopeInRange(nextStep.bottomSlope)) {
    return true;
  }
  if (currentStep->isTopSlopeValid() && !isSlopeInRange(currentStep->topSlope)) {
    return true;
  }
  return false;
}

template <int8_t totalRowCount>
bool Line<totalRowCount>::isSlopeInRange(int16_t slope) {
  return (slope < (slopeMax + D_SLOPE))
         && (slope > (slopeMin - D_SLOPE));
}




template <int8_t totalRowCount>
LineStep * Line<totalRowCount>::getNextStep() {
  if (currentStep == &steps.stepBufferLast) {
    return &steps.step2;
  } else {
    return currentStep + 1;
  }
}



template <int8_t totalRowCount>
void Line<totalRowCount>::checkSlopeForMinMax(int16_t slope) {
  if (slope > slopeMax) slopeMax = slope;
  if (slope < slopeMin) slopeMin = slope;
}









template <int8_t totalRowCount>
void Line<totalRowCount>::setLastStep(LineStep * step) {
  lastStep = step;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getTotalRowCount() {
  return totalRowCount;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isLineIdentified() {
  return lastStep != nullptr;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstRowIndex() {
  return steps.firstStep.rowIndexStart;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstPosition() {
  return steps.firstStep.linePos;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastRowIndex() {
  return lastStep->rowIndexEnd;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastPosition() {
  return lastStep->linePos;
}






#endif //ROBOTEXLINEFOLLOWERCAMERA_LINE_H
