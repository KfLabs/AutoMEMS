/* ============================================================================
BNO055 I2C device API
Based on BNO055 Bosch Data Sheet rev 1.0, July 2014 (BST-BNO055-DS000-10)
by: sheen yari
date: 9-14-2014

This software is intended for use by the Laboratory of Neurophysics at the 
University of California - San Diego. 

NOTE: THIS IS ONLY A PARTIAL RELEASE. THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE
DEVELOPMENT AND IS STILL MISSING IMPORTANT FEATURES. THIS CODE IS CURRENTLY ONLY TO 
SUPPORT SIMPLE PROTOTYPING OF THE BOSCH BNO055 FUSIONLIB LIBRARY
===============================================================================
*/


/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
//C:\Users\Cheyenne\Documents\Arduino\libraries\BNO055\BNO055.cpp
#include "BNO055.h"

/** Default constructor, uses default I2C address.
 * @see BNO055_DEFAULT_ADDRESS
 */
BNO055::BNO055() {
	devAddr = BNO055_DEFAULT_ADDRESS;
}

/** Specific address constructor.
 * @param address I2C address
 * @see BNO055_DEFAULT_ADDRESS
 * @see BNO055_ADDRESS_COM3_LOW
 * @see BNO055_ADDRESS_COM3_HIGH
 * @see BNO055_ADDRESS_I2C_HID
 */
BNO055::BNO055(uint8_t address) {
	devAddr = address;
}

uint8_t BNO055::getSelfTest() {
	I2Cdev::readBits(devAddr, ST_RESULT, SELF_TEST_BIT, SELF_TEST_LENGTH, buffer);
	return buffer[0];
}

bool BNO055::verifySelfTest() {
	I2Cdev::readBits(devAddr, ST_RESULT, SELF_TEST_BIT, SELF_TEST_LENGTH, buffer);
	return buffer[0] == 0x0F;
}

uint8_t BNO055::getAccelRange() {
	I2Cdev::writeByte(devAddr, PAGE_ID, GOTO_PAGE_1);
	I2Cdev::readBits(devAddr, ACC_CONFIG, ACC_RANGE_SEL_BIT, ACC_RANGE_SEL_LENGTH, buffer);
	I2Cdev::writeByte(devAddr, PAGE_ID, GOTO_PAGE_0);
	return buffer[0];
}
	
void BNO055::setAccelRange(uint8_t range) {
	I2Cdev::writeByte(devAddr, PAGE_ID, GOTO_PAGE_1);
	I2Cdev::writeBits(devAddr, ACC_CONFIG, ACC_RANGE_SEL_BIT, ACC_RANGE_SEL_LENGTH, range);
	I2Cdev::writeByte(devAddr, PAGE_ID, GOTO_PAGE_0);
}

uint8_t BNO055::getOperatingMode() {
	I2Cdev::readBits(devAddr, OPR_MODE, OPR_MODE_SEL_BIT, OPR_MODE_SEL_LENGTH, buffer);
	return buffer[0];
}

void BNO055::setOperatingMode(uint8_t mode) {
	I2Cdev::writeBits(devAddr, OPR_MODE, OPR_MODE_SEL_BIT, OPR_MODE_SEL_LENGTH, mode);
}

int8_t BNO055::getTemperature() {
	I2Cdev::readByte(devAddr, TEMP, buffer);
	return buffer[0];
}

void BNO055::getAcceleration(int16_t *x, int16_t *y, int16_t *z) {
		I2Cdev::readBytes(devAddr, ACC_DATA_X_LSB, 6, buffer);
		*x = (((int16_t)buffer[1]) << 8) | buffer[0];
		*y = (((int16_t)buffer[3]) << 8) | buffer[2];
		*z = (((int16_t)buffer[5]) << 8) | buffer[4];
}
	
