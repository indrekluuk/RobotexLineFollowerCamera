//
// Created by indrek on 13.11.2016.
//


#include "line/Line.h"
#include "gtest/gtest.h"

#include "screencapture/Capture1.h"
#include "screencapture/Capture2.h"
#include "screencapture/Capture3.h"
#include "screencapture/Capture4.h"
#include "screencapture/Capture5.h"




class CapturedScreenTest : public ::testing::Test
{
protected:
    static const int LINE_COUNT = 120;

    struct LineData {
        uint16_t pixelData;
        int8_t linePos;
    };
    Line<LINE_COUNT> line;

    void processScreen(uint16_t (&screen) [LINE_COUNT]) {
      LineData lineData[LINE_COUNT];
      for (int i=LINE_COUNT-1; i>=0; i--) {
        uint8_t rowIndex = LINE_COUNT-i-1;
        uint16_t screenRow = screen[i];
        lineData[i].pixelData = screenRow;
        lineData[i].linePos = line.setRowBitmap(rowIndex, (screenRow >> 8) & 0xFF, (screenRow) & 0xFF);
      }
      printScreen(lineData);
    }

    void printScreen(LineData (&lineData)[LINE_COUNT]) {
      std::cout << "\n";
      for (int i=0; i<LINE_COUNT; i++) {
        LineData & data = lineData[i];
        std::string screenLine;
        for (uint32_t mask = 0x8000; mask >= 0x0001; mask >>= 1) {
          screenLine += (data.pixelData & mask ? "  " : "[]");
        }
        if (data.linePos >= 0) {
          screenLine[31-data.linePos] = '*';
          screenLine[30-data.linePos] = '*';
        }
        std::cout << std::setw(3) << std::setfill('0') << (LINE_COUNT - i - 1);
        std::cout << ": " << screenLine << "\n";
      }
      std::cout << "       28  24  20  16  12  08  04  00\n";
      std::cout << "     30  26  22  18  14  10  06  02\n";
    }

};




TEST_F(CapturedScreenTest, testCapture1) {
  processScreen(capture_1);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(101, line.getLineLastRowIndex());
  ASSERT_EQ(13, line.getLineLastPosition());
}


TEST_F(CapturedScreenTest, testCapture2) {
  processScreen(capture_2);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(82, line.getLineLastRowIndex());
  ASSERT_EQ(11, line.getLineLastPosition());
}


TEST_F(CapturedScreenTest, testCapture3) {
  processScreen(capture_3);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(87, line.getLineLastRowIndex());
  ASSERT_EQ(6, line.getLineLastPosition());
}


TEST_F(CapturedScreenTest, testCapture4) {
  processScreen(capture_4);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(79, line.getLineLastRowIndex());
  ASSERT_EQ(4, line.getLineLastPosition());
}


TEST_F(CapturedScreenTest, testCapture5) {
  processScreen(capture_5);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(88, line.getLineLastRowIndex());
  ASSERT_EQ(4, line.getLineLastPosition());
}

