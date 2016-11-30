//
// Created by indrek on 30.11.2016.
//

#include "LineSegment.h"




LineSegment::LineSegment() :
    start(lineNotFound),
    end(lineNotFound),
    center(lineNotFound),
    linePosition(lineNotFound),
    touchesSeekSegment(false)
{
}


LineSegment::LineSegment(int8_t start, int8_t end) :
    start(start),
    end(end),
    center((start + end) >> 1),
    linePosition(center),
    touchesSeekSegment(false)
{
}


LineSegment::LineSegment(int8_t start, int8_t end, LineSegment * seekSegment) :
    start(start),
    end(end),
    center((start + end) >> 1)
{
  linePosition = calculateLinePosition(seekSegment);
  touchesSeekSegment = seekSegment != nullptr && touchesSegment(*seekSegment);
}






