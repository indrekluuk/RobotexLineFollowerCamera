//
// Created by indrek on 20.09.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H
#define ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H


#include <Arduino.h>


#define MESSAGE_START 0x80
#define MESSAGE_COMMAND_MASK 0x70
#define MESSAGE_COUNT_MASK 0x0F
#define MESSAGE_DATA_MASK 0x7F

class DataBufferSender {

private:
    // D (digital pins 0 to 7)
    static const uint8_t PORTD_CLOCK_ENABLE_MAP = 0b10000000;

public:
    DataBufferSender();
    void sendMessage(uint8_t commandCode, uint8_t * buf, uint8_t count);
    inline void sendByte(uint8_t byte) __attribute__((always_inline));


private:
    void dataDelay();
};



void DataBufferSender::sendByte(uint8_t byte) {
  SPDR = byte;
  dataDelay();
  PORTD = PORTD | PORTD_CLOCK_ENABLE_MAP;
  PORTD = PORTD & (~PORTD_CLOCK_ENABLE_MAP);
}







#endif //ROBOTEXLINEFOLLOWERCAMERA_DATABUFFERSENDER_H
