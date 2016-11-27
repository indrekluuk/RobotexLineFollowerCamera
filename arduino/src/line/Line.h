//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "LineEdge.h"
#include "RowLinePosition.h"
#include <Arduino.h>



template <int8_t totalRowCount>
class Line {

    LineEdge startEdge;
    LineEdge endEdge;
    int8_t previousDetectedLinePosition;
    int8_t lineSeekPosition;


    int8_t lineBottomRowIndex;
    int8_t lineBottomPosition;
    int8_t lineTopRowIndex;
    int8_t lineTopPosition;

public:

    Line();

    void resetLine();
    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    constexpr static int8_t getTotalRowCount();
    bool isLineIdentified();
    int8_t getLineFirstRowIndex();
    int8_t getLineFirstPosition();
    int8_t getLineLastRowIndex();
    int8_t getLineLastPosition();

    int8_t getStartEdgeStepCount();
    int8_t getEndEdgeStepCount();
    bool isStartEdgeContinues();
    bool isEndEdgeContinues();


private:
    int8_t updateLine(uint8_t rowIndex, RowLinePosition & position);
    inline bool areSegmentsTouching(RowLinePosition & position) __attribute__((always_inline));
    inline void setLineBottom(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTop(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  lineSeekPosition = RowLinePosition::rowRangeMidPoint;
  previousDetectedLinePosition = RowLinePosition::rowRangeMidPoint;
  startEdge.init(-1, -1);
  endEdge.init(-1, -1);
  lineBottomRowIndex = -1;
  lineBottomPosition = -1;
  lineTopRowIndex = -1;
  lineTopPosition = -1;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {

  if (lineTopRowIndex <0) {
    RowLinePosition position(rowIndex, bitmapHigh, bitmapLow, lineSeekPosition);
    int8_t currentDetectedLinePosition = RowLinePosition::lineNotFound;

    if (position.isLineNotFound()) {
      if (lineBottomRowIndex >= 0) {
        setLineTop(rowIndex-1, previousDetectedLinePosition);
      }
    } else {
      currentDetectedLinePosition = updateLine(rowIndex, position);
      if (RowLinePosition::isLineNotFound(currentDetectedLinePosition)) {
        setLineTop(rowIndex - 1, previousDetectedLinePosition);
      } else {
        if (rowIndex == totalRowCount - 1) {
          setLineTop(rowIndex, position.getLinePosition());
        }
      }
    }

    lineSeekPosition = position.getLinePosition();
    previousDetectedLinePosition = currentDetectedLinePosition;
    return currentDetectedLinePosition;
  } else {
    return RowLinePosition::lineNotFound;
  }
}




template <int8_t totalRowCount>
int8_t Line<totalRowCount>::updateLine(uint8_t rowIndex, RowLinePosition & position) {

  if (lineBottomRowIndex < 0) {
    setLineBottom(rowIndex, position.getLinePosition());
    startEdge.init(position.getLineSegmentStart(), position.getLinePosition());
    endEdge.init(position.getLineSegmentEnd(),position.getLinePosition());
    return position.getLinePosition();

  } else {
    if (areSegmentsTouching(position)) {
      startEdge.update(position.getLineSegmentStart());
      endEdge.update(position.getLineSegmentEnd());

      if (startEdge.isContinues() && endEdge.isContinues()) {
        startEdge.calculateLinePositionToEdge(position.getLinePosition());
        endEdge.calculateLinePositionToEdge(position.getLinePosition());
        return position.getLinePosition();
      } else if (startEdge.isContinues()) {
        startEdge.calculateLinePositionToEdgeDecreaseOnly(position.getLinePosition());
        return startEdge.getLinePositionFromEdge();
      } else if (endEdge.isContinues()) {
        endEdge.calculateLinePositionToEdgeDecreaseOnly(position.getLinePosition());
        return endEdge.getLinePositionFromEdge();
      } else {
        return RowLinePosition::lineNotFound;
      }

    } else {
      return RowLinePosition::lineNotFound;
    }
  }
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::areSegmentsTouching(RowLinePosition & position) {
  return ((position.getLineSegmentEnd() - startEdge.currentStepPosition >= -2)
          && (endEdge.currentStepPosition - position.getLineSegmentStart() >= -2));
}





template <int8_t totalRowCount>
void Line<totalRowCount>::setLineBottom(uint8_t rowIndex, int8_t position) {
  lineBottomRowIndex = rowIndex;
  lineBottomPosition = position;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineTop(uint8_t rowIndex, int8_t position) {
  lineTopRowIndex = rowIndex;
  lineTopPosition = position;
}


template <int8_t totalRowCount>
constexpr int8_t Line<totalRowCount>::getTotalRowCount() {
  return totalRowCount;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isLineIdentified() {
  return lineTopRowIndex >= 0;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstRowIndex() {
  return  lineBottomRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineFirstPosition() {
  return lineBottomPosition;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastRowIndex() {
  return lineTopRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineLastPosition() {
  return lineTopPosition;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getStartEdgeStepCount() {
  return startEdge.currentStepCount;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getEndEdgeStepCount() {
  return endEdge.currentStepCount;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isStartEdgeContinues() {
  return startEdge.isContinues();
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isEndEdgeContinues() {
  return endEdge.isContinues();
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINE_H
