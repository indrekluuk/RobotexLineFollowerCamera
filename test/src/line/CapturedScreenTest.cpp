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
#include "screencapture/Capture11.h"
#include "screencapture/Capture12.h"
#include "screencapture/Capture13.h"
#include "screencapture/Capture14.h"
#include "screencapture/Capture15.h"
#include "screencapture/Capture16.h"
#include "screencapture/Capture17.h"
#include "screencapture/Capture18.h"
#include "screencapture/Capture19.h"
#include "screencapture/Capture20.h"




TEST(CapturedScreenTest, testCapture1) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_1);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(104, line.getLineTopRowIndex());
  ASSERT_EQ(11, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture2) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_2);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(86, line.getLineTopRowIndex());
  ASSERT_EQ(10, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture3) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_3);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(87, line.getLineTopRowIndex());
  ASSERT_EQ(6, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture4) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_4);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(79, line.getLineTopRowIndex());
  ASSERT_EQ(4, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture5) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_5);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(88, line.getLineTopRowIndex());
  ASSERT_EQ(4, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture6_reuseLine) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);

  screenProcessor.process(capture_6);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(77, line.getLineTopRowIndex());
  ASSERT_EQ(20, line.getLineTopPosition());

  line.resetLine();
  screenProcessor.process(capture_6);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(77, line.getLineTopRowIndex());
  ASSERT_EQ(20, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture7) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_7);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(81, line.getLineTopRowIndex());
  ASSERT_EQ(25, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture8) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_8);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(72, line.getLineTopRowIndex());
  ASSERT_EQ(27, line.getLineTopPosition());
}




TEST(CapturedScreenTest, testCapture9) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_9);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(49, line.getLineTopRowIndex());
  ASSERT_EQ(30, line.getLineTopPosition());
}




TEST(CapturedScreenTest, testCapture10) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_10);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(73, line.getLineTopRowIndex());
  ASSERT_EQ(30, line.getLineTopPosition());
}




TEST(CapturedScreenTest, testCapture11) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_11);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(18, line.getLineTopPosition());
}





TEST(CapturedScreenTest, testCapture12) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_12);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(16, line.getLineTopPosition());
}





TEST(CapturedScreenTest, testCapture13) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_13);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(21, line.getLineTopPosition());
}







TEST(CapturedScreenTest, testCapture14) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_14);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(16, line.getLineTopPosition());
}





TEST(CapturedScreenTest, testCapture15) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_15);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(4, line.getLineTopPosition());
}







TEST(CapturedScreenTest, testCapture16) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_16);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(18, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture17) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_17);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(14, line.getLineTopPosition());
}



TEST(CapturedScreenTest, testCapture18) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_18);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(22, line.getLineTopPosition());
}




TEST(CapturedScreenTest, testCapture19) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_19);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(22, line.getLineTopPosition());
}




TEST(CapturedScreenTest, testCapture20) {
  Line<120> line;
  TestScreenProcessor<120> screenProcessor(line);
  screenProcessor.process(capture_20);
  ASSERT_TRUE(line.isLineTopFound());
  ASSERT_EQ(6, line.getLineTopPosition());
}




