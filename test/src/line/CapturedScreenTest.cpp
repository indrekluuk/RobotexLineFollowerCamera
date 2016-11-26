//
// Created by indrek on 13.11.2016.
//


#include "TestScreenProcessor.h"
#include "gtest/gtest.h"

#include "screencapture/Capture1.h"
#include "screencapture/Capture2.h"
#include "screencapture/Capture3.h"
#include "screencapture/Capture4.h"
#include "screencapture/Capture5.h"




TEST(CapturedScreenTest, testCapture1) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_1);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(101, line.getLineLastRowIndex());
  ASSERT_EQ(13, line.getLineLastPosition());
}


TEST(CapturedScreenTest, testCapture2) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_2);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(82, line.getLineLastRowIndex());
  ASSERT_EQ(11, line.getLineLastPosition());
}


TEST(CapturedScreenTest, testCapture3) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_3);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(87, line.getLineLastRowIndex());
  ASSERT_EQ(6, line.getLineLastPosition());
}


TEST(CapturedScreenTest, testCapture4) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_4);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(79, line.getLineLastRowIndex());
  ASSERT_EQ(4, line.getLineLastPosition());
}


TEST(CapturedScreenTest, testCapture5) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_5);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(88, line.getLineLastRowIndex());
  ASSERT_EQ(4, line.getLineLastPosition());
}

