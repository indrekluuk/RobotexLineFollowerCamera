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

    static const int8_t ignoreTurnDetectionToLine = 50;
    static const int8_t splitDetectionToLine = 60;
    static const int8_t splitDetectionMinimumLineCount = 25;
    static const int8_t lineTurn = -1;

    int8_t currentRowIndex;
    RowBitmapLineSegmentFinder bitmapLineFinder;
    LineEdge startEdge;
    LineEdge endEdge;

    bool splitDetected;
    int8_t previousLinePosition;
    int8_t previousAltLine1Position;
    int8_t previousAltLine2Position;

    int8_t lineBottomRowIndex;
    int8_t lineBottomPosition;
    int8_t lineFirstTurnRowIndex;
    int8_t lineFirstTurnPosition;
    int8_t lineTopCandidateRowIndex;
    int8_t lineTopCandidatePosition;
    int8_t lineTopRowIndex;
    int8_t lineTopPosition;
    bool isEndOfLine;

public:

    Line();

    void resetLine();
    void setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    inline bool isIdentifiedLine() __attribute__((always_inline));
    inline int8_t getIdentifiedLine() __attribute__((always_inline));
    inline bool isSplitDetectionLine() __attribute__((always_inline));
    inline int8_t getFirstSplitDetectionLine() __attribute__((always_inline));
    inline int8_t getSecondSplitDetectionLine() __attribute__((always_inline));

    constexpr static int8_t getTotalRowCount();
    bool isLineTopFound();
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
    int8_t updateLine(LineSegment &lineSegment);
    inline bool isLastRow(int8_t rowIndex) __attribute__((always_inline));
    inline void setLineBottom(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineFirstTurn(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTopCandidate(uint8_t rowIndex, int8_t position) __attribute__((always_inline));
    inline void setLineTop(uint8_t rowIndex, int8_t linePosition, int8_t altLine1Position, int8_t altLine2Position, bool isEnd) __attribute__((always_inline));
};






template <int8_t totalRowCount>
Line<totalRowCount>::Line() {
  resetLine();
}


template <int8_t totalRowCount>
void Line<totalRowCount>::resetLine() {
  currentRowIndex = -1;
  bitmapLineFinder.reset();
  startEdge.reset();
  endEdge.reset();

  splitDetected = false;
  previousLinePosition = LineSegment::rowRangeMidPoint;
  previousAltLine1Position = LineSegment::lineNotFound;
  previousAltLine2Position = LineSegment::lineNotFound;

  lineBottomRowIndex = -1;
  lineBottomPosition = -1;
  lineFirstTurnRowIndex = -1;
  lineFirstTurnPosition = -1;
  lineTopCandidateRowIndex = -1;
  lineTopCandidatePosition = -1;
  lineTopRowIndex = -1;
  lineTopPosition = -1;
  isEndOfLine = false;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  currentRowIndex = rowIndex;
  int8_t currentLinePosition = LineSegment::lineNotFound;
  int8_t currentAltLine1Position = LineSegment::lineNotFound;
  int8_t currentAltLine2Position = LineSegment::lineNotFound;

  if (lineTopRowIndex <0) {
    bitmapLineFinder.nextRow(rowIndex, bitmapHigh, bitmapLow);
    if (!bitmapLineFinder.isLineFound()) {
      if (lineBottomRowIndex >= 0) {
        if (lineTopCandidateRowIndex >= 0) {
          setLineTop(lineTopCandidateRowIndex, lineTopCandidatePosition, LineSegment::lineNotFound, LineSegment::lineNotFound, true);
        } else {
          setLineTop(rowIndex - 1, previousLinePosition, previousAltLine1Position, previousAltLine2Position, true);
        }
      }
    } else if (bitmapLineFinder.isLineSplit()) {
      splitDetected = true;
      // if line split then do nothing until one of the forks has ended
      currentAltLine1Position = bitmapLineFinder.getFirstLine().getLinePosition();
      currentAltLine2Position = bitmapLineFinder.getSecondLine().getLinePosition();
      if (isLastRow(rowIndex)) {
        setLineTop(rowIndex, LineSegment::lineNotFound, currentAltLine1Position, currentAltLine2Position, true);
      }
    } else {
      LineSegment &lineSegment = bitmapLineFinder.getSingleLine();

      if (splitDetected || lineTopCandidatePosition >= 0) {
        // top line candidate already. check some additional lines to check for possible splits.
        if ((rowIndex >= splitDetectionToLine)
            && (rowIndex >= (lineTopCandidateRowIndex + splitDetectionMinimumLineCount))) {

          if (splitDetected) {
            setLineTop(rowIndex, lineSegment.getLinePosition(), LineSegment::lineNotFound, LineSegment::lineNotFound, false);
          } else {
            // if line was not split then use candidate as line top
            setLineTop(lineTopCandidateRowIndex, lineTopCandidatePosition, LineSegment::lineNotFound, LineSegment::lineNotFound, false);
          }
          currentLinePosition = lineSegment.getLinePosition();
        } else {
          currentAltLine1Position = lineSegment.getLinePosition();
        }

      } else {
        // if possible line top not found yet then look for line top

        if (lineBottomRowIndex < 0) {
          setLineBottom(rowIndex, lineSegment.getLinePosition());
        }

        currentLinePosition = updateLine(lineSegment);

        if (currentLinePosition == lineTurn) {
          if (rowIndex < ignoreTurnDetectionToLine) {
            // if in the ignore turn zone then just store the point as first turn
            if (lineFirstTurnRowIndex < 0) {
              setLineFirstTurn(rowIndex, previousLinePosition);
            }
            currentLinePosition = lineSegment.getLinePosition();
          } else {
            // turn after ignoring zone is candidate for line top. Continue a little further to check for line split
            setLineTopCandidate(rowIndex - 1, previousLinePosition);
            // set Alt line since from here we do the split seek
            currentAltLine1Position = lineSegment.getLinePosition();
          }

        } else {
          // reached top of the screen
          if (isLastRow(rowIndex)) {
            setLineTop(rowIndex, currentLinePosition, LineSegment::lineNotFound, LineSegment::lineNotFound, true);
          }
        }
      }
    }
  }

  previousLinePosition = currentLinePosition;
  previousAltLine1Position = currentAltLine1Position;
  previousAltLine2Position = currentAltLine2Position;
}




template <int8_t totalRowCount>
int8_t Line<totalRowCount>::updateLine(LineSegment &lineSegment) {
  if (!startEdge.isInitialized()) {
    startEdge.init(lineSegment.getStart(), lineSegment.getLinePosition());
    endEdge.init(lineSegment.getEnd(),lineSegment.getLinePosition());
    return lineSegment.getLinePosition();
  } else {

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
      startEdge.resetFirstStepTo(lineSegment.getStart(), lineSegment.getLinePosition());
      endEdge.resetFirstStepTo(lineSegment.getEnd(), lineSegment.getLinePosition());
      return lineTurn;
    }
  }
}



