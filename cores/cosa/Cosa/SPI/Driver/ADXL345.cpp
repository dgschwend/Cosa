/**
 * @file Cosa/SPI/Driver/ADXL345.cpp
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2012-2013, Mikael Patel
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
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 *
 * This file is part of the Arduino Che Cosa project.
 */

#include "Cosa/SPI/Driver/ADXL345.hh"

ADXL345::ADXL345(Board::DigitalPin ss) :
  m_ss(ss, 1) 
{
  if (begin()) {
    write(DATA_FORMAT, _BV(FULL_RES) | RANGE_16G);
    write(POWER_CTL, _BV(MEASURE));
  }
}

void 
ADXL345::write(Register reg, uint8_t value)
{
  asserted(m_ss) {
    spi.write(WRITE_CMD | (reg & REG_MASK), value);
  }
}

void 
ADXL345::write(Register reg, void* buffer, uint8_t count)
{
  asserted(m_ss) {
    spi.write(WRITE_CMD | MULTIPLE_BYTE | (reg & REG_MASK), buffer, count);
  }
}

uint8_t 
ADXL345::read(Register reg)
{
  uint8_t res;
  asserted(m_ss) {
    res = spi.read(READ_CMD | (reg & REG_MASK));
  }
  return (res);
}

void 
ADXL345::read(Register reg, void* buffer, uint8_t count)
{
  asserted(m_ss) {
    spi.read(READ_CMD | MULTIPLE_BYTE | (reg & REG_MASK), buffer, count);
  }
}

void 
ADXL345::calibrate(int8_t x, int8_t y, int8_t z)
{
  offset_t ofs; 
  ofs.x = x;
  ofs.y = y;
  ofs.z = z;
  write(OFS, &ofs, sizeof(ofs));
}

void 
ADXL345::sample(sample_t& s)
{
  read(DATA, &s, sizeof(s));
}

void
ADXL345::calibrate()
{
  sample_t value;
  calibrate(0, 0, 0);
  sample(value);
  calibrate(-value.x/4, -value.y/4, -value.z/4);
}