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

#ifndef I2C_HARDWARE_PORT
  #define I2C_HARDWARE_PORT 1
#endif

#include <Wire/HardWire.h>

#ifdef I2C_HARDWARE_FAST
  HardWire DevI2C1(I2C_HARDWARE_PORT, I2C_FAST_MODE);
#else
  HardWire DevI2C1(I2C_HARDWARE_PORT);
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

#define DevI2C1 Wire
#endif


void initializeI2C(void) {
  DevI2C1.begin();
}


byte requestI2C(int deviceAddress, int numBytes) {
  return DevI2C1.requestFrom(deviceAddress, numBytes);
}

int availableI2C(void) {
  return DevI2C1.available();
}

void sendByteI2C(int deviceAddress, byte dataValue) {

  DevI2C1.beginTransmission(deviceAddress);
  DevI2C1.write(dataValue);
  DevI2C1.endTransmission();
}

byte readByteI2C() {
    return DevI2C1.read();
}

byte readByteI2C(int deviceAddress) {

    DevI2C1.requestFrom(deviceAddress, 1);
    return DevI2C1.read();
}

int readWordI2C(int deviceAddress) {

  DevI2C1.requestFrom(deviceAddress, 2);
  return (DevI2C1.read() << 8) | DevI2C1.read();
}

int readWordI2C() {

  return (DevI2C1.read() << 8) | DevI2C1.read();
}

int readShortI2C() {

  return (signed short)readWordI2C();
}

int readShortI2C(int deviceAddress) {

 DevI2C1.requestFrom(deviceAddress, 2);
 return (signed short)readWordI2C();
}

int readReverseShortI2C() {

  return (signed short)( DevI2C1.read() | (DevI2C1.read() << 8));
}

int readWordWaitI2C(int deviceAddress) {

  DevI2C1.requestFrom(deviceAddress, 2); // request two bytes
  while(!DevI2C1.available()); // wait until data available
  unsigned char msb = DevI2C1.read();
  while(!DevI2C1.available()); // wait until data available
  unsigned char lsb = DevI2C1.read();
  return (((int)msb<<8) | ((int)lsb));
}

int readReverseWordI2C(int deviceAddress) {

  DevI2C1.requestFrom(deviceAddress, 2);
  byte lowerByte = DevI2C1.read();
  return (DevI2C1.read() << 8) | lowerByte;
}

byte readWhoI2C(int deviceAddress) {

  DevI2C1.beginTransmission(deviceAddress);
  DevI2C1.write((byte)0);
  DevI2C1.endTransmission();
  delay(100);
  DevI2C1.requestFrom(deviceAddress, 1);
  return DevI2C1.read();
}

void updateRegisterI2C(int deviceAddress, byte dataAddress, byte dataValue) {

  DevI2C1.beginTransmission(deviceAddress);
  DevI2C1.write(dataAddress);
  DevI2C1.write(dataValue);
  DevI2C1.endTransmission();
}  



#endif





