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
#include "screencapture/Capture6.h"
#include "screencapture/Capture7.h"
#include "screencapture/Capture8.h"
#include "screencapture/Capture9.h"
#include "screencapture/Capture10.h"





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
  ASSERT_EQ(86, line.getLineLastRowIndex());
  ASSERT_EQ(10, line.getLineLastPosition());
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



TEST(CapturedScreenTest, testCapture6_reuseLine) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);

  screenProcessor.process(capture_6);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(77, line.getLineLastRowIndex());
  ASSERT_EQ(20, line.getLineLastPosition());

  line.resetLine();
  screenProcessor.process(capture_6);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(77, line.getLineLastRowIndex());
  ASSERT_EQ(20, line.getLineLastPosition());
}



TEST(CapturedScreenTest, testCapture7) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_7);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(81, line.getLineLastRowIndex());
  ASSERT_EQ(25, line.getLineLastPosition());
}



TEST(CapturedScreenTest, testCapture8) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_8);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(72, line.getLineLastRowIndex());
  ASSERT_EQ(27, line.getLineLastPosition());
}




TEST(CapturedScreenTest, testCapture9) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_9);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(45, line.getLineLastRowIndex());
  ASSERT_EQ(29, line.getLineLastPosition());
}




TEST(CapturedScreenTest, testCapture10) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_10);
  ASSERT_TRUE(line.isLineIdentified());
  ASSERT_EQ(52, line.getLineLastRowIndex());
  ASSERT_EQ(26, line.getLineLastPosition());
}






