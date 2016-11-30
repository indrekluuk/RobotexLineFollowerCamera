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

    RowBitmapLineSegmentFinder bitmapLineFinder;
    LineEdge startEdge;
    LineEdge endEdge;
    int8_t previousDetectedLinePosition;

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
    int8_t updateLine(uint8_t rowIndex, LineSegment &lineSegment);
    inline void setLineBottom(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTop(uint8_t rowIndex, int8_t position, bool isEnd) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  bitmapLineFinder.reset();
  startEdge.reset();
  endEdge.reset();

  previousDetectedLinePosition = LineSegment::rowRangeMidPoint;

  lineBottomRowIndex = -1;
  lineBottomPosition = -1;
  lineTopRowIndex = -1;
  lineTopPosition = -1;
  isEndOfLine = false;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {

  if (lineTopRowIndex <0) {
    bitmapLineFinder.nextRow(rowIndex, bitmapHigh, bitmapLow);
    int8_t currentDetectedLinePosition = LineSegment::lineNotFound;

    if (!bitmapLineFinder.isLineFound()) {
      if (lineBottomRowIndex >= 0) {
        setLineTop(rowIndex-1, previousDetectedLinePosition, true);
      }
    } else {
      LineSegment &lineSegment = bitmapLineFinder.getFirstLine();

      if (lineBottomRowIndex < 0) {
        setLineBottom(rowIndex, lineSegment.getLinePosition());
      }

      //currentDetectedLinePosition = updateLine(rowIndex, lineSegment);
      currentDetectedLinePosition = lineSegment.getLinePosition();

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

    previousDetectedLinePosition = currentDetectedLinePosition;
    return currentDetectedLinePosition;
  } else {
    return LineSegment::lineNotFound;
  }
}




template <int8_t totalRowCount>
int8_t Line<totalRowCount>::updateLine(uint8_t rowIndex, LineSegment &lineSegment) {
  if (bitmapLineFinder.isLineFound()) {
    return lineEnd;
  } else {
    return lineSegment.getLinePosition();
  }



  /*

  if (!startEdge.isInitialized()) {
    startEdge.init(lineSegment.getStart(), lineSegment.getLinePosition());
    endEdge.init(lineSegment.getEnd(),lineSegment.getLinePosition());
    return lineSegment.getLinePosition();
  } else {
    if (lineSegment.touchesSegment(startEdge.currentStepPosition, endEdge.currentStepPosition)) {

      if (rowIndex < turnDetectionFromLine) {
        startEdge.resetFirstStepTo(lineSegment.getStart(), lineSegment.getLinePosition());
        endEdge.resetFirstStepTo(lineSegment.getEnd(), lineSegment.getLinePosition());
        return lineSegment.getLinePosition();
      }

      startEdge.update(lineSegment.getStart());
      endEdge.update(lineSegment.getEnd());

      if (startEdge.isContinues() && endEdge.isContinues()) {
        startEdge.calculateLinePositionToEdge(lineSegment.getLinePosition());
        endEdge.calculateLinePositionToEdge(lineSegment.getLinePosition());
        return lineSegment.getLinePosition();
      } else if (startEdge.isContinues()) {
        startEdge.calculateLinePositionToEdgeDecreaseOnly(lineSegment.getLinePosition());
        return startEdge.getLinePositionFromEdge();
      } else if (endEdge.isContinues()) {
        endEdge.calculateLinePositionToEdgeDecreaseOnly(lineSegment.getLinePosition());
        return endEdge.getLinePositionFromEdge();
      } else {
        return lineTurn;
      }

    } else {
      return lineEnd;
    }
  }
   */
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
