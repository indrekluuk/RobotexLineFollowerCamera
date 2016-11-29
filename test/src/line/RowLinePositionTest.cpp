//
// Created by indrek on 30.10.2016.
//


#include "line/RowLinePosition.h"
#include "gtest/gtest.h"





TEST(RowLinePositionTest, testLineNotFound) {
  RowLinePosition linePosition(60, 0b00000000, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_TRUE(linePosition.isLineNotFound(linePos));
}


TEST(RowLinePositionTest, testLineInTheMiddle) {
  RowLinePosition linePosition(60, 0b00000001, 0b10000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(15, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge1) {
  RowLinePosition linePosition(60, 0b10000000, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(30, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge2) {
  RowLinePosition linePosition(60, 0b00000000, 0b00000001, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(0, linePos);
}


TEST(RowLinePositionTest, testOhterLineBeforeCenterLine) {
  RowLinePosition linePosition(60, 0b00000010, 0b00000110, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testOhterLineAfterCenterLine) {
  RowLinePosition linePosition(60, 0b00110010, 0b00000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testWideLine) {
  RowLinePosition linePosition(60, 0b00000111, 0b11000000, RowLinePosition::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(16, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint1) {
  RowLinePosition linePosition(60, 0b00010001, 0b11000110, 22);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(24, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint2) {
  RowLinePosition linePosition(60, 0b00010001, 0b11000110, 6);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(3, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekRight) {
  RowLinePosition linePosition(60, 0b00000000, 0b01100100, 12);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(11, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekLeft) {
  RowLinePosition linePosition(60, 0b00000000, 0b01100100, 4);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(4, linePos);
}



TEST(RowLinePositionTest, ignoreBottomCorners2pixels) {
  RowLinePosition linePosition1(7, 0b11000000, 0b00000000, RowLinePosition::lineNotFound);
  int8_t linePos1 = linePosition1.getLinePosition();
  ASSERT_TRUE(linePosition1.isLineNotFound(linePos1));

  RowLinePosition linePosition2(7, 0b11100000, 0b00000000, RowLinePosition::lineNotFound);
  int8_t linePos2 = linePosition2.getLinePosition();
  ASSERT_EQ(30, linePos2);
}



TEST(RowLinePositionTest, ignoreBottomCorners1pixels) {
  RowLinePosition linePosition1(18, 0b00000000, 0b00000001, RowLinePosition::lineNotFound);
  int8_t linePos1 = linePosition1.getLinePosition();
  ASSERT_TRUE(linePosition1.isLineNotFound(linePos1));

  RowLinePosition linePosition2(18, 0b0000000, 0b00000011, RowLinePosition::lineNotFound);
  int8_t linePos2 = linePosition2.getLinePosition();
  ASSERT_EQ(0, linePos2);

  RowLinePosition linePosition3(30, 0b00000000, 0b00000001, RowLinePosition::lineNotFound);
  int8_t linePos3 = linePosition3.getLinePosition();
  ASSERT_EQ(0, linePos3);
}






TEST(RowLinePositionTest, testSegmentBeforeAndAfter) {
  RowLinePosition linePosition1(60, 0b00000111, 0b00000000, RowLinePosition::lineNotFound);
  ASSERT_EQ(18, linePosition1.getLinePosition());
  ASSERT_FALSE(linePosition1.isLineBefore());
  ASSERT_FALSE(linePosition1.isLineAfter());

  // only before
  RowLinePosition linePosition2(60, 0b00000111, 0b00000110, 15);
  ASSERT_EQ(18, linePosition2.getLinePosition());
  ASSERT_TRUE(linePosition2.isLineBefore());
  ASSERT_EQ(3, linePosition2.getLineBeforePosition());
  ASSERT_EQ(2, linePosition2.getLineBeforeSegmentStart());
  ASSERT_EQ(4, linePosition2.getLineBeforeSegmentEnd());
  ASSERT_FALSE(linePosition2.isLineAfter());

  // before and after
  RowLinePosition linePosition3(60, 0b11110111, 0b00000110, 15);
  ASSERT_EQ(18, linePosition3.getLinePosition());
  ASSERT_TRUE(linePosition3.isLineBefore());
  ASSERT_EQ(3, linePosition3.getLineBeforePosition());
  ASSERT_EQ(2, linePosition3.getLineBeforeSegmentStart());
  ASSERT_EQ(4, linePosition3.getLineBeforeSegmentEnd());
  ASSERT_TRUE(linePosition3.isLineAfter());
  ASSERT_EQ(30, linePosition3.getLineAfterPosition());
  ASSERT_EQ(24, linePosition3.getLineAfterSegmentStart());
  ASSERT_EQ(30, linePosition3.getLineAfterSegmentEnd());

  // two before
  RowLinePosition linePosition4(60, 0b00111000, 0b01100111, 24);
  ASSERT_EQ(24, linePosition4.getLinePosition());
  ASSERT_TRUE(linePosition4.isLineBefore());
  ASSERT_EQ(11, linePosition4.getLineBeforePosition());
  ASSERT_EQ(10, linePosition4.getLineBeforeSegmentStart());
  ASSERT_EQ(12, linePosition4.getLineBeforeSegmentEnd());
  ASSERT_FALSE(linePosition4.isLineAfter());

  // two after
  RowLinePosition linePosition5(60, 0b00111000, 0b01100111, 2);
  ASSERT_EQ(0, linePosition5.getLinePosition());
  ASSERT_FALSE(linePosition5.isLineBefore());
  ASSERT_TRUE(linePosition5.isLineAfter());
  ASSERT_EQ(11, linePosition5.getLineAfterPosition());
  ASSERT_EQ(10, linePosition5.getLineAfterSegmentStart());
  ASSERT_EQ(12, linePosition5.getLineAfterSegmentEnd());
}






