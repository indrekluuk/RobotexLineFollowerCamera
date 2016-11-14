//
// Created by indrek on 30.10.2016.
//


#include "line/RowLinePosition.h"
#include "gtest/gtest.h"





TEST(RowLinePositionTest, testLineNotFound) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000000, 0b00000000);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_TRUE(linePosition.isLineNotFound(linePos));
}


TEST(RowLinePositionTest, testLineInTheMiddle) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000001, 0b10000000);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(0, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge1) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b01000000, 0b00000000);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(13, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge2) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000000, 0b00000010);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(-13, linePos);
}


TEST(RowLinePositionTest, testOhterLineBeforeCenterLine) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000010, 0b00000110);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(3, linePos);
}


TEST(RowLinePositionTest, testOhterLineAfterCenterLine) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00110010, 0b00000000);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(3, linePos);
}


TEST(RowLinePositionTest, testWideLine) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000111, 0b11000000);
  int8_t linePos = linePosition.getLinePosition(0);
  ASSERT_EQ(1, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint1) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00010001, 0b11000110);
  int8_t linePos = linePosition.getLinePosition(7);
  ASSERT_EQ(9, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint2) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00010001, 0b11000110);
  int8_t linePos = linePosition.getLinePosition(-9);
  ASSERT_EQ(-12, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekRight) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000000, 0b01100100);
  int8_t linePos = linePosition.getLinePosition(-3);
  ASSERT_EQ(-4, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekLeft) {
  //                             76543210    01234567
  RowLinePosition linePosition(0b00000000, 0b01100100);
  int8_t linePos = linePosition.getLinePosition(-11);
  ASSERT_EQ(-11, linePos);
}

