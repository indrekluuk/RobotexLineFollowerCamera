//
// Created by indrek on 29.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H
#define ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H

struct LineSegmentMessageBuffer {
    uint8_t lineBottomIndex;
    uint8_t lineBottomPosition : 5;
    uint8_t isEndOfLine : 1;
    uint8_t isSharpTurn : 1;
    uint8_t sharpTurnDirection : 1;
    uint8_t lineTopIndex;
    uint8_t lineTopPosition;
};


#endif //ROBOTEXLINEFOLLOWERCAMERA_LINESEGMENTMESSAGE_H


