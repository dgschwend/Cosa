/**
 * @file Cosa/VWI/Codec/HammingCodec_8_4.cpp
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2015, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * This file is part of the Arduino Che Cosa project.
 */

#include "Cosa/Wireless/Driver/VWI/Codec/HammingCodec_8_4.hh"

// Encoding table; 4-bit code to 8-bit symbol
const uint8_t HammingCodec_8_4::symbols[16] __PROGMEM = {
  0x0f, 0x18, 0x24, 0x33, 0x42, 0x55, 0x69, 0x7e,
  0x81, 0x96, 0xaa, 0xbd, 0xcc, 0xdb, 0xe7, 0xf0
};

// Decoding table; 8-bit symbol to 4-bit code (packed table)
const uint8_t HammingCodec_8_4::codes[128] __PROGMEM = {
  0x08, 0x40, 0x20, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x11, 0x13, 0x15, 0x91, 0x11, 0x11, 0x11, 0x10,
  0x22, 0x23, 0x22, 0x22, 0x26, 0xa2, 0x22, 0x20,
  0x33, 0x33, 0x23, 0x33, 0x13, 0x33, 0x3b, 0x73,
  0x44, 0x44, 0x45, 0x44, 0x46, 0x44, 0xc4, 0x40,
  0x55, 0x45, 0x55, 0x55, 0x15, 0x5d, 0x55, 0x75,
  0x66, 0x46, 0x26, 0x6e, 0x66, 0x66, 0x66, 0x76,
  0xf7, 0x73, 0x75, 0x77, 0x76, 0x77, 0x77, 0x77,
  0x88, 0x88, 0x88, 0x98, 0x88, 0xa8, 0xc8, 0x80,
  0x98, 0x99, 0x99, 0x99, 0x19, 0x9d, 0x9b, 0x99,
  0xa8, 0xaa, 0x2a, 0xae, 0xaa, 0xaa, 0xab, 0xaa,
  0xfb, 0xb3, 0xbb, 0x9b, 0xbb, 0xab, 0xbb, 0xbb,
  0xc8, 0x4c, 0xcc, 0xce, 0xcc, 0xcd, 0xcc, 0xcc,
  0xfd, 0xdd, 0xd5, 0x9d, 0xdd, 0xdd, 0xcd, 0xdd,
  0xfe, 0xee, 0xee, 0xee, 0xe6, 0xae, 0xce, 0xee,
  0xff, 0xff, 0xff, 0xfe, 0xff, 0xfd, 0xfb, 0x7f
};

const uint8_t HammingCodec_8_4::preamble[8] __PROGMEM = {
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5a
};
