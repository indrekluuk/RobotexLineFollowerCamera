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

    struct StepBuffer {
        LineStep firstStep;
        LineStep secondStep;
        LineStep step2;
        LineStep step3;
    } steps;
    LineStep * previousStep;
    LineStep * currentStep;
    LineStep * lastStep;
    int8_t previousLinePos;



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
    void updateStep(uint8_t rowIndex, RowLinePosition & position);
    LineStep * getNextStep();
    bool isTurn();
    void setLastStep(LineStep * step);
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
      updateStep(rowIndex, position);
      if (isTurn()) {
        currentDetectedLinePosition = RowLinePosition::lineNotFound;
        setLastStep(previousStep);
      } else {
        currentDetectedLinePosition = currentStep->linePos;
        if (rowIndex == totalRowCount - 1) {
          setLastStep(currentStep);
        }
      }
    }

    previousLinePos = position.getLinePosition();
    return currentDetectedLinePosition;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
void Line<totalRowCount>::updateStep(uint8_t rowIndex, RowLinePosition & position) {
  if (currentStep) {
    if (currentStep->isPartOfStep(position)) {
      currentStep->update(rowIndex, position);
    } else {
      previousStep = currentStep;
      currentStep = getNextStep();
      currentStep->initStep(
          ((position.getLinePosition() - previousStep->linePos) < 0) ? (int8_t)-1 : (int8_t)1,
          rowIndex,
          position);
    }
  } else {
    steps.firstStep.initStep(
        0,
        rowIndex,
        position);
    currentStep = &steps.firstStep;
  }
}


template <int8_t totalRowCount>
LineStep * Line<totalRowCount>::getNextStep() {
  if (currentStep == &steps.step3) {
    return &steps.step2;
  } else {
    return currentStep + 1;
  }
}



template <int8_t totalRowCount>
bool Line<totalRowCount>::isTurn() {
  if (currentStep == &steps.firstStep) {
    return false;
  } else {
    if (!currentStep->isStepConnected(*previousStep)) {
      return true;
    }
    if (currentStep != &steps.secondStep) {
      return false; // todo check angle
    } else {
      return false;
    }
  }
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
