//
// Created by indrek on 12.11.2016.
//

#include "Line.h"





Line::Line() {
  resetLine();
}


void Line::resetLine() {
  previousLinePos = 0;
  lineFirstRowIndex = -1;
  lineFirstRowPos = 0;
  lineLastRowIndex = -1;
  lineLastRowPos = 0;
  minLineSlantCoefficient = 0x7FFF;
  maxLineSlantCoefficient = -0x7FFF;
  lineFound = false;
}



int8_t Line::setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow) {
  if (!lineFound) {

    RowLinePosition position(bitmapHigh, bitmapLow);
    int8_t linePos = position.getLinePosition(previousLinePos);
    uint16_t lineCoefficient = processNewLinePosition(rowIndex, linePos);

    if (RowLinePosition::isLineNotFound(linePos) || isTurnOnRow(rowIndex, lineCoefficient)) {
      if (lineFirstRowIndex >= 0) {
        setLineLastRow(rowIndex, previousLinePos);
      }
    } else {
      if (lineFirstRowIndex < 0) {
        setLineFirstRow(rowIndex, linePos);
      }
      if (rowIndex == rowCount - 1) {
        setLineLastRow(rowCount, linePos);
      }
    }

    previousLinePos = linePos;
    previousLineSlantCoefficient = lineCoefficient;
    return linePos;
  } else {
    return RowLinePosition::lineNotFound;
  }
}





int16_t Line::processNewLinePosition(uint8_t rowIndex, int8_t linePos) {
  if (RowLinePosition::isInRange(linePos)) {
    if (lineFirstRowIndex >= 0) {
      int16_t lineCoefficient = (((int16_t)(lineFirstRowPos - linePos)) << 10) / ((int16_t)rowIndex - (int16_t)lineFirstRowIndex);
      if (minLineSlantCoefficient > lineCoefficient) minLineSlantCoefficient = lineCoefficient;
      if (maxLineSlantCoefficient < lineCoefficient) maxLineSlantCoefficient = lineCoefficient;
      return lineCoefficient;
    } else {
      lineFirstRowIndex = rowIndex;
      lineFirstRowPos = linePos;
      return 0;
    }
  }
  return 0;
}


void Line::setLineFirstRow(uint8_t rowIndex, int8_t linePos) {
  lineFirstRowIndex = rowIndex;
  lineFirstRowPos = linePos;
}


void Line::setLineLastRow(uint8_t rowIndex, int8_t linePos) {
  lineFound = true;
  lineLastRowIndex = rowIndex - (uint8_t)1;
  lineLastRowPos = linePos;
}



bool Line::isTurnOnRow(uint8_t rowIndex, int16_t lineCoefficient) {
  if (lineFirstRowIndex < 0 || (rowIndex - lineFirstRowIndex < 2)) {
    return false;
  } else {
    return (abs(lineCoefficient - minLineSlantCoefficient) > turnCoefficient)
           || (abs(lineCoefficient - maxLineSlantCoefficient) > turnCoefficient);
  }
}




int8_t Line::getRowCount() {
  return rowCount;
}

bool Line::isLineFound() {
  return lineFound;
}

int8_t Line::getLineFirstRowIndex() {
  return lineFirstRowIndex;
}

int8_t Line::getLineFirstRowPosition() {
  return lineFirstRowPos;
}

int8_t Line::getLineLastRowIndex() {
  return lineLastRowIndex;
}

int8_t Line::getLineLastRowPosition() {
  return lineLastRowPos;
}







