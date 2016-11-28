//
// Created by indrek on 13.11.2016.
//


#include "line/Line.h"
#include "gtest/gtest.h"




uint8_t shiftIndex(uint8_t index) {
  return RowLinePosition::getIgnoreRowCount() + index;
}



TEST(LineTest, testLineNotFound) {
  Line<120> line;
  ASSERT_FALSE(line.isLineIdentified());
}



TEST(LineTest, testEndOfLineNotFoundYet) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(1), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(2), 0b00010000, 0b00000000);
  ASSERT_FALSE(line.isLineIdentified());
}



TEST(LineTest, testLineFound) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(1), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(2), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(3), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(24, line.getLineLastPosition());
}



TEST(LineTest, testLineAcrossTheScreen) {
  Line<11> line;
  line.setRowBitmap(shiftIndex(0), 0b000010000, 0b000000000);
  line.setRowBitmap(shiftIndex(1), 0b000010000, 0b000000000);
  line.setRowBitmap(shiftIndex(2), 0b000010000, 0b000000000);
  line.setRowBitmap(shiftIndex(3), 0b000010000, 0b000000000);
  line.setRowBitmap(shiftIndex(4), 0b000010000, 0b000000000);
  ASSERT_FALSE(line.isLineIdentified());
  line.setRowBitmap(shiftIndex(5), 0b000010000, 0b000000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(24, line.getLineLastPosition());
}




TEST(LineTest, testSlantedLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0), 0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(1), 0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(2), 0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(3), 0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(4), 0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(5), 0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(6), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(7), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(8), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(7), line.getLineLastRowIndex());
  ASSERT_EQ(22, line.getLineLastPosition());
}




TEST(LineTest, testLineTurnsInSlantDirection) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00000010);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00000010);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00000010);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 6), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 7), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 8), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 9), 0b00000000, 0b11110000);
  line.setRowBitmap(shiftIndex(10), 0b00000111, 0b10000000);
  line.setRowBitmap(shiftIndex(11), 0b00111100, 0b00000000);
  line.setRowBitmap(shiftIndex(12), 0b01100000, 0b00000000);
  line.setRowBitmap(shiftIndex(13), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(9), line.getLineLastRowIndex());
  ASSERT_EQ(8, line.getLineLastPosition());
}




TEST(LineTest, testLineTurnsAwayFromSlantDirection) {
  Line<120> line;
  line.setRowBitmap( 0, 0b00000010, 0b00000000);
  line.setRowBitmap( 1, 0b00000010, 0b00000000);
  line.setRowBitmap( 2, 0b00000100, 0b00000000);
  line.setRowBitmap( 3, 0b00000100, 0b00000000);
  line.setRowBitmap( 4, 0b00001000, 0b00000000);
  line.setRowBitmap( 5, 0b00001000, 0b00000000);
  line.setRowBitmap( 6, 0b00010000, 0b00000000);
  line.setRowBitmap( 7, 0b00010000, 0b00000000);
  line.setRowBitmap( 8, 0b00000111, 0b11110000);
  line.setRowBitmap( 9, 0b00000000, 0b11111111);
  line.setRowBitmap(10, 0b00000000, 0b00000000);
  line.setRowBitmap(11, 0b00000000, 0b00000000);
  line.setRowBitmap(11, 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(7, line.getLineLastRowIndex());
  ASSERT_EQ(24, line.getLineLastPosition());
}




TEST(LineTest, testIgnoreOtherLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(1),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(2),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(3),  0b00000100, 0b00100000);
  line.setRowBitmap(shiftIndex(4),  0b00000100, 0b00100000);
  line.setRowBitmap(shiftIndex(5),  0b00000100, 0b00110000);
  line.setRowBitmap(shiftIndex(6),  0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex(7),  0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex(8),  0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex(9),  0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex(10), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(5), line.getLineLastRowIndex());
  ASSERT_EQ(20, line.getLineLastPosition());
}





TEST(LineTest, testIgnoreOtherLineEndsAftercurrentLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00100000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00100000);
  line.setRowBitmap(shiftIndex( 6), 0b10000000, 0b01000000);
  line.setRowBitmap(shiftIndex( 7), 0b10000000, 0b01000000);
  line.setRowBitmap(shiftIndex( 8), 0b10000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 9), 0b10000000, 0b00000000);
  line.setRowBitmap(shiftIndex(10), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(7), line.getLineLastRowIndex());
  ASSERT_EQ(12, line.getLineLastPosition());
}





