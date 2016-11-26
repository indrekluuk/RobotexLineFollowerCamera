//
// Created by indrek on 26.11.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_FRAMECAPTURE_H
#define ROBOTEXLINEFOLLOWERCAMERA_FRAMECAPTURE_H


template <int8_t totalRowCount>
class FrameCapture {

    uint16_t captureBuffer[totalRowCount];


public:

    void addRow(uint8_t rowIndex, uint8_t byteHigh, uint8_t byteLow);
    void sendCapturedFrame();

};


template <int8_t totalRowCount>
void FrameCapture<totalRowCount>::addRow(uint8_t rowIndex, uint8_t byteHigh, uint8_t byteLow) {
  captureBuffer[rowIndex] = (((uint16_t)byteHigh) << 8) | ((uint16_t)byteLow);
}


template <int8_t totalRowCount>
void FrameCapture<totalRowCount>::sendCapturedFrame() {
  Serial.println("------------------------");

  for (int8_t i=totalRowCount-1; i>=0; i--) {
    Serial.print("0b");
    for (uint16_t mask = 0x8000; mask >= 0x0001; mask>>=1) {
      Serial.print(captureBuffer[i] & mask ? "1" : "0");
    }
    Serial.print(", //");
    Serial.println(i);
  }
}



#endif //ROBOTEXLINEFOLLOWERCAMERA_FRAMECAPTURE_H