int16_t BNO055::getAccelerationX() {
	I2Cdev::readBytes(devAddr, ACC_DATA_X_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getAccelerationY() {
	I2Cdev::readBytes(devAddr, ACC_DATA_Y_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getAccelerationZ() {
	I2Cdev::readBytes(devAddr, ACC_DATA_Z_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

void BNO055::getRotation(int16_t *x, int16_t *y, int16_t *z) {
	I2Cdev::readBytes(devAddr, GYR_DATA_X_LSB, 6, buffer);
	*x = (((int16_t) buffer[1]) << 8) | buffer[0];
	*y = (((int16_t) buffer[3]) << 8) | buffer[2];
	*z = (((int16_t) buffer[5]) << 8) | buffer[4];
}


int16_t BNO055::getRotationX() {
	I2Cdev::readBytes(devAddr, GYR_DATA_X_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getRotationY() {
	I2Cdev::readBytes(devAddr, GYR_DATA_Y_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getRotationZ() {
	I2Cdev::readBytes(devAddr, GYR_DATA_Z_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

void BNO055::getMag(int16_t *x, int16_t *y, int16_t *z) {
	I2Cdev::readBytes(devAddr, MAG_DATA_X_LSB, 6, buffer);
	*x = (((int16_t) buffer[1]) << 8) | buffer[0];
	*y = (((int16_t) buffer[3]) << 8) | buffer[2];
	*z = (((int16_t) buffer[5]) << 8) | buffer[4];
}


int16_t BNO055::getMagX() {
	I2Cdev::readBytes(devAddr, MAG_DATA_X_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getMagY() {
	I2Cdev::readBytes(devAddr, MAG_DATA_Y_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

int16_t BNO055::getMagZ() {
	I2Cdev::readBytes(devAddr, MAG_DATA_Z_LSB, 2, buffer);
	return (((int16_t)buffer[1]) << 8) | buffer[0];
}

void BNO055::get9AxisData(int16_t *ax, int16_t *ay, int16_t *az, int16_t *mx, int16_t *my, int16_t *mz, int16_t *gx, int16_t *gy, int16_t *gz) {
	I2Cdev::readBytes(devAddr, ACC_DATA_X_LSB, 18, buffer);
	*ax = (((int16_t)buffer[1]) << 8) | buffer[0];
    *ay = (((int16_t)buffer[3]) << 8) | buffer[2];
    *az = (((int16_t)buffer[5]) << 8) | buffer[4];
    *mx = (((int16_t)buffer[7]) << 8) | buffer[6];
    *my = (((int16_t)buffer[9]) << 8) | buffer[8];
    *mz = (((int16_t)buffer[11]) << 8) | buffer[10];
	*gx = (((int16_t)buffer[13]) << 8) | buffer[12];
    *gy = (((int16_t)buffer[15]) << 8) | buffer[14];
    *gz = (((int16_t)buffer[17]) << 8) | buffer[16];
}

// FUSED EULER_*OUT_* Data
void BNO055::getEulerAngles(int16_t *h, int16_t *r, int16_t *p)
{
    I2Cdev::readBytes(devAddr, EUL_HEADING_LSB, 6, buffer);
	*h = (((int16_t)buffer[1]) << 8) | buffer[0];
	*r = (((int16_t)buffer[3]) << 8) | buffer[2];
	*p = (((int16_t)buffer[5]) << 8) | buffer[4];
}
		
// FUSED QUATERNION_*OUT_* Data
void BNO055::getQuaternions(int16_t *w, int16_t *x, int16_t *y, int16_t *z)
{
    I2Cdev::readBytes(devAddr, QUA_DATA_W_LSB, 8, buffer);
	*w = (((int16_t)buffer[1]) << 8) | buffer[0];
	*x = (((int16_t)buffer[3]) << 8) | buffer[2];
	*y = (((int16_t)buffer[5]) << 8) | buffer[4];
	*z = (((int16_t)buffer[7]) << 8) | buffer[6];
}

// FUSED LINEAR_ACCELERATION_*OUT_* Data
void BNO055::getLinearAcceleration(int16_t *x, int16_t *y, int16_t *z)
{
    I2Cdev::readBytes(devAddr, LIA_DATA_X_LSB, 6, buffer);
	*x = (((int16_t)buffer[1]) << 8) | buffer[0];
	*y = (((int16_t)buffer[3]) << 8) | buffer[2];
	*z = (((int16_t)buffer[5]) << 8) | buffer[4];
}
		
// FUSED GRAVITY_*OUT_* Data
void BNO055::getGravity(int16_t *x, int16_t *y, int16_t *z)
{
    I2Cdev::readBytes(devAddr, LIA_DATA_X_LSB, 6, buffer);
	*x = (((int16_t)buffer[1]) << 8) | buffer[0];
	*y = (((int16_t)buffer[3]) << 8) | buffer[2];
	*z = (((int16_t)buffer[5]) << 8) | buffer[4];
}











