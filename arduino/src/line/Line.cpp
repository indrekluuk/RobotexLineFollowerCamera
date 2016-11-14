//
// Created by indrek on 12.11.2016.
//

#include "Line.h"





Line::Line() {
  resetLine();
}



int8_t Line::getRowCount() {
  return rowCount;
}



int8_t Line::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (rowIndex < rowCount) {
    //uint16_t rowBitmap = ((((uint16_t)bitmapHigh) << 8) | ((uint16_t)bitmapLow)) & (uint16_t)0x7FFE;

    if (!lineFound) {
      RowLinePosition position(bitmapHigh, bitmapLow);
      int8_t linePos = position.getLinePosition(getPreviousLineLinePosition(rowIndex));
      setLinePosition(rowIndex, linePos);
      if (RowLinePosition::isLineNotFound(linePos) || isTurnOnRow(rowIndex)) {
        if (lineStartRow >= 0) {
          setLineLastRow(rowIndex);
        }
      } else {
        if (lineStartRow < 0) {
          lineStartRow = rowIndex;
        }
        if (rowIndex == rowCount - 1) {
          setLineLastRow(rowIndex);
        }
      }
    }
  }

  return 0;
}


void Line::resetLine() {
  lineStartRow = -1;
  lineEndRow = -1;
  lineFound = false;
}


int8_t Line::getPreviousLineLinePosition(uint8_t rowIndex) {
  uint8_t previousRowIndex = (uint8_t)(rowIndex - 1);
  return rowIndex == 0 || RowLinePosition::isLineNotFound(rowLinePositions[previousRowIndex]) ?
         (int8_t)0:
         rowLinePositions[previousRowIndex];
}



void Line::setLinePosition(uint8_t rowIndex, int8_t linePos) {
  rowLinePositions[rowIndex] = linePos;
  if (lineStartRow >= 0 && lineStartRow != rowIndex) {
    rowLineSlantCoefficient[rowIndex] =0;
        //(((int16_t)(rowLinePositions[lineStartRow] - linePos)) << 10) / ((int16_t)rowIndex);
  } else {
    rowLineSlantCoefficient[rowIndex] = 0;
  }
}



void Line::setLineLastRow(uint8_t rowIndex) {
  lineFound = true;
  lineEndRow = (uint8_t)(rowIndex - 1);
}



bool Line::isTurnOnRow(uint8_t rowIndex) {
  if (lineStartRow < 0 || (rowIndex - lineStartRow < 2)) {
    return false;
  } else {
    int16_t currentRowCoefficient = rowLineSlantCoefficient[rowIndex];
    for (int8_t i = lineStartRow; i <rowIndex; i++) {
      if (abs(rowLineSlantCoefficient[i] - currentRowCoefficient) > turnCoefficient) {
        return true;
      }
    }
  }
  return false;
}



bool Line::isLineFound() {
  return lineFound;
}



int8_t Line::getLinePosition() {
  if (lineEndRow >= 0) {
    return rowLinePositions[lineEndRow];
  } else {
    return 0;
  }
}


int8_t Line::getLineStartRow() {
  return lineStartRow;
}


int8_t Line::getLineEndRow() {
  return lineEndRow;
}








