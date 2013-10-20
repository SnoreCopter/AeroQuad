/*
  AeroQuad v3.0.1 - February 2012
  www.AeroQuad.com
  Copyright (c) 2012 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.
 
  This program is free software: you can redistribute it and/or modify 
  it under the terms of the GNU General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or 
  (at your option) any later version. 

  This program is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  GNU General Public License for more details. 

  You should have received a copy of the GNU General Public License 
  along with this program. If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef _AEROQUAD_DEVICE_I2C_H_
#define _AEROQUAD_DEVICE_I2C_H_

#if defined(I2C_HARDWARE_FAST) || defined(I2C_HARDWARE)

#error "Hardware I2C not working"

#ifndef I2C_HARDWARE_PORT
  #define I2C_HARDWARE_PORT 1
#endif

#include <Wire/HardWire.h>

#ifdef I2C_HARDWARE_FAST
  HardWire Wire(I2C_HARDWARE_PORT, I2C_FAST_MODE);
#else
  HardWire Wire(I2C_HARDWARE_PORT);
#endif


#else

// I2C functions
#include "Arduino.h"
#include <Wire.h>
/*
void sendByteI2C(int deviceAddress, byte dataValue);
byte readByteI2C();
byte readByteI2C(int deviceAddress);
int readWordI2C(int deviceAddress);
int readWordI2C();
int readShortI2C(int deviceAddress);
int readShortI2C();
int readReverseShortI2C();
int readWordWaitI2C(int deviceAddress);
int readReverseWordI2C(int deviceAddress);
byte readWhoI2C(int deviceAddress);
void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue);
*/

#endif

void initializeI2C(void) {
  Wire.begin();
}

byte requestI2C(int deviceAddress, int numBytes) {
  return Wire.requestFrom(deviceAddress, numBytes);
}

int availableI2C(void) {
  return Wire.available();
}

void sendByteI2C(int deviceAddress, byte dataValue) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(dataValue);
  Wire.endTransmission();
}

byte readByteI2C() {
  return Wire.read();
}

byte readByteI2C(int deviceAddress) {
  Wire.requestFrom(deviceAddress, 1);
  return Wire.read();
}

int readWordI2C(int deviceAddress) {
  Wire.requestFrom(deviceAddress, 2);
  return (Wire.read() << 8) | Wire.read();
}

int readWordI2C() {
  return (Wire.read() << 8) | Wire.read();
}

int readShortI2C() {
  return (signed short)readWordI2C();
}

int readShortI2C(int deviceAddress) {
 Wire.requestFrom(deviceAddress, 2);
 return (signed short)readWordI2C();
}

int readReverseShortI2C() {

  return (signed short)( Wire.read() | (Wire.read() << 8));
}

int readWordWaitI2C(int deviceAddress) {
  Wire.requestFrom(deviceAddress, 2); // request two bytes
  while(!Wire.available()); // wait until data available
  unsigned char msb = Wire.read();
  while(!Wire.available()); // wait until data available
  unsigned char lsb = Wire.read();
  return (((int)msb<<8) | ((int)lsb));
}

int readReverseWordI2C(int deviceAddress) {
  Wire.requestFrom(deviceAddress, 2);
  byte lowerByte = Wire.read();
  return (Wire.read() << 8) | lowerByte;
}

byte readWhoI2C(int deviceAddress) {
  Wire.beginTransmission(deviceAddress);
  Wire.write((byte)0);
  Wire.endTransmission();
  delay(100);
  Wire.requestFrom(deviceAddress, 1);
  return Wire.read();
}

void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue) {
  Wire.beginTransmission(deviceAddress);
  Wire.write(dataAddress);
  Wire.write(dataValue);
  Wire.endTransmission();
}  



#endif





