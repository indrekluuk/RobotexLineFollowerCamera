//
// Created by indrek on 26.11.2016.
//


#include "line/LineEdge.h"
#include "gtest/gtest.h"



TEST(LineEdgeTest, testLineStartsOnScreenEdge) {
  LineEdge lineEdge;

  lineEdge.init(0, 0);
  lineEdge.update(60, 0);
  lineEdge.update(61, 0);
  lineEdge.update(62, 0);
  lineEdge.update(63, 0);
  lineEdge.update(64, 0);
  lineEdge.update(65, 0);
  lineEdge.update(66, 0);
  lineEdge.update(67, 0);
  lineEdge.update(68, 1);
  lineEdge.update(69, 1);
  lineEdge.update(70, 1);
  lineEdge.update(71, 2);
  ASSERT_FALSE(lineEdge.stepLengthInvalid);
}




TEST(LineEdgeTest, testOnScreenEdgeDoesNotCountAsFirstStep) {
  LineEdge lineEdge;

  lineEdge.init(0, 0);
  lineEdge.update(60, 0);
  lineEdge.update(61, 0);
  lineEdge.update(62, 0);
  lineEdge.update(63, 0);
  lineEdge.update(64, 1);
  ASSERT_EQ(-1, lineEdge.firstStepCount);
  ASSERT_EQ(-1, lineEdge.validStepCount);
  lineEdge.update(65, 2);
  lineEdge.update(66, 2);
  lineEdge.update(67, 2);
  ASSERT_EQ(1, lineEdge.firstStepCount);
  ASSERT_EQ(-1, lineEdge.validStepCount);
  lineEdge.update(68, 3);
  ASSERT_EQ(1, lineEdge.firstStepCount);
  ASSERT_EQ(3, lineEdge.validStepCount);
}





TEST(LineEdgeTest, testLastStepExceedsLimit) {
  LineEdge lineEdge;

  lineEdge.init(1, 1);
  lineEdge.update(60, 1);
  lineEdge.update(61, 1);
  lineEdge.update(62, 1);
  lineEdge.update(63, 2);
  lineEdge.update(64, 2);
  lineEdge.update(65, 2);
  lineEdge.update(66, 2);
  lineEdge.update(67, 3);
  lineEdge.update(68, 3);
  lineEdge.update(69, 3);
  lineEdge.update(70, 3);
  ASSERT_FALSE(lineEdge.stepLengthInvalid);
  lineEdge.update(71, 3);
  lineEdge.update(72, 3);
  lineEdge.update(73, 3);
  lineEdge.update(74, 3);
  lineEdge.update(75, 3);
  lineEdge.update(76, 3);
  lineEdge.update(77, 3);
  lineEdge.update(78, 3);
  lineEdge.update(79, 3);
  lineEdge.update(80, 3);
  lineEdge.update(81, 3);
  ASSERT_TRUE(lineEdge.stepLengthInvalid);
}


