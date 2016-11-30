//
// Created by indrek on 30.10.2016.
//


#include "line/RowBitmapLineSegmentFinder.h"
#include "gtest/gtest.h"





TEST(RowBitmapLineSegmentFinderTest, testLineNotFound) {
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000000, 0b00000000, nullptr);
  ASSERT_FALSE(lineFinder.isLineFound());
}


TEST(RowBitmapLineSegmentFinderTest, testLineInTheMiddle) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000001, 0b10000000, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(15, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testLineOnTheEdge1) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b10000000, 0b00000000, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(30, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testLineOnTheEdge2) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000000, 0b00000001, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(0, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testOhterLineBeforeCenterLine) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000010, 0b00000110, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(18, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testOhterLineAfterCenterLine) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00110010, 0b00000000, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(18, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testWideLine) {
  LineSegment seek(LineSegment::rowRangeMidPoint, LineSegment::rowRangeMidPoint);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000111, 0b11000000, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(16, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testShiftedSeekPoint1) {
  LineSegment seek(22, 23);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00010001, 0b11000110, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(24, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testShiftedSeekPoint2) {
  LineSegment seek(4, 6);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00010001, 0b11000110, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(3, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testTwoNegatwesSeekRight) {
  LineSegment seek(11, 12);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000000, 0b01100100, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(11, lineFinder.getFoundLineSegment().getLinePosition());
}


TEST(RowBitmapLineSegmentFinderTest, testTwoNegatwesSeekLeft) {
  LineSegment seek(4, 5);
  RowBitmapLineSegmentFinder lineFinder(60, 0b00000000, 0b01100100, &seek);
  ASSERT_TRUE(lineFinder.isLineFound());
  ASSERT_EQ(4, lineFinder.getFoundLineSegment().getLinePosition());
}



TEST(RowBitmapLineSegmentFinderTest, ignoreBottomCorners2pixels) {
  RowBitmapLineSegmentFinder lineFinder1(7, 0b11000000, 0b00000000, nullptr);
  ASSERT_FALSE(lineFinder1.isLineFound());

  RowBitmapLineSegmentFinder lineFinder2(7, 0b11100000, 0b00000000, nullptr);
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_EQ(30, lineFinder2.getFoundLineSegment().getLinePosition());
}



TEST(RowBitmapLineSegmentFinderTest, ignoreBottomCorners1pixels) {
  RowBitmapLineSegmentFinder lineFinder1(18, 0b00000000, 0b00000001, nullptr);
  ASSERT_FALSE(lineFinder1.isLineFound());

  RowBitmapLineSegmentFinder lineFinder2(18, 0b0000000, 0b00000011, nullptr);
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_EQ(0, lineFinder2.getFoundLineSegment().getLinePosition());

  RowBitmapLineSegmentFinder lineFinder3(30, 0b00000000, 0b00000001, nullptr);
  ASSERT_TRUE(lineFinder3.isLineFound());
  ASSERT_EQ(0, lineFinder3.getFoundLineSegment().getLinePosition());
}




TEST(RowBitmapLineSegmentFinderTest, testCooseCorrectPathOnSplit) {
  // all segments touching seek segment. Choose closest to middle of the screen
  LineSegment seek1(2, 28);
  RowBitmapLineSegmentFinder lineFinder1(60, 0b11001100, 0b00001111, &seek1);
  ASSERT_TRUE(lineFinder1.isLineFound());
  ASSERT_EQ(21, lineFinder1.getFoundLineSegment().getLinePosition());

  // all segments touching seek segment. Choose closest to middle of the screen
  LineSegment seek2(0, 16);
  RowBitmapLineSegmentFinder lineFinder2(60, 0b00000011, 0b01100000, &seek2);
  ASSERT_TRUE(lineFinder2.isLineFound());
  ASSERT_EQ(17, lineFinder2.getFoundLineSegment().getLinePosition());

  // No segments touching seek segment. Choose closest to seek position
  LineSegment seek3(23, 24);
  RowBitmapLineSegmentFinder lineFinder3(60, 0b01100000, 0b11000000, &seek3);
  ASSERT_TRUE(lineFinder3.isLineFound());
  ASSERT_EQ(27, lineFinder3.getFoundLineSegment().getLinePosition());
}




