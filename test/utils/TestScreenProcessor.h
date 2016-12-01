//
// Created by indrek on 26.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_TESTSCREENPROCESSOR_H
#define ROBOTEXLINEFOLLOWERCAMERA_TESTSCREENPROCESSOR_H


#include "line/Line.h"
#include <iostream>
#include <iomanip>



struct LineData {
    uint16_t pixelData;
    int8_t singleLinePos;
    int8_t altLine1Pos;
    int8_t altLine2Pos;
    int8_t startEdgeCount;
    int8_t endEdgeCount;
    bool startEdgeOk;
    bool endEdgeOk;
};



template <int8_t rowCount>
class TestScreenProcessor {

    Line<rowCount> &line;

public:
    TestScreenProcessor(Line<rowCount> &line);
    void process(uint16_t (&pixelData)[rowCount]);

private:
    void printScreen(LineData (&lineData)[rowCount]);

};






template <int8_t rowCount>
TestScreenProcessor<rowCount>::TestScreenProcessor(Line<rowCount> &line) : line(line) {
}



template <int8_t rowCount>
void TestScreenProcessor<rowCount>::process(uint16_t (&pixelData)[rowCount]) {
  LineData lineData[rowCount];
  for (int i=rowCount-1; i>=0; i--) {
    uint8_t rowIndex = rowCount-i-1;
    uint16_t screenRow = pixelData[i];
    lineData[i].pixelData = screenRow;
    line.setRowBitmap(rowIndex, (screenRow >> 8) & 0xFF, (screenRow) & 0xFF);

    lineData[i].singleLinePos = line.isLine() ? line.getLine() : -1;
    lineData[i].altLine1Pos = line.isSplit() ? line.getFirstLine() : -1;
    lineData[i].altLine2Pos = line.isSplit() ? line.getSecondLine() : -1;

    lineData[i].startEdgeCount = line.getStartEdgeStepCount();
    lineData[i].endEdgeCount = line.getEndEdgeStepCount();
    lineData[i].startEdgeOk = line.isStartEdgeContinues();
    lineData[i].endEdgeOk = line.isEndEdgeContinues();

  }
  printScreen(lineData);
}


template <int8_t rowCount>
void TestScreenProcessor<rowCount>::printScreen(LineData (&lineData)[rowCount]) {
  std::cout << "\n";
  for (int i=0; i<rowCount; i++) {
    LineData & data = lineData[i];
    std::string screenLine;
    for (uint32_t mask = 0x8000; mask >= 0x0001; mask >>= 1) {
      screenLine += (data.pixelData & mask ? "  " : "[]");
    }
    if (data.singleLinePos >= 0) {
      screenLine[31 - data.singleLinePos] = '*';
      screenLine[30 - data.singleLinePos] = '*';
    }
    if (data.altLine1Pos >= 0) {
      screenLine[31-data.altLine1Pos] = '.';
      screenLine[30-data.altLine1Pos] = '.';
    }
    if (data.altLine2Pos >= 0) {
      screenLine[31-data.altLine2Pos] = '.';
      screenLine[30-data.altLine2Pos] = '.';
    }

    std::cout
        << std::setw(3) << std::setfill('0') << (rowCount - i - 1) << ": "
        << " " << std::setw(3) << std::setfill(' ') << (int)data.endEdgeCount << (data.endEdgeOk?"|":" ") << " "
        << screenLine << " "
        << " " << std::setw(3) << std::setfill(' ') << (int)data.startEdgeCount << (data.startEdgeOk?"|":" ") <<" "
        << "\n";
  }
  std::cout << "             28  24  20  16  12  08  04  00\n";
  std::cout << "           30  26  22  18  14  10  06  02\n";
}







#endif //ROBOTEXLINEFOLLOWERCAMERA_TESTSCREENPROCESSOR_H
