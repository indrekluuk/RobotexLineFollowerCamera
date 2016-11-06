//
// Created by indrek on 30.04.2016.
//

#ifndef ROBOTEXLINEFOLLOWERCAMERA_GRAYSCALETABLE_H
#define ROBOTEXLINEFOLLOWERCAMERA_GRAYSCALETABLE_H


// grayscale table for inverted byte
// 00000000, 10000000, 01000000, 11000000, 00100000 ...

const uint8_t graysScaleTableHigh[] = {
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF,
    0x00,
    0x84,
    0x42,
    0xC6,
    0x21,
    0xA5,
    0x63,
    0xE7,
    0x10,
    0x94,
    0x52,
    0xD6,
    0x31,
    0xB5,
    0x73,
    0xF7,
    0x08,
    0x8C,
    0x4A,
    0xCE,
    0x29,
    0xAD,
    0x6B,
    0xEF,
    0x18,
    0x9C,
    0x5A,
    0xDE,
    0x39,
    0xBD,
    0x7B,
    0xFF
};



uint8_t graysScaleTableLow[] = {
    0x00,
    0x10,
    0x08,
    0x18,
    0x04,
    0x14,
    0x0C,
    0x1C,
    0x82,
    0x92,
    0x8A,
    0x9A,
    0x86,
    0x96,
    0x8E,
    0x9E,
    0x41,
    0x51,
    0x49,
    0x59,
    0x45,
    0x55,
    0x4D,
    0x5D,
    0xC3,
    0xD3,
    0xCB,
    0xDB,
    0xC7,
    0xD7,
    0xCF,
    0xDF,
    0x20,
    0x30,
    0x28,
    0x38,
    0x24,
    0x34,
    0x2C,
    0x3C,
    0xA2,
    0xB2,
    0xAA,
    0xBA,
    0xA6,
    0xB6,
    0xAE,
    0xBE,
    0x61,
    0x71,
    0x69,
    0x79,
    0x65,
    0x75,
    0x6D,
    0x7D,
    0xE3,
    0xF3,
    0xEB,
    0xFB,
    0xE7,
    0xF7,
    0xEF,
    0xFF,
    0x00,
    0x10,
    0x08,
    0x18,
    0x04,
    0x14,
    0x0C,
    0x1C,
    0x82,
    0x92,
    0x8A,
    0x9A,
    0x86,
    0x96,
    0x8E,
    0x9E,
    0x41,
    0x51,
    0x49,
    0x59,
    0x45,
    0x55,
    0x4D,
    0x5D,
    0xC3,
    0xD3,
    0xCB,
    0xDB,
    0xC7,
    0xD7,
    0xCF,
    0xDF,
    0x20,
    0x30,
    0x28,
    0x38,
    0x24,
    0x34,
    0x2C,
    0x3C,
    0xA2,
    0xB2,
    0xAA,
    0xBA,
    0xA6,
    0xB6,
    0xAE,
    0xBE,
    0x61,
    0x71,
    0x69,
    0x79,
    0x65,
    0x75,
    0x6D,
    0x7D,
    0xE3,
    0xF3,
    0xEB,
    0xFB,
    0xE7,
    0xF7,
    0xEF,
    0xFF,
    0x00,
    0x10,
    0x08,
    0x18,
    0x04,
    0x14,
    0x0C,
    0x1C,
    0x82,
    0x92,
    0x8A,
    0x9A,
    0x86,
    0x96,
    0x8E,
    0x9E,
    0x41,
    0x51,
    0x49,
    0x59,
    0x45,
    0x55,
    0x4D,
    0x5D,
    0xC3,
    0xD3,
    0xCB,
    0xDB,
    0xC7,
    0xD7,
    0xCF,
    0xDF,
    0x20,
    0x30,
    0x28,
    0x38,
    0x24,
    0x34,
    0x2C,
    0x3C,
    0xA2,
    0xB2,
    0xAA,
    0xBA,
    0xA6,
    0xB6,
    0xAE,
    0xBE,
    0x61,
    0x71,
    0x69,
    0x79,
    0x65,
    0x75,
    0x6D,
    0x7D,
    0xE3,
    0xF3,
    0xEB,
    0xFB,
    0xE7,
    0xF7,
    0xEF,
    0xFF,
    0x00,
    0x10,
    0x08,
    0x18,
    0x04,
    0x14,
    0x0C,
    0x1C,
    0x82,
    0x92,
    0x8A,
    0x9A,
    0x86,
    0x96,
    0x8E,
    0x9E,
    0x41,
    0x51,
    0x49,
    0x59,
    0x45,
    0x55,
    0x4D,
    0x5D,
    0xC3,
    0xD3,
    0xCB,
    0xDB,
    0xC7,
    0xD7,
    0xCF,
    0xDF,
    0x20,
    0x30,
    0x28,
    0x38,
    0x24,
    0x34,
    0x2C,
    0x3C,
    0xA2,
    0xB2,
    0xAA,
    0xBA,
    0xA6,
    0xB6,
    0xAE,
    0xBE,
    0x61,
    0x71,
    0x69,
    0x79,
    0x65,
    0x75,
    0x6D,
    0x7D,
    0xE3,
    0xF3,
    0xEB,
    0xFB,
    0xE7,
    0xF7,
    0xEF,
    0xFF,
};



#endif //ROBOTEXLINEFOLLOWERCAMERA_GRAYSCALETABLE_H
