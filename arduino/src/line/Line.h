//
// Created by indrek on 12.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINE_H


#include "RowLinePosition.h"
#include <Arduino.h>




class Line {

    static const int8_t rowCount = 120;
    static const int16_t turnCoefficient = 1001;

    int8_t rowLinePositions[rowCount];
    int16_t rowLineSlantCoefficient[rowCount];

    int8_t lineStartRow;
    int8_t lineEndRow;
    bool lineFound;



public:
    Line();

    static int8_t getRowCount();

    void resetLine();

    int8_t setRowBitmap(uint8_t rowIndex, uint8_t bitmapHigh, uint8_t bitmapLow);

    bool isLineFound();
    int8_t getLinePosition();
    int8_t getLineStartRow();
    int8_t getLineEndRow();


private:
    int8_t getPreviousLineLinePosition(uint8_t rowIndex);
    void setLinePosition(uint8_t rowIndex, int8_t linePos);
    void setLineLastRow(uint8_t rowIndex);
    bool isTurnOnRow(uint8_t rowIndex);


};


#endif //ROBOTEXLINEFOLLOWERCAMERA_LINE_H
