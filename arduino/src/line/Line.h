//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "RowLinePosition.h"
#include <Arduino.h>




class Line {

    static const int8_t rowCount = 120;
    static const int16_t turnCoefficient = 1025;

    int8_t previousLinePos;
    int16_t previousLineSlantCoefficient;
    int16_t minLineSlantCoefficient;
    int16_t maxLineSlantCoefficient;
    int8_t lineFirstRowIndex;
    int8_t lineFirstRowPos;
    int8_t lineLastRowIndex;
    int8_t lineLastRowPos;
    bool lineFound;



public:
    Line();

    void resetLine();
    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    static int8_t getRowCount();
    bool isLineFound();
    int8_t getLineFirstRowIndex();
    int8_t getLineFirstRowPosition();
    int8_t getLineLastRowIndex();
    int8_t getLineLastRowPosition();


private:
    int16_t processNewLinePosition(uint8_t rowIndex, int8_t linePos);
    void setLineFirstRow(uint8_t rowIndex, int8_t linePos);
    void setLineLastRow(uint8_t rowIndex, int8_t linePos);
    bool isTurnOnRow(uint8_t rowIndex, int16_t lineCoefficient);


};


#endif //ROBOTEXLINEFOLLOWERCAMERA_LINE_H
