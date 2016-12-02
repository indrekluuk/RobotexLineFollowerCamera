//
// Created by indrek on 30.10.2016.
//


#include "line/RowBitmapLineSegmentFinder.h"
#include "gtest/gtest.h"





TEST(RowBitmapLineSegmentFinderTest, testLineNotFound) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000000, 0b00000000);
  ASSERT_FALSE(lineFinder.isLineFound());
}


TEST(RowBitmapLineSegmentFinderTest, testLineInTheMiddle) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000001, 0b10000000, LineSegment(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint));
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(15, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testLineOnTheEdge1) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b10000000, 0b00000000);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(30, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testLineOnTheEdge2) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000000, 0b00000001);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(0, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testOhterLineBeforeCenterLine) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000010, 0b00000110);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(18, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testOhterLineAfterCenterLine) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00110010, 0b00000000);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(18, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testWideLine) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000111, 0b11000000);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(16, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testShiftedSeekPoint1) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00010001, 0b11000110, LineSegment(22, 23));
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(24, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testShiftedSeekPoint2) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00010001, 0b11000110, LineSegment(4, 6));
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(3, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testTwoNegatwesSeekRight) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000000, 0b01100100, LineSegment(11, 12));
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(11, lineFinder.getFirstLine().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testTwoNegatwesSeekLeft) {
  RowBitmapLineSegmentFinder lineFinder;
  lineFinder.nextRow(60, 0b00000000, 0b01100100, LineSegment(4, 5));
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(4, lineFinder.getFirstLine().getLinePosition());
}



TEST(RowBitmapLineSegmentFinderTest, ignoreBottomCorners2pixels) {
  RowBitmapLineSegmentFinder lineFinder1;
  lineFinder1.nextRow(7, 0b11000000, 0b00000000);
  ASSERT_FALSE(lineFinder1.isLineFound());

  RowBitmapLineSegmentFinder lineFinder2;
  lineFinder2.nextRow(7, 0b11100000, 0b00000000);
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_EQ(28, lineFinder2.getFirstLine().getLinePosition());
}



TEST(RowBitmapLineSegmentFinderTest, ignoreBottomCorners1pixels) {
  RowBitmapLineSegmentFinder lineFinder1;
  lineFinder1.nextRow(18, 0b00000000, 0b00000001);
  ASSERT_FALSE(lineFinder1.isLineFound());

  RowBitmapLineSegmentFinder lineFinder2;
  lineFinder2.nextRow(18, 0b00000000, 0b00000011);
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_EQ(1, lineFinder2.getFirstLine().getLinePosition());

  RowBitmapLineSegmentFinder lineFinder3;
  lineFinder3.nextRow(30, 0b000000000, 0b00000001);
  ASSERT_TRUE(lineFinder3.isLineFound());
  ASSERT_EQ(0, lineFinder3.getFirstLine().getLinePosition());
}




TEST(RowBitmapLineSegmentFinderTest, testLine) {
  // first segments to go to split segments if more than two found
  RowBitmapLineSegmentFinder lineFinder1;
  lineFinder1.nextRow(60, 0b11001100, 0b00001111, LineSegment(2, 28));
  ASSERT_TRUE(lineFinder1.isLineFound());
  ASSERT_TRUE(lineFinder1.isLineSplit());
  ASSERT_EQ(3, lineFinder1.getFirstLine().getLinePosition());
  ASSERT_EQ(21, lineFinder1.getSecondLine().getLinePosition());

  // select only segments that are covered with previous line section
  RowBitmapLineSegmentFinder lineFinder2;
  lineFinder2.nextRow(60, 0b01100011, 0b01100011, LineSegment(6, 16));
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_TRUE(lineFinder2.isLineSplit());
  ASSERT_EQ(11, lineFinder2.getFirstLine().getLinePosition());
  ASSERT_EQ(17, lineFinder2.getSecondLine().getLinePosition());

  // Only one segment matching previous line then no split
  RowBitmapLineSegmentFinder lineFinder3;
  lineFinder3.nextRow(60, 0b01100000, 0b11001100, LineSegment(10, 16));
  ASSERT_TRUE(lineFinder3.isLineFound());
  ASSERT_FALSE(lineFinder3.isLineSplit());
  ASSERT_EQ(13, lineFinder3.getFirstLine().getLinePosition());
}




