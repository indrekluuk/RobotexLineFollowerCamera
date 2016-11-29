//
// Created by indrek on 16.11.2016.
//

#include "RowLinePosition.h"






RowLinePosition::RowLinePosition(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow, int8_t seekPos)
    :
      rowIndex(rowIndex),
      bitmapHigh(bitmapHigh),
      bitmapLow(bitmapLow),
      lineSegmentStart(lineNotFound),
      lineSegmentEnd(lineNotFound),
      linePos(lineNotFound),
      lineBeforeSegmentStart(lineNotFound),
      lineBeforeSegmentEnd(lineNotFound),
      lineBeforePos(lineNotFound),
      lineAfterSegmentStart(lineNotFound),
      lineAfterSegmentEnd(lineNotFound),
      lineAfterPos(lineNotFound),
      lineSeekPos(seekPos)
{
  int8_t segmentStart = lineNotFound;
  if (rowIndex >= ignoreRows) {
    processPixel(bitmapLow  & (uint8_t)0b00000001,  0, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b00000010,  2, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b00000100,  4, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b00001000,  6, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b00010000,  8, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b00100000, 10, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b01000000, 12, segmentStart);
    processPixel(bitmapLow  & (uint8_t)0b10000000, 14, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00000001, 16, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00000010, 18, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00000100, 20, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00001000, 22, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00010000, 24, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b00100000, 26, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b01000000, 28, segmentStart);
    processPixel(bitmapHigh & (uint8_t)0b10000000, 30, segmentStart);

    if (segmentStart != lineNotFound) {
      processLineSegment(segmentStart, 30);
    }
  }
};




