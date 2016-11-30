//
// Created by indrek on 30.10.2016.
//


#include "line/RowBitmapLineSegmentFinder.h"
#include "gtest/gtest.h"





TEST(RowLinePositionTest, testLineNotFound) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000000, 0b00000000, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_TRUE(linePosition.isLineNotFound(linePos));
}


TEST(RowLinePositionTest, testLineInTheMiddle) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000001, 0b10000000, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(15, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge1) {
  RowBitmapLineSegmentFinder linePosition(60, 0b10000000, 0b00000000, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(30, linePos);
}


TEST(RowLinePositionTest, testLineOnTheEdge2) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000000, 0b00000001, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(0, linePos);
}


TEST(RowLinePositionTest, testOhterLineBeforeCenterLine) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000010, 0b00000110, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testOhterLineAfterCenterLine) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00110010, 0b00000000, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(18, linePos);
}


TEST(RowLinePositionTest, testWideLine) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000111, 0b11000000, RowBitmapLineSegmentFinder::rowRangeMidPoint, RowBitmapLineSegmentFinder::rowRangeMidPoint);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(16, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint1) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00010001, 0b11000110, 22, 23);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(24, linePos);
}


TEST(RowLinePositionTest, testShiftedSeekPoint2) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00010001, 0b11000110, 4, 6);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(3, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekRight) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000000, 0b01100100, 11, 12);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(11, linePos);
}


TEST(RowLinePositionTest, testTwoNegatwesSeekLeft) {
  RowBitmapLineSegmentFinder linePosition(60, 0b00000000, 0b01100100, 4, 5);
  int8_t linePos = linePosition.getLinePosition();
  ASSERT_EQ(4, linePos);
}



TEST(RowLinePositionTest, ignoreBottomCorners2pixels) {
  RowBitmapLineSegmentFinder linePosition1(7, 0b11000000, 0b00000000, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  int8_t linePos1 = linePosition1.getLinePosition();
  ASSERT_TRUE(linePosition1.isLineNotFound(linePos1));

  RowBitmapLineSegmentFinder linePosition2(7, 0b11100000, 0b00000000, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  int8_t linePos2 = linePosition2.getLinePosition();
  ASSERT_EQ(30, linePos2);
}



TEST(RowLinePositionTest, ignoreBottomCorners1pixels) {
  RowBitmapLineSegmentFinder linePosition1(18, 0b00000000, 0b00000001, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  int8_t linePos1 = linePosition1.getLinePosition();
  ASSERT_TRUE(linePosition1.isLineNotFound(linePos1));

  RowBitmapLineSegmentFinder linePosition2(18, 0b0000000, 0b00000011, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  int8_t linePos2 = linePosition2.getLinePosition();
  ASSERT_EQ(0, linePos2);

  RowBitmapLineSegmentFinder linePosition3(30, 0b00000000, 0b00000001, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  int8_t linePos3 = linePosition3.getLinePosition();
  ASSERT_EQ(0, linePos3);
}






TEST(RowLinePositionTest, testSegmentBeforeAndAfter) {
  RowBitmapLineSegmentFinder linePosition1(60, 0b00000111, 0b00000000, RowBitmapLineSegmentFinder::lineNotFound, RowBitmapLineSegmentFinder::lineNotFound);
  ASSERT_EQ(18, linePosition1.getLinePosition());
  ASSERT_FALSE(linePosition1.isLineBefore());
  ASSERT_FALSE(linePosition1.isLineAfter());

  // only before
  RowBitmapLineSegmentFinder linePosition2(60, 0b00000111, 0b00000110, 15, 16);
  ASSERT_EQ(18, linePosition2.getLinePosition());
  ASSERT_TRUE(linePosition2.isLineBefore());
  ASSERT_EQ(3, linePosition2.getLineBeforePosition());
  ASSERT_EQ(2, linePosition2.getLineBeforeSegmentStart());
  ASSERT_EQ(4, linePosition2.getLineBeforeSegmentEnd());
  ASSERT_FALSE(linePosition2.isLineAfter());

  // before and after
  RowBitmapLineSegmentFinder linePosition3(60, 0b11110111, 0b00000110, 15, 16);
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
  RowBitmapLineSegmentFinder linePosition4(60, 0b00111000, 0b01100111, 24, 25);
  ASSERT_EQ(24, linePosition4.getLinePosition());
  ASSERT_TRUE(linePosition4.isLineBefore());
  ASSERT_EQ(11, linePosition4.getLineBeforePosition());
  ASSERT_EQ(10, linePosition4.getLineBeforeSegmentStart());
  ASSERT_EQ(12, linePosition4.getLineBeforeSegmentEnd());
  ASSERT_FALSE(linePosition4.isLineAfter());

  // two after
  RowBitmapLineSegmentFinder linePosition5(60, 0b00111000, 0b01100111, 2, 3);
  ASSERT_EQ(0, linePosition5.getLinePosition());
  ASSERT_FALSE(linePosition5.isLineBefore());
  ASSERT_TRUE(linePosition5.isLineAfter());
  ASSERT_EQ(11, linePosition5.getLineAfterPosition());
  ASSERT_EQ(10, linePosition5.getLineAfterSegmentStart());
  ASSERT_EQ(12, linePosition5.getLineAfterSegmentEnd());
}




TEST(RowLinePositionTest, testCooseCorrectPathOnSplit) {
  // all segments touching seek segment. Choose closest to middle of the screen
  RowBitmapLineSegmentFinder linePosition1(60, 0b11001100, 0b00001111, 2, 28);
  ASSERT_EQ(21, linePosition1.getLinePosition());

  // all segments touching seek segment. Choose closest to middle of the screen
  RowBitmapLineSegmentFinder linePosition2(60, 0b00000011, 0b01100000, 0, 16);
  ASSERT_EQ(17, linePosition2.getLinePosition());

  // No segments touching seek segment. Choose closest to seek position
  RowBitmapLineSegmentFinder linePosition3(60, 0b01100000, 0b11000000, 23, 24);
  ASSERT_EQ(27, linePosition3.getLinePosition());
}




