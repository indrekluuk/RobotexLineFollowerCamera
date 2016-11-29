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

    static const int8_t turnDetectionFromLine = 50;
    static const int8_t lineEnd = -1;
    static const int8_t lineTurn = -2;

    LineEdge startEdge;
    LineEdge endEdge;
    int8_t previousDetectedLinePosition;
    int8_t lineSeekPosition;

    int8_t segmentBeforeStart;
    int8_t segmentBeforeEnd;
    bool segmentBeforeMerged;

    int8_t segmentAfterStart;
    int8_t segmentAfterEnd;
    bool segmentAfterMerged;

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


    bool isSharpTurn();
    bool getSharpTurnDirection();
    bool isMergedBefore();
    int8_t getMergedBeforePosition();
    bool isMergedAfter();
    int8_t getMergedAfterPosition();

    int8_t getStartEdgeStepCount();
    int8_t getEndEdgeStepCount();
    bool isStartEdgeContinues();
    bool isEndEdgeContinues();


private:
    int8_t updateLine(uint8_t rowIndex, RowLinePosition & position);
    void processBeforeAndAfterSegments(uint8_t rowIndex, RowLinePosition & position);
    inline bool areSegmentsTouching(RowLinePosition & position) __attribute__((always_inline));
    inline bool areSegmentsTouching(int8_t start1, int8_t end1, int8_t start2, int8_t end2) __attribute__((always_inline));
    inline void setLineBottom(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTop(uint8_t rowIndex, int8_t position, bool isEnd) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  lineSeekPosition = RowLinePosition::lineNotFound;
  previousDetectedLinePosition = RowLinePosition::rowRangeMidPoint;
  startEdge.reset();
  endEdge.reset();

  segmentBeforeStart = -1;
  segmentBeforeEnd = -1;
  segmentBeforeMerged = false;

  segmentAfterStart = -1;
  segmentAfterEnd = -1;
  segmentAfterMerged = false;

  lineBottomRowIndex = -1;
  lineBottomPosition = -1;
  lineTopRowIndex = -1;
  lineTopPosition = -1;
  isEndOfLine = false;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {

  if (lineTopRowIndex <0) {
    RowLinePosition position(rowIndex, bitmapHigh, bitmapLow, lineSeekPosition);
    int8_t currentDetectedLinePosition = RowLinePosition::lineNotFound;

    if (position.isLineNotFound()) {
      if (lineBottomRowIndex >= 0) {
        setLineTop(rowIndex-1, previousDetectedLinePosition, true);
      }
    } else {
      if (lineBottomRowIndex < 0) {
        setLineBottom(rowIndex, position.getLinePosition());
      }

      processBeforeAndAfterSegments(rowIndex, position);

      currentDetectedLinePosition = updateLine(rowIndex, position);
      if (currentDetectedLinePosition == lineTurn) {
        setLineTop(rowIndex - 1, previousDetectedLinePosition, false);
      } else if (currentDetectedLinePosition == lineEnd) {
        setLineTop(rowIndex - 1, previousDetectedLinePosition, true);
      } else {
        if (rowIndex == totalRowCount - 1) {
          setLineTop(rowIndex, position.getLinePosition(), true);
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
  if (!startEdge.isInitialized()) {
    startEdge.init(position.getLineSegmentStart(), position.getLinePosition());
    endEdge.init(position.getLineSegmentEnd(),position.getLinePosition());
    return position.getLinePosition();
  } else {
    if (areSegmentsTouching(position)) {

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
void Line<totalRowCount>::processBeforeAndAfterSegments(uint8_t rowIndex, RowLinePosition & position) {

  if (!segmentBeforeMerged) {
    if (segmentBeforeStart != -1 && areSegmentsTouching(
        segmentBeforeStart, segmentBeforeEnd,
        position.getLineSegmentStart(), position.getLineSegmentEnd()
    )) {
      segmentBeforeMerged = true;
    } else {
      if (position.isLineBefore()) {
        if (segmentBeforeStart == -1 || !areSegmentsTouching(
            segmentBeforeStart, segmentBeforeEnd,
            position.getLineBeforeSegmentStart(), position.getLineBeforeSegmentEnd()
        )) {
          segmentBeforeStart = position.getLineBeforeSegmentStart();
        }
        segmentBeforeEnd = position.getLineBeforeSegmentEnd();
      } else {
        segmentBeforeStart = -1;
        segmentBeforeEnd = -1;
      }
    }
  }


  if (!segmentAfterMerged) {
    if (segmentAfterStart != -1 && areSegmentsTouching(
        segmentAfterStart, segmentAfterEnd,
        position.getLineSegmentStart(), position.getLineSegmentEnd()
    )) {
      segmentAfterMerged = true;
    } else {
      if (position.isLineAfter()) {
        segmentAfterStart = position.getLineAfterSegmentStart();
        if (segmentAfterStart == -1 || !areSegmentsTouching(
            segmentAfterStart, segmentAfterEnd,
            position.getLineAfterSegmentStart(), position.getLineAfterSegmentEnd()
        )) {
          segmentAfterEnd = position.getLineAfterSegmentEnd();
        }
      } else {
        segmentAfterStart = -1;
        segmentAfterEnd = -1;
      }
    }
  }

}



template <int8_t totalRowCount>
bool Line<totalRowCount>::areSegmentsTouching(RowLinePosition & position) {
  return areSegmentsTouching(
      position.getLineSegmentStart(),
      position.getLineSegmentEnd(),
      startEdge.currentStepPosition,
      endEdge.currentStepPosition);
}

template <int8_t totalRowCount>
bool Line<totalRowCount>::areSegmentsTouching(int8_t start1, int8_t end1, int8_t start2, int8_t end2) {
  return ((end1 - start2 >= -2) && (end2- start1 >= -2));
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
bool Line<totalRowCount>::isSharpTurn() {
  return isMergedAfter() || isMergedBefore();
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::getSharpTurnDirection() {
  if (getMergedBeforePosition() == -1) {
    return true;
  }
  if (getMergedAfterPosition() == -1) {
    return false;
  }
  return (abs(getLineTopPosition() - getMergedBeforePosition())
          > abs(getLineTopPosition() - getMergedAfterPosition())) ? false : true;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isMergedBefore() {
  return segmentBeforeMerged;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getMergedBeforePosition() {
  return segmentBeforeStart;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isMergedAfter() {
  return segmentAfterMerged;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getMergedAfterPosition() {
  return segmentAfterEnd;
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