TEST(LineTest, testIgnoreLineAfter) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(1),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(2),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(3),  0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(4),  0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(5),  0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(6),  0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex(7),  0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex(8),  0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex(9),  0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex(10), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(22, line.getLineLastPosition());
}



TEST(LineTest, testIgnoreLineAfterGap) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(1),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(2),  0b00000010, 0b00000000);
  line.setRowBitmap(shiftIndex(3),  0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(4),  0b00000100, 0b00000000);
  line.setRowBitmap(shiftIndex(5),  0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex(6),  0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(7),  0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(8),  0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(9),  0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(10), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(4), line.getLineLastRowIndex());
  ASSERT_EQ(20, line.getLineLastPosition());
}




TEST(LineTest, testJaggedLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex(0), 0b00000000, 0b00001100);
  line.setRowBitmap(shiftIndex(1), 0b00000000, 0b00001100);
  line.setRowBitmap(shiftIndex(2), 0b00000000, 0b00011100);
  line.setRowBitmap(shiftIndex(3), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex(4), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex(5), 0b00000000, 0b00111000);
  line.setRowBitmap(shiftIndex(6), 0b00000000, 0b00110000);
  line.setRowBitmap(shiftIndex(7), 0b00000000, 0b00110000);
  line.setRowBitmap(shiftIndex(8), 0b00000111, 0b11110000);
  line.setRowBitmap(shiftIndex(9), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(8), line.getLineLastRowIndex());
  ASSERT_EQ(9, line.getLineLastPosition());
}





TEST(LineTest, testActiveLinePosEdge1) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(60, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(61, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(62, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(63, 0b00000000, 0b00000001);
  ASSERT_EQ(0, pos);
  pos = line.setRowBitmap(64, 0b00000000, 0b00000011);
  ASSERT_EQ(0, pos);
  pos = line.setRowBitmap(65, 0b00000000, 0b00000010);
  ASSERT_EQ(2, pos);
  pos = line.setRowBitmap(66, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
}




TEST(LineTest, testActiveLinePosEdge2) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(60, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(61, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(62, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(63, 0b10000000, 0b00000000);
  ASSERT_EQ(30, pos);
  pos = line.setRowBitmap(64, 0b11000000, 0b00000000);
  ASSERT_EQ(30, pos);
  pos = line.setRowBitmap(65, 0b01000000, 0b00000000);
  ASSERT_EQ(28, pos);
  pos = line.setRowBitmap(66, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
}





TEST(LineTest, testLineConnectedHorizonatllySingleLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex( 6), 0b00000000, 0b00100000);
  line.setRowBitmap(shiftIndex( 7), 0b00001111, 0b11100000);
  line.setRowBitmap(shiftIndex( 8), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex( 9), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(10), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(11), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(12), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(7), line.getLineLastRowIndex());
  ASSERT_EQ(10, line.getLineLastPosition());
}



TEST(LineTest, testLineConnectedHorizonatllyDoubleLine) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00000100);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00001000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00010000);
  line.setRowBitmap(shiftIndex( 5), 0b00000100, 0b00010000);
  line.setRowBitmap(shiftIndex( 6), 0b00001111, 0b11100000);
  line.setRowBitmap(shiftIndex( 7), 0b00001111, 0b11100000);
  line.setRowBitmap(shiftIndex( 8), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex( 9), 0b00001000, 0b00000000);
  line.setRowBitmap(shiftIndex(10), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(11), 0b00010000, 0b00000000);
  line.setRowBitmap(shiftIndex(12), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(7), line.getLineLastRowIndex());
  ASSERT_EQ(10, line.getLineLastPosition());
}






TEST(LineTest, testParallelLinesWithoutSteps) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 3), 0b00011111, 0b11111000);
  line.setRowBitmap(shiftIndex( 4), 0b00011111, 0b11111000);
  line.setRowBitmap(shiftIndex( 5), 0b00011000, 0b00000000);
  line.setRowBitmap(shiftIndex( 6), 0b00011000, 0b00000000);
  line.setRowBitmap(shiftIndex( 7), 0b00011000, 0b00000000);
  line.setRowBitmap(shiftIndex( 8), 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(4), line.getLineLastRowIndex());
  ASSERT_EQ(7, line.getLineLastPosition());
}






