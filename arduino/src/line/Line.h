//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "LineEdge.h"
#include "RowBitmapLineSegmentFinder.h"
#include <Arduino.h>



template <int8_t totalRowCount>
class Line {

    static const int8_t turnDetectionFromLine = 5;
    static const int8_t lineEnd = -1;
    static const int8_t lineTurn = -2;

    LineEdge startEdge;
    LineEdge endEdge;
    int8_t previousDetectedLinePosition;
    int8_t lineSeekStart;
    int8_t lineSeekEnd;

    int8_t lineBottomRowIndex;
    int8_t lineBottomPosition;
    int8_t lineTopRowIndex;
    int8_t lineTopPosition;
    bool isEndOfLine;

public:

    Line();

    void resetLine();
    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    constexpr static int8_t getTotalRowCount();
    bool isLineIdentified();
    int8_t getLineBottomRowIndex();
    int8_t getLineBottomPosition();
    int8_t getLineTopRowIndex();
    int8_t getLineTopPosition();
    bool getIsEndOfLine();

    int8_t getStartEdgeStepCount();
    int8_t getEndEdgeStepCount();
    bool isStartEdgeContinues();
    bool isEndEdgeContinues();


private:
    int8_t updateLine(uint8_t rowIndex, RowBitmapLineSegmentFinder & position);
    void processBeforeAndAfterSegments(uint8_t rowIndex, RowBitmapLineSegmentFinder & position);
    inline bool doesPositionTouchLine(RowBitmapLineSegmentFinder & position) __attribute__((always_inline));
    inline void setLineBottom(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTop(uint8_t rowIndex, int8_t position, bool isEnd) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  lineSeekStart = RowBitmapLineSegmentFinder::lineNotFound;
  lineSeekEnd = RowBitmapLineSegmentFinder::lineNotFound;
  previousDetectedLinePosition = RowBitmapLineSegmentFinder::rowRangeMidPoint;
  startEdge.reset();
  endEdge.reset();

  lineBottomRowIndex = -1;
  lineBottomPosition = -1;
  lineTopRowIndex = -1;
  lineTopPosition = -1;
  isEndOfLine = false;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {

  if (lineTopRowIndex <0) {
    RowBitmapLineSegmentFinder position(rowIndex, bitmapHigh, bitmapLow, lineSeekStart, lineSeekEnd);
    int8_t currentDetectedLinePosition = RowBitmapLineSegmentFinder::lineNotFound;

    if (position.isLineNotFound()) {
      if (lineBottomRowIndex >= 0) {
        setLineTop(rowIndex-1, previousDetectedLinePosition, true);
      }
    } else {
      if (lineBottomRowIndex < 0) {
        setLineBottom(rowIndex, position.getLinePosition());
      }

      currentDetectedLinePosition = updateLine(rowIndex, position);
      if (currentDetectedLinePosition == lineTurn) {
        setLineTop(rowIndex - 1, previousDetectedLinePosition, false);
      } else if (currentDetectedLinePosition == lineEnd) {
        setLineTop(rowIndex - 1, previousDetectedLinePosition, true);
      } else {
        if (rowIndex == totalRowCount - 1) {
          setLineTop(rowIndex, currentDetectedLinePosition, true);
        }
      }
    }

    lineSeekStart = position.getLineSegmentStart();
    lineSeekEnd = position.getLineSegmentEnd();
    previousDetectedLinePosition = currentDetectedLinePosition;
    return currentDetectedLinePosition;
  } else {
    return RowBitmapLineSegmentFinder::lineNotFound;
  }
}




template <int8_t totalRowCount>
int8_t Line<totalRowCount>::updateLine(uint8_t rowIndex, RowBitmapLineSegmentFinder & position) {
  if (!startEdge.isInitialized()) {
    startEdge.init(position.getLineSegmentStart(), position.getLinePosition());
    endEdge.init(position.getLineSegmentEnd(),position.getLinePosition());
    return position.getLinePosition();
  } else {
    if (doesPositionTouchLine(position)) {

      if (rowIndex < turnDetectionFromLine) {
        startEdge.resetFirstStepTo(position.getLineSegmentStart(), position.getLinePosition());
        endEdge.resetFirstStepTo(position.getLineSegmentEnd(), position.getLinePosition());
        return position.getLinePosition();
      }

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
        return lineTurn;
      }

    } else {
      return lineEnd;
    }
  }
}




template <int8_t totalRowCount>
bool Line<totalRowCount>::doesPositionTouchLine(RowBitmapLineSegmentFinder & position) {
  return RowBitmapLineSegmentFinder::areSegmentsTouching(
      position.getLineSegmentStart(),
      position.getLineSegmentEnd(),
      startEdge.currentStepPosition,
      endEdge.currentStepPosition);
}




template <int8_t totalRowCount>
void Line<totalRowCount>::setLineBottom(uint8_t rowIndex, int8_t position) {
  lineBottomRowIndex = rowIndex;
  lineBottomPosition = position;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineTop(uint8_t rowIndex, int8_t position, bool isEnd) {
  lineTopRowIndex = rowIndex;
  lineTopPosition = position;
  isEndOfLine = isEnd;
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
int8_t Line<totalRowCount>::getLineBottomRowIndex() {
  return  lineBottomRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineBottomPosition() {
  return lineBottomPosition;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineTopRowIndex() {
  return lineTopRowIndex;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getLineTopPosition() {
  return lineTopPosition;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::getIsEndOfLine() {
  return isEndOfLine;
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
