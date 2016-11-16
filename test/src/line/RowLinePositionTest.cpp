//
// Created by indrek on 30.10.2016.
//


#include "line/RowLinePosition.h"
#include "gtest/gtest.h"





TEST(RowLinePositionTest, testLineNotFound) {
  RowLinePosition linePosition(0b00000000, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_TRUE(linePosition.isLineNotFound(linePos));
}


TEST(RowLinePositionTest, testLineInTheMiddle) {
  RowLinePosition linePosition(0b00000001, 0b10000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(15, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge1) {
  RowLinePosition linePosition(0b10000000, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(30, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge2) {
  RowLinePosition linePosition(0b00000000, 0b00000001, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(0, linePos);
}


TEST(RowLinePositionTest, testOhterLineBeforeCenterLine) {
  RowLinePosition linePosition(0b00000010, 0b00000110, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testOhterLineAfterCenterLine) {
  RowLinePosition linePosition(0b00110010, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testWideLine) {
  RowLinePosition linePosition(0b00000111, 0b11000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(16, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint1) {
  RowLinePosition linePosition(0b00010001, 0b11000110, 22);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(24, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint2) {
  RowLinePosition linePosition(0b00010001, 0b11000110, 6);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(3, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekRight) {
  RowLinePosition linePosition(0b00000000, 0b01100100, 12);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(11, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekLeft) {
  RowLinePosition linePosition(0b00000000, 0b01100100, 4);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(4, linePos);
}