template <int8_t totalRowCount>
bool Line<totalRowCount>::isLastRow(int8_t rowIndex) {
  return rowIndex == totalRowCount - 1;
}





template <int8_t totalRowCount>
bool Line<totalRowCount>::isIdentifiedLine() {
  return previousLinePosition >= 0;
}

template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getIdentifiedLine() {
  return previousLinePosition;
}

template <int8_t totalRowCount>
bool Line<totalRowCount>::isSplitDetectionLine() {
  return previousAltLine1Position >= 0 || previousAltLine2Position >= 0;
}


template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getFirstSplitDetectionLine() {
  return previousAltLine1Position;
}

template <int8_t totalRowCount>
int8_t Line<totalRowCount>::getSecondSplitDetectionLine() {
  return previousAltLine2Position;
}





template <int8_t totalRowCount>
void Line<totalRowCount>::setLineBottom(uint8_t rowIndex, int8_t position) {
  lineBottomRowIndex = rowIndex;
  lineBottomPosition = position;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineFirstTurn(uint8_t rowIndex, int8_t position) {
  lineFirstTurnRowIndex = rowIndex;
  lineFirstTurnPosition = position;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineTopCandidate(uint8_t rowIndex, int8_t position) {
  lineTopCandidateRowIndex = rowIndex;
  lineTopCandidatePosition = position;
}


template <int8_t totalRowCount>
void Line<totalRowCount>::setLineTop(uint8_t rowIndex, int8_t linePosition, int8_t altLine1Position, int8_t altLine2Position, bool isEnd) {
  lineTopRowIndex = rowIndex;
  if (linePosition != LineSegment::lineNotFound) {
    lineTopPosition = linePosition;
  } else if (altLine1Position != LineSegment::lineNotFound && altLine2Position != LineSegment::lineNotFound) {
    lineTopPosition = abs(altLine1Position - LineSegment::rowRangeMidPoint)
                      < abs(altLine2Position - LineSegment::rowRangeMidPoint) ?
                      altLine1Position : altLine2Position;
  } else {
    lineTopPosition = LineSegment::rowRangeMidPoint;
  }

  isEndOfLine = isEnd;
}


template <int8_t totalRowCount>
constexpr int8_t Line<totalRowCount>::getTotalRowCount() {
  return totalRowCount;
}


template <int8_t totalRowCount>
bool Line<totalRowCount>::isLineTopFound() {
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
