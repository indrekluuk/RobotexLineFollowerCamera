//
// Created by indrek on 13.11.2016.
//


#include "line/Line.h"
#include "gtest/gtest.h"

#include "Capture1.h"




class CapturedScreenTest : public ::testing::Test
{
protected:
    static const int LINE_COUNT = 120;

    Line<LINE_COUNT> line;

    void processScreen(uint16_t (&screen) [LINE_COUNT]) {
      int8_t linePos[LINE_COUNT];
      for (int i=LINE_COUNT-1; i>=0; i--) {
        uint8_t rowIndex = LINE_COUNT-i-1;
        uint16_t screenRow = screen[i];
        linePos[i] = line.setRowBitmap(rowIndex, (screenRow >> 8) & 0xFF, (screenRow) & 0xFF);
      }
      printScreen(screen, linePos);
    }

    void printScreen(uint16_t (&screen) [LINE_COUNT], int8_t (&linePos) [LINE_COUNT]) {
      std::cout << "\n";
      for (int i=0; i<LINE_COUNT; i++) {
        std::string screenLine;
        for (uint32_t mask = 0x8000; mask >= 0x0001; mask >>= 1) {
          screenLine += (screen[i] & mask ? "  " : "[]");
        }
        if (linePos[i] >= 0) {
          screenLine[31-linePos[i]] = '*';
          screenLine[30-linePos[i]] = '*';
        }
        std::cout << std::setw(3) << std::setfill('0') << (LINE_COUNT - i - 1);
        std::cout << ": " << screenLine << "\n";
      }
      std::cout << "       28  24  20  16  12  08  04  00\n";
      std::cout << "     30  26  22  18  14  10  06  02\n";
    }

};




TEST_F(CapturedScreenTest, testScreen1) {
  processScreen(capture_1);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(100, line.getLineLastRowIndex());
  ASSERT_EQ(12, line.getLineLastPosition());
}



