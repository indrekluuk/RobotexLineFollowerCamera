//
// Created by indrek on 13.11.2016.
//


#include "line/Line.h"
#include "gtest/gtest.h"



TEST(LineTest, testLineNotFound) {
  Line<120> line;
  ASSERT_FALSE(line.isLineFound());
}



TEST(LineTest, testEndOfLineNotFoundYet) {
  Line<120> line;
  line.setRowBitmap(0, 0b00010000, 0b00000000);
  line.setRowBitmap(1, 0b00010000, 0b00000000);
  line.setRowBitmap(2, 0b00010000, 0b00000000);
  ASSERT_FALSE(line.isLineFound());
}



TEST(LineTest, testLineFound) {
  Line<120> line;
  line.setRowBitmap(0, 0b00010000, 0b00000000);
  line.setRowBitmap(1, 0b00010000, 0b00000000);
  line.setRowBitmap(2, 0b00010000, 0b00000000);
  line.setRowBitmap(3, 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(24, line.getLineLastRowPosition());
}



TEST(LineTest, testLineAcrossTheScreen) {
  Line<6> line;
  line.setRowBitmap(0, 0b000010000, 0b000000000);
  line.setRowBitmap(1, 0b000010000, 0b000000000);
  line.setRowBitmap(2, 0b000010000, 0b000000000);
  line.setRowBitmap(3, 0b000010000, 0b000000000);
  line.setRowBitmap(4, 0b000010000, 0b000000000);
  ASSERT_FALSE(line.isLineFound());
  line.setRowBitmap(5, 0b000010000, 0b000000000);
  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(24, line.getLineLastRowPosition());
}




TEST(LineTest, testSlantedLine) {
  Line<120> line;
  line.setRowBitmap(0, 0b00000010, 0b00000000);
  line.setRowBitmap(1, 0b00000010, 0b00000000);
  line.setRowBitmap(2, 0b00000010, 0b00000000);
  line.setRowBitmap(3, 0b00000100, 0b00000000);
  line.setRowBitmap(4, 0b00000100, 0b00000000);
  line.setRowBitmap(5, 0b00000100, 0b00000000);
  line.setRowBitmap(6, 0b00001000, 0b00000000);
  line.setRowBitmap(7, 0b00001000, 0b00000000);
  line.setRowBitmap(8, 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(22, line.getLineLastRowPosition());
}




TEST(LineTest, testLineTurnsInSlantDirection) {
  Line<120> line;
  line.setRowBitmap( 0, 0b00000000, 0b00000010);
  line.setRowBitmap( 1, 0b00000000, 0b00000010);
  line.setRowBitmap( 2, 0b00000000, 0b00000010);
  line.setRowBitmap( 3, 0b00000000, 0b00000100);
  line.setRowBitmap( 4, 0b00000000, 0b00000100);
  line.setRowBitmap( 5, 0b00000000, 0b00000100);
  line.setRowBitmap( 6, 0b00000000, 0b00001000);
  line.setRowBitmap( 7, 0b00000000, 0b00001000);
  line.setRowBitmap( 8, 0b00000000, 0b00001000);
  line.setRowBitmap( 9, 0b00000000, 0b11110000);
  line.setRowBitmap(10, 0b00000111, 0b10000000);
  line.setRowBitmap(11, 0b00111100, 0b00000000);
  line.setRowBitmap(12, 0b01100000, 0b00000000);
  line.setRowBitmap(13, 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(6, line.getLineLastRowPosition());
}




TEST(LineTest, testLineTurnsAwayFromSlantDirection) {
  Line<120> line;
  line.setRowBitmap(0,  0b00000010, 0b00000000);
  line.setRowBitmap(1,  0b00000010, 0b00000000);
  line.setRowBitmap(2,  0b00000100, 0b00000000);
  line.setRowBitmap(3,  0b00000100, 0b00000000);
  line.setRowBitmap(5,  0b00001000, 0b00000000);
  line.setRowBitmap(6,  0b00001000, 0b00000000);
  line.setRowBitmap(7,  0b00010000, 0b00000000);
  line.setRowBitmap(8,  0b00010000, 0b00000000);
  line.setRowBitmap(9,  0b00000111, 0b11110000);
  line.setRowBitmap(10, 0b00000000, 0b11111111);
  line.setRowBitmap(11, 0b00000000, 0b00000000);
  line.setRowBitmap(12, 0b00000000, 0b00000000);
  line.setRowBitmap(13, 0b00000000, 0b00000000);
  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(24, line.getLineLastRowPosition());
}




TEST(LineTest, testIgnoreOtherLine) {
  Line<120> line;
  line.setRowBitmap(0,  0b00000010, 0b00000000);
  line.setRowBitmap(1,  0b00000010, 0b00000000);
  line.setRowBitmap(2,  0b00000010, 0b00000000);
  line.setRowBitmap(3,  0b00000100, 0b00100000);
  line.setRowBitmap(4,  0b00000100, 0b00100000);
  line.setRowBitmap(5,  0b00000100, 0b00110000);
  line.setRowBitmap(6,  0b00000000, 0b00010000);
  line.setRowBitmap(7,  0b00000000, 0b00011000);
  line.setRowBitmap(8,  0b00000000, 0b00001000);
  line.setRowBitmap(9,  0b00000000, 0b00001000);
  line.setRowBitmap(10, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(20, line.getLineLastRowPosition());
}





TEST(LineTest, testIgnoreOtherLineEndsAftercurrentLine) {
  Line<120> line;
  line.setRowBitmap( 0, 0b00000000, 0b00001000);
  line.setRowBitmap( 1, 0b00000000, 0b00001000);
  line.setRowBitmap( 2, 0b00000000, 0b00010000);
  line.setRowBitmap( 3, 0b00000000, 0b00010000);
  line.setRowBitmap( 4, 0b00000000, 0b00100000);
  line.setRowBitmap( 5, 0b00000000, 0b00100000);
  line.setRowBitmap( 6, 0b10000000, 0b01000000);
  line.setRowBitmap( 7, 0b10000000, 0b01000000);
  line.setRowBitmap( 8, 0b10000000, 0b00000000);
  line.setRowBitmap( 9, 0b10000000, 0b00000000);
  line.setRowBitmap(10, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(7, line.getLineLastRowIndex());
  ASSERT_EQ(12, line.getLineLastRowPosition());
}





TEST(LineTest, testIgnoreLineAfter) {
  Line<120> line;
  line.setRowBitmap(0,  0b00000010, 0b00000000);
  line.setRowBitmap(1,  0b00000010, 0b00000000);
  line.setRowBitmap(2,  0b00000010, 0b00000000);
  line.setRowBitmap(3,  0b00000100, 0b00000000);
  line.setRowBitmap(4,  0b00000100, 0b00000000);
  line.setRowBitmap(5,  0b00001000, 0b00000000);
  line.setRowBitmap(6,  0b00000000, 0b00000000);
  line.setRowBitmap(7,  0b00000000, 0b00001000);
  line.setRowBitmap(8,  0b00000000, 0b00001000);
  line.setRowBitmap(9,  0b00000000, 0b00001000);
  line.setRowBitmap(10, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(22, line.getLineLastRowPosition());
}



TEST(LineTest, testIgnoreLineAfterGap) {
  Line<120> line;
  line.setRowBitmap(0,  0b00000010, 0b00000000);
  line.setRowBitmap(1,  0b00000010, 0b00000000);
  line.setRowBitmap(2,  0b00000010, 0b00000000);
  line.setRowBitmap(3,  0b00000100, 0b00000000);
  line.setRowBitmap(4,  0b00000100, 0b00000000);
  line.setRowBitmap(5,  0b00000000, 0b00000000);
  line.setRowBitmap(6,  0b00001000, 0b00000000);
  line.setRowBitmap(7,  0b00001000, 0b00000000);
  line.setRowBitmap(8,  0b00010000, 0b00000000);
  line.setRowBitmap(9,  0b00010000, 0b00000000);
  line.setRowBitmap(10, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(20, line.getLineLastRowPosition());
  ASSERT_EQ(4, line.getLineLastRowIndex());
}




TEST(LineTest, testJaggedLine) {
  Line<120> line;
  line.setRowBitmap(0, 0b00000000, 0b00001100);
  line.setRowBitmap(1, 0b00000000, 0b00001100);
  line.setRowBitmap(2, 0b00000000, 0b00011100);
  line.setRowBitmap(3, 0b00000000, 0b00011000);
  line.setRowBitmap(4, 0b00000000, 0b00011000);
  line.setRowBitmap(5, 0b00000000, 0b00111000);
  line.setRowBitmap(6, 0b00000000, 0b00110000);
  line.setRowBitmap(7, 0b00000000, 0b00110000);
  line.setRowBitmap(8, 0b00000111, 0b11110000);
  line.setRowBitmap(9, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(8, line.getLineLastRowIndex());
  ASSERT_EQ(9, line.getLineLastRowPosition());
}







TEST(LineTest, testStepGetsShorter) {
  Line<120> line;
  line.setRowBitmap( 0, 0b00000000, 0b00000100);
  line.setRowBitmap( 1, 0b00000000, 0b00000100);
  line.setRowBitmap( 2, 0b00000000, 0b00000100);
  line.setRowBitmap( 3, 0b00000000, 0b00000100);
  line.setRowBitmap( 4, 0b00000000, 0b00000100);
  line.setRowBitmap( 5, 0b00000000, 0b00001000);
  line.setRowBitmap( 6, 0b00000000, 0b00001000);
  line.setRowBitmap( 7, 0b00000000, 0b00001000);
  line.setRowBitmap( 8, 0b00000000, 0b00001000);
  line.setRowBitmap( 9, 0b00000000, 0b00001000);
  line.setRowBitmap(10, 0b00000000, 0b00010000);
  line.setRowBitmap(11, 0b00000000, 0b00010000);
  line.setRowBitmap(12, 0b00000000, 0b00010000);
  line.setRowBitmap(13, 0b00000000, 0b00010000);
  line.setRowBitmap(14, 0b00000000, 0b00010000);
  line.setRowBitmap(15, 0b00000000, 0b00100000);
  line.setRowBitmap(16, 0b00000000, 0b00100000);
  line.setRowBitmap(17, 0b00000000, 0b01000000);
  line.setRowBitmap(18, 0b00000000, 0b01000000);
  line.setRowBitmap(19, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(14, line.getLineLastRowIndex());
  ASSERT_EQ(8, line.getLineLastRowPosition());
}





TEST(LineTest, testActiveLinePosEdge1) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(0, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(1, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(2, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(3, 0b00000000, 0b00000001);
  ASSERT_EQ(0, pos);
  pos = line.setRowBitmap(4, 0b00000000, 0b00000011);
  ASSERT_EQ(0, pos);
  pos = line.setRowBitmap(5, 0b00000000, 0b00000010);
  ASSERT_EQ(2, pos);
  pos = line.setRowBitmap(6, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
}




TEST(LineTest, testActiveLinePosEdge2) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(0, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(1, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(2, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
  pos = line.setRowBitmap(3, 0b10000000, 0b00000000);
  ASSERT_EQ(30, pos);
  pos = line.setRowBitmap(4, 0b11000000, 0b00000000);
  ASSERT_EQ(30, pos);
  pos = line.setRowBitmap(5, 0b01000000, 0b00000000);
  ASSERT_EQ(28, pos);
  pos = line.setRowBitmap(6, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
}





TEST(LineTest, testStepLengthVariation) {
  Line<120> line;
  line.setRowBitmap( 0, 0b00000000, 0b00000100);
  line.setRowBitmap( 1, 0b00000000, 0b00000100);
  line.setRowBitmap( 2, 0b00000000, 0b00000100);
  line.setRowBitmap( 3, 0b00000000, 0b00000100);
  line.setRowBitmap( 4, 0b00000000, 0b00001000);
  line.setRowBitmap( 5, 0b00000000, 0b00001000);
  line.setRowBitmap( 6, 0b00000000, 0b00001000);
  line.setRowBitmap( 7, 0b00000000, 0b00001000);
  line.setRowBitmap( 8, 0b00000000, 0b00010000);
  line.setRowBitmap( 9, 0b00000000, 0b00010000);
  line.setRowBitmap(10, 0b00000000, 0b00010000);
  line.setRowBitmap(11, 0b00000000, 0b00010000);
  line.setRowBitmap(12, 0b00000000, 0b00100000);
  line.setRowBitmap(13, 0b00000000, 0b00100000);
  line.setRowBitmap(14, 0b00000000, 0b00100000);
  line.setRowBitmap(15, 0b00000000, 0b01000000);
  line.setRowBitmap(16, 0b00000000, 0b01000000);
  line.setRowBitmap(17, 0b00000000, 0b01000000);
  line.setRowBitmap(18, 0b00000000, 0b01000000);
  line.setRowBitmap(19, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(18, line.getLineLastRowIndex());
  ASSERT_EQ(12, line.getLineLastRowPosition());
}




TEST(LineTest, testActiveLineSplit) {
  Line<120> line;
  int8_t pos;
  pos = line.setRowBitmap(0, 0b01111111, 0b11111100);
  ASSERT_EQ(16, pos);
  pos = line.setRowBitmap(1, 0b00011110, 0b00000110);
  ASSERT_EQ(21, pos);
  pos = line.setRowBitmap(2, 0b00110000, 0b00000010);
  ASSERT_EQ(25, pos);
  pos = line.setRowBitmap(3, 0b00100000, 0b00000010);
  ASSERT_EQ(26, pos);
  pos = line.setRowBitmap(4, 0b00100000, 0b00000010);
  ASSERT_EQ(26, pos);
  pos = line.setRowBitmap(5, 0b00000000, 0b00000000);
  ASSERT_EQ(-1, pos);
}






TEST(LineTest, testStartFromTheMiddle) {
  Line<120> line;
  line.setRowBitmap(0, 0b00000111, 0b11110011);
  line.setRowBitmap(1, 0b00000011, 0b11000011);
  line.setRowBitmap(2, 0b00000011, 0b10000011);
  line.setRowBitmap(3, 0b00000011, 0b00000001);
  line.setRowBitmap(4, 0b00000011, 0b00000000);
  line.setRowBitmap(5, 0b00000000, 0b00000000);

  ASSERT_TRUE(line.isLineFound());
  ASSERT_EQ(4, line.getLineLastRowIndex());
  ASSERT_EQ(17, line.getLineLastRowPosition());
}




