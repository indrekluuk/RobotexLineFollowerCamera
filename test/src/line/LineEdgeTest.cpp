//
// Created by indrek on 26.11.2016.
//


#include "line/LineEdge.h"
#include "gtest/gtest.h"



TEST(LineEdgeTest, testLineStartsOnScreenEdge) {
  LineEdge lineEdge;

  lineEdge.init(0, 0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(1);
  lineEdge.update(1);
  lineEdge.update(1);
  lineEdge.update(2);
  ASSERT_FALSE(lineEdge.stepLengthInvalid);
}




TEST(LineEdgeTest, testOnScreenEdgeDoesNotCountAsFirstStep) {
  LineEdge lineEdge;

  lineEdge.init(0, 0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(0);
  lineEdge.update(1);
  ASSERT_EQ(-1, lineEdge.firstStepCount);
  ASSERT_EQ(-1, lineEdge.validStepCount);
  lineEdge.update(2);
  lineEdge.update(2);
  lineEdge.update(2);
  ASSERT_EQ(1, lineEdge.firstStepCount);
  ASSERT_EQ(-1, lineEdge.validStepCount);
  lineEdge.update(3);
  ASSERT_EQ(1, lineEdge.firstStepCount);
  ASSERT_EQ(3, lineEdge.validStepCount);
}





TEST(LineEdgeTest, testLastStepExceedsLimit) {
  LineEdge lineEdge;

  lineEdge.init(1, 1);
  lineEdge.update(1);
  lineEdge.update(1);
  lineEdge.update(1);
  lineEdge.update(2);
  lineEdge.update(2);
  lineEdge.update(2);
  lineEdge.update(2);
  lineEdge.update(3);
  lineEdge.update(3);
  lineEdge.update(3);
  lineEdge.update(3);
  ASSERT_FALSE(lineEdge.stepLengthInvalid);
  lineEdge.update(3);
  lineEdge.update(3);
  lineEdge.update(3);
  lineEdge.update(3);
  ASSERT_TRUE(lineEdge.stepLengthInvalid);
}


