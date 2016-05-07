//
// Created by Indrek Luuk on 07.05.16.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_UTILS_H
#define ROBOTEXLINEFOLLOWERCAMERA_UTILS_H

#include <arduino.h>


inline void sleep(uint64_t milliseconds) {
  for (uint64_t d = 0; d<196*milliseconds; d++) {
    asm volatile("nop");
  }
}


inline void serialPrintHex(uint32_t n) {
  for (int i=7; i>=0; i--) {
    uint8_t nibble = (n >> (i*4)) & 0xF;
    UDR0 = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
    while(!( UCSR0A & (1<<UDRE0))); //wait for byte to transmit
  }
  UDR0 = '\n';
  while(!( UCSR0A & (1<<UDRE0))); //wait for byte to transmit
}



#endif //ROBOTEXLINEFOLLOWERCAMERA_UTILS_H
