//
// Created by indrek on 30.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENT_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENT_H


#include "Arduino.h"


class LineSegment {
    int8_t start;
    int8_t end;
    int8_t center;
    int8_t linePosition;
    bool  touchesSeekSegment;

public:
    static const int8_t rowRange = 30;
    static const int8_t rowRangeMidPoint = rowRange >> 1;
    static const int8_t lineNotFound = -1;

    LineSegment();
    LineSegment(int8_t start, int8_t end);
    LineSegment(int8_t start, int8_t end, LineSegment * seekSegment);



    inline int8_t getStart() __attribute__((always_inline));
    inline int8_t getEnd() __attribute__((always_inline));
    inline int8_t getCenter() __attribute__((always_inline));
    inline bool isLineNotFound() __attribute__((always_inline));
    inline int8_t getLinePosition() __attribute__((always_inline));
    inline bool isTouchingSeekSegment() __attribute__((always_inline));
    inline bool touchesSegment(LineSegment & otherSegment) __attribute__((always_inline));
    inline bool touchesSegment(int8_t start, int8_t end) __attribute__((always_inline));


    inline static bool isOnEdge(int8_t position) __attribute__((always_inline));

private:

    inline int8_t calculateLinePosition(LineSegment * seekSegment) __attribute__((always_inline));


};



int8_t LineSegment::getStart() {
  return start;
}



int8_t LineSegment::getEnd() {
  return end;
}



int8_t LineSegment::getCenter() {
  return center;
}


bool LineSegment::isLineNotFound() {
  return linePosition == lineNotFound;
}


int8_t LineSegment::getLinePosition() {
  return linePosition;
}


bool LineSegment::isTouchingSeekSegment() {
  return touchesSeekSegment;
}


bool LineSegment::touchesSegment(LineSegment & otherSegment) {
  return touchesSegment(otherSegment.start, otherSegment.end );
}


bool LineSegment::touchesSegment(int8_t otherStart, int8_t otherEnd) {
  return ((end - otherStart >= -2) && (otherEnd - start >= -2));
}




int8_t LineSegment::calculateLinePosition(LineSegment * seekSegment) {
  if (start > 0 && end < rowRange) {
    return center;
  } else if (start == 0 && end == rowRange) {
    if (seekSegment == nullptr) {
      return rowRangeMidPoint;
    } else {
      return (seekSegment->getCenter()) > rowRangeMidPoint ? end : start;
    }
  } else {
    if (start == 0) {
      return start;
    } else {
      return end;
    }
  }
}





bool LineSegment::isOnEdge(int8_t position) {
  return position == 0 || position == rowRange;
}




#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENT_H