TEST(LineTest, twoStepLine) {
  Line<5> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00001100);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(1), line.getLineLastRowIndex());
  ASSERT_EQ(7, line.getLineLastPosition());
}





TEST(LineTest, testReUseLine) {
  Line<5> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(4), line.getLineLastRowIndex());
  ASSERT_EQ(7, line.getLineLastPosition());

  line.resetLine();
  line.setRowBitmap(shiftIndex( 0), 0b01100000, 0b00000000);
  line.setRowBitmap(shiftIndex( 1), 0b00110000, 0b00000000);
  line.setRowBitmap(shiftIndex( 2), 0b00011000, 0b00000000);
  line.setRowBitmap(shiftIndex( 3), 0b00001100, 0b00000000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(3), line.getLineLastRowIndex());
  ASSERT_EQ(21, line.getLineLastPosition());

  line.resetLine();
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00001100);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00011000);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000000);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(1), line.getLineLastRowIndex());
  ASSERT_EQ(7, line.getLineLastPosition());
}



TEST(LineTest, testIgnoreLineInCorner) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00000011);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00000011);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00000011);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00000110);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000110);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000110);
  line.setRowBitmap(shiftIndex( 6), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(3), line.getLineFirstRowIndex());
  ASSERT_EQ(3, line.getLineFirstPosition());
  ASSERT_EQ(shiftIndex(5), line.getLineLastRowIndex());
  ASSERT_EQ(3, line.getLineLastPosition());
}


TEST(LineTest, testDoNotIgnoreLineIfAlreadyDiscoverdBeforeCorner) {
  Line<120> line;
  line.setRowBitmap(shiftIndex( 0), 0b00000000, 0b00000001);
  line.setRowBitmap(shiftIndex( 1), 0b00000000, 0b00000001);
  line.setRowBitmap(shiftIndex( 2), 0b00000000, 0b00000111);
  line.setRowBitmap(shiftIndex( 3), 0b00000000, 0b00000001);
  line.setRowBitmap(shiftIndex( 4), 0b00000000, 0b00000001);
  line.setRowBitmap(shiftIndex( 5), 0b00000000, 0b00000001);
  line.setRowBitmap(shiftIndex( 6), 0b00000000, 0b00000010);
  line.setRowBitmap(shiftIndex( 7), 0b00000000, 0b00000010);
  line.setRowBitmap(shiftIndex( 8), 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(shiftIndex(2), line.getLineFirstRowIndex());
  ASSERT_EQ(0, line.getLineFirstPosition());
  ASSERT_EQ(shiftIndex(7), line.getLineLastRowIndex());
  ASSERT_EQ(2, line.getLineLastPosition());
}



TEST(LineTest, testMoveLineToEdgeIfSegmentTouchesEdge) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(60, 0b00000000, 0b00000111);
  ASSERT_EQ(0, pos);
  pos = line.setRowBitmap(61, 0b00000000, 0b00001110);
  ASSERT_EQ(4, pos);
  pos = line.setRowBitmap(62, 0b00000000, 0b00011100);
  ASSERT_EQ(6, pos);
  pos = line.setRowBitmap(63, 0b00000000, 0b00111000);
  ASSERT_EQ(8, pos);
  pos = line.setRowBitmap(64, 0b00000000, 0b01110000);
  ASSERT_EQ(10, pos);
  pos = line.setRowBitmap(65, 0b00000000, 0b11100000);
  ASSERT_EQ(12, pos);
  pos = line.setRowBitmap(66, 0b00000001, 0b11000000);
  ASSERT_EQ(14, pos);
  pos = line.setRowBitmap(67, 0b00000011, 0b10000000);
  ASSERT_EQ(16, pos);
  pos = line.setRowBitmap(68, 0b00000111, 0b00000000);
  ASSERT_EQ(18, pos);
  pos = line.setRowBitmap(69, 0b00001110, 0b00000000);
  ASSERT_EQ(20, pos);
  pos = line.setRowBitmap(70, 0b00011100, 0b00000000);
  ASSERT_EQ(22, pos);
  pos = line.setRowBitmap(71, 0b00111000, 0b00000000);
  ASSERT_EQ(24, pos);
  pos = line.setRowBitmap(72, 0b01110000, 0b00000000);
  ASSERT_EQ(26, pos);
  pos = line.setRowBitmap(73, 0b11100000, 0b00000000);
  ASSERT_EQ(30, pos);
  pos = line.setRowBitmap(74, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);

}






