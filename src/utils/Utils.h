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



inline void serialPrintCharacter(uint8_t chr) {
  UDR0 = chr;
  while(!( UCSR0A & (1<<UDRE0))); //wait for byte to transmit
}

inline void serialPrintHex(uint32_t n) {
  for (int i=7; i>=0; i--) {
    uint8_t nibble = (n >> (i*4)) & 0xF;
    serialPrintCharacter(nibble < 10 ? '0' + nibble : 'A' + nibble - 10);
  }
}

inline void serialPrintLnHex(uint32_t n) {
  serialPrintHex(n);
  serialPrintCharacter('\n');
}


inline void serialPrintInteger(uint32_t n) {
  if (n == 0) {
    serialPrintCharacter('0');
  } else {
    uint8_t digits[10];
    uint8_t digitCount = 0;
    while (n > 0) {
      digits[digitCount] = n % 10;
      n = n / 10;
      digitCount++;
    }
    for (int8_t i=digitCount-1; i>=0; i--) {
      serialPrintCharacter('0' + digits[i]);
    }
  }
}


#endif //ROBOTEXLINEFOLLOWERCAMERA_UTILS_H
