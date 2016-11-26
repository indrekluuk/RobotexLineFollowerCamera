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



