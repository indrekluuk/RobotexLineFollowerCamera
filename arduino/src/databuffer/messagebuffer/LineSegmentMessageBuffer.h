//
// Created by indrek on 29.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H

struct LineSegmentMessageBuffer {
    uint8_t lineBottomIndex;
    uint8_t lineBottomPosition : 5;
    uint8_t reserved1 : 1;
    uint8_t isEndOfLine : 1;
    uint8_t unusable1 : 1;
    uint8_t lineTopIndex;
    uint8_t lineTopPosition : 5;
    uint8_t reserved2 : 2;
    uint8_t unusable2 : 1;
};


#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H


