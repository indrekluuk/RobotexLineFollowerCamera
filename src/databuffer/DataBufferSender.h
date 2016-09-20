//
// Created by indrek on 20.09.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H
#define ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H


#include <arduino.h>


class DataBufferSender {

private:
    // D (digital pins 0 to 7)
    static const uint8_t PORTD_CLOCK_ENABLE_MAP = 0b10000000;

public:
    DataBufferSender();

    void newFrame();
    inline void send(uint8_t data) __attribute__((always_inline));



private:
    bool isNewFrame = false;

    void dataDelay();

};



void DataBufferSender::send(uint8_t data) {
    //SPI.transfer(data);
    SPDR = data;
    dataDelay();
    isNewFrame = false;
    PORTD = PORTD | PORTD_CLOCK_ENABLE_MAP;
    PORTD = PORTD & (~PORTD_CLOCK_ENABLE_MAP);
}







#endif //ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H
