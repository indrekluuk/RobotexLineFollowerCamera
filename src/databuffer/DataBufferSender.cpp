//
// Created by indrek on 20.09.2016.
//

#include "DataBufferSender.h"
#include <SPI.h>


extern SPIClass SPI;
static SPISettings settings;

DataBufferSender::DataBufferSender() {
  settings = SPISettings(8000000, MSBFIRST, SPI_MODE0);
  pinMode(7, OUTPUT);
  PORTD = PORTD & (~PORTD_CLOCK_ENABLE_MAP);
}



void DataBufferSender::send(uint8_t * buf, uint8_t count) {
  send(count | MESSAGE_START);
  uint8_t * bufEnd = buf + count;
  for (; buf < bufEnd; buf++) {
    send(*buf);
  }
}


void DataBufferSender::dataDelay() {
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
}












