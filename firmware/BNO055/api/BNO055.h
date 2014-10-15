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

#ifndef _BNO055_H_
#define _BNO055_H_

#include "I2Cdev.h"
#include <avr/pgmspace.h>


// The register map is separated into two logical pages, Page 1 contains
// sensor-specific data and Page 0 contains all other configuration
// parameters and output data.

// At power on Page 0 is selected, the PAGE_ID register can be used to 
// identify the current selected page and change between page 0 and page 1.

//C:\Users\Cheyenne\Documents\Arduino\libraries\BNO055\BNO055.h

// PAGE 0
//BNO055 Slave Addresses
#define BNO055_DEFAULT_ADDRESS    0x28 
#define BNO055_ADDRESS_COM3_HIGH  0x29
#define BNO055_ADDRESS_COM3_LOW   0x28
#define BNO055_ADDRESS_I2C_HID    0x40

// BNO055 Registers
#define MAG_RADIUS_MSB 0x6A // R/W
#define MAG_RADIUS_LSB 0x69 // R/W
#define ACC_RADIUS_MSB 0x68 // R/W
#define ACC_RADIUS_LSB 0x67 // R/W

#define GYR_OFFSET_Z_MSB 0x66 // R/W
#define GYR_OFFSET_Z_LSB 0x65 // R/W
#define GYR_OFFSET_Y_MSB 0x64 // R/W
#define GYR_OFFSET_Y_LSB 0x63 // R/W 
#define GYR_OFFSET_X_MSB 0x62 // R/W
#define GYR_OFFSET_X_LSB 0x61 // R/W

#define MAG_OFFSET_Z_MSB 0x60 // R/W
#define MAG_OFFSET_Z_LSB 0x5F // R/W
#define MAG_OFFSET_Y_MSB 0x5E // R/W
#define MAG_OFFSET_Y_LSB 0x5D // R/W
#define MAG_OFFSET_X_MSB 0x5C // R/W
#define MAG_OFFSET_X_LSB 0x5B // R/W

#define ACC_OFFSET_Z_MSB 0x5A // R/W
#define ACC_OFFSET_Z_LSB 0x59 // R/W
#define ACC_OFFSET_Y_MSB 0x58 // R/W
#define ACC_OFFSET_Y_LSB 0x57 // R/W
#define ACC_OFFSET_X_MSB 0x56 // R/W
#define ACC_OFFSET_X_LSB 0x55 // R/W

// Registers 43-54 reserved for Soft Iron Calibration Matrix

#define AXIS_MAP_SIGN   0x42 // Bits0-2: R/W; Bits3-7: reserved 
#define AXIS_MAP_CONFIG 0x41 // Bits0-5: R/W; Bits6-7: reserved
#define TEMP_SOURCE     0x40 // Bits0-1: R/W; Bits2-7: reserved

#define SYS_TRIGGER 0x3F
#define PWR_MODE    0x3E
#define OPR_MODE    0x3D

// Register 3C Reserved

#define UNIT_SEL       0x3B //RO
#define SYS_ERR        0x3A //RO
#define SYS_STATUS     0x39 //RO 
#define SYS_CLK_STATUS 0x38 //RO
#define INT_STATUS     0x37	//RO
#define ST_RESULT      0x36 //RO
#define CALIB_STAT     0x35 //RO
#define TEMP           0x34 //RO

#define GRV_DATA_Z_MSB 0x33 //RO
#define GRV_DATA_Z_LSB 0x32 //RO
#define GRV_DATA_Y_MSB 0x31 //RO
#define GRV_DATA_Y_LSB 0x30 //RO
#define GRV_DATA_X_MSB 0x2F //RO
#define GRV_DATA_X_LSB 0x2E //RO

#define LIA_DATA_Z_MSB 0x2D //RO
#define LIA_DATA_Z_LSB 0x2C //RO
#define LIA_DATA_Y_MSB 0x2B //RO
#define LIA_DATA_Y_LSB 0x2A //RO
#define LIA_DATA_X_MSB 0x29 //RO
#define LIA_DATA_X_LSB 0x28 //RO

#define QUA_DATA_Z_MSB 0x27 //RO
#define QUA_DATA_Z_LSB 0x26 //RO
#define QUA_DATA_Y_MSB 0x25 //RO
#define QUA_DATA_Y_LSB 0x24 //RO
#define QUA_DATA_X_MSB 0x23 //RO
#define QUA_DATA_X_LSB 0x22 //RO
#define QUA_DATA_W_MSB 0x21 //RO
#define QUA_DATA_W_LSB 0x20 //RO

#define EUL_PITCH_MSB   0x1F //RO
#define EUL_PITCH_LSB   0x1E //RO
#define EUL_ROLL_MSB    0x1D //RO
#define EUL_ROLL_LSB    0x1C //RO
#define EUL_HEADING_MSB 0x1B //RO
#define EUL_HEADING_LSB 0x1A //RO

#define GYR_DATA_Z_MSB 0x19 //RO
#define GYR_DATA_Z_LSB 0x18 //RO
#define GYR_DATA_Y_MSB 0x17 //RO
#define GYR_DATA_Y_LSB 0x16 //RO
#define GYR_DATA_X_MSB 0x15 //RO
#define GYR_DATA_X_LSB 0x14 //RO

#define MAG_DATA_Z_MSB 0x13 //RO
#define MAG_DATA_Z_LSB 0x12 //RO
#define MAG_DATA_Y_MSB 0x11 //RO
#define MAG_DATA_Y_LSB 0x10 //RO
#define MAG_DATA_X_MSB 0x0F //RO
#define MAG_DATA_X_LSB 0x0E //RO

#define ACC_DATA_Z_MSB 0x0D //RO
#define ACC_DATA_Z_LSB 0x0C //RO
#define ACC_DATA_Y_MSB 0x0B //RO
#define ACC_DATA_Y_LSB 0x0A //RO
#define ACC_DATA_X_MSB 0x09 //RO
#define ACC_DATA_X_LSB 0x08 //RO

#define PAGE_ID       0x07 //RO
#define BL_REV_ID     0x06 //RO
#define SW_REV_ID_MSB 0x05 //RO
#define SW_REV_ID_LSB 0x04 //RO

#define GYR_ID  0x03 // RO; Default = 0x0F
#define MAG_ID  0x02 // RO; Default = 0x32
#define ACC_ID  0x01 // RO; Default = 0xFB
#define CHIP_ID 0x00 // RO; Default 0xA0

#define PWR_MODE_SEL_BIT    0
#define PWR_MODE_SEL_LENGTH 2

#define PWR_MODE_NORMAL  0x00
#define PWR_MODE_LOW	 0x01
#define PWR_MODE_SUSPEND 0x02

#define OPR_MODE_SEL_BIT 0
#define OPR_MODE_SEL_LENGTH  4

// CONFIG MODE selection
#define OPR_MODE_CONFIG_MODE  0x00
// Sensor Mode selections 
#define OPR_MODE_ACCONLY 	  0x01
#define OPR_MODE_MAGONLY 	  0x02
#define OPR_MODE_GYROONLY 	  0x03
#define OPR_MODE_ACCMAG 	  0x04
#define OPR_MODE_ACCGYRO 	  0x05
#define OPR_MODE_MAGGYRO 	  0x06
#define OPR_MODE_AMG	 	  0x07
// Fusion Mode selections
#define OPR_MODE_IMU	 	  0x08
#define OPR_MODE_COMPASS 	  0x09
#define OPR_MODE_M4G	 	  0x0A
#define OPR_MODE_NDOF_FMC_OFF 0x0B
#define OPR_MODE_NDOF 		  0x0C

#define DATA_RATE_SEL_BIT    4
#define DATA_RATE_SEL_LENGTH 3

#define FASTEST_MODE 0x01
#define GAME_MODE	 0x02
#define UI_MODE		 0x03
#define NORMAL_MODE  0x04

#define X_AXIS_REMAP_BIT  0
#define Y_AXIS_REMAP_BIT  2
#define Z_AXIS_REMAP_BIT  4
#define AXIS_REMAP_LENGTH 2

#define AXIS_REP_X 0x00
#define AXIS_REP_Y 0x01
#define AXIS_REP_Z 0x02

#define AXIS_SIGN_REMAP_BIT	   0
#define AXIS_SIGN_REMAP_LENGTH 3

#define ACC_RANGE_SEL_BIT	  0
#define ACC_RANGE_SEL_LENGTH  2
#define ACC_BW_SEL_BIT        2 //Auto controlled in fusion mode
#define ACC_BW_SEL_LENGTH     3 //Auto controlled in fusion mode
#define ACC_OPMODE_SEL_BIT    5 //Auto controlled in fusion mode
#define ACC_OPMODE_SEL_LENGTH 3 //Auto controlled in fusion mode

#define ACC_RANGE_2G  0x00
#define ACC_RANGE_4G  0x01 // Default
#define ACC_RANGE_8G  0x02
#define ACC_RANGE_16G 0x03

#define GYR_RANGE_SEL_BIT	  0 //Auto controlled in fusion mode
#define GYR_RANGE_SEL_LENGTH  3 //Auto controlled in fusion mode
#define GYR_BW_SEL_BIT        3 //Auto controlled in fusion mode
#define GYR_BW_SEL_LENGTH     3 //Auto controlled in fusion mode
#define GYR_OPMODE_SEL_BIT    6 //Auto controlled in fusion mode
#define GYR_OPMODE_SEL_LENGTH 2 //Auto controlled in fusion mode

#define MAG_RANGE_SEL_BIT	  0 //Auto controlled in fusion mode
#define MAG_RANGE_SEL_LENGTH  3 //Auto controlled in fusion mode
#define MAG_BW_SEL_BIT        3 //Auto controlled in fusion mode
#define MAG_BW_SEL_LENGTH     2 //Auto controlled in fusion mode
#define MAG_OPMODE_SEL_BIT    5 //Auto controlled in fusion mode
#define MAG_OPMODE_SEL_LENGTH 2 //Auto controlled in fusion mode

#define ACC_UNIT_SEL_BIT          0
#define ANGULAR_RATE_UNIT_SEL_BIT 1
#define EULER_ANGLE_UNIT_SEL_BIT  2
#define TEMP_UNIT_SEL_BIT         4
#define UNIT_SEL_LENGTH           1

#define ACC_UNIT_M_SSQ        0
#define ACC_UNIT_MG           1
#define ANGULAR_RATE_UNIT_DPS 0
#define ANGULAR_RATE_UNIT_RPS 1
#define EULER_ANGLE_UNIT_DEG  0
#define EULER_ANGLE_UNIT_RAD  1
#define TEMP_UNIT_C           0
#define TEMP_UNIT_F           1

#define SELF_TEST_BIT    0
#define SELF_TEST_LENGTH 4

#define SYS_CLK_STATUS_BIT    0
#define SYS_CLK_STATUS_LENGTH 1

#define GOTO_PAGE_0 0x00
#define GOTO_PAGE_1 0x01

// PAGE 1 (All unreserved registers in Page 1 are READ ONLY)
// Registers 7F-60 reserved
// Registers 5F-50 are named UNIQUE_ID and are READ ONLY
// Registers 4F-20 reserved

#define GYR_AM_SET     0x1F // Default = 0x0A
#define GYR_AM_THRES   0x1E	// Default = 0x04
#define GYR_DUR_Z      0x1D	// Default = 0x19
#define GYR_HR_Z_SET   0x1C	// Default = 0x01
#define GYR_DUR_Y      0x1B	// Default = 0x19
#define GYR_HR_Y_SET   0x1A	// Default = 0x01
#define GYR_DUR_X      0x19	// Default = 0x19
#define GYR_HR_X_SET   0x18	// Default = 0x01
#define GYR_INT_SETING 0x17 // Default = 0x00

#define ACC_NM_SET       0x16 // Default = 0x0B
#define ACC_NM_THRE      0x15 // Default = 0x0A
#define ACC_HG_THRE      0x14 // Default = 0xC0
#define ACC_HG_DURATION  0x13 // Default = 0x0F
#define ACC_INT_SETTINGS 0x12 // Default = 0x03
#define ACC_AM_THRES     0x11 // Default = 0x14

#define INT_EN   0x10
#define INT_MASK 0x0F

// Register 0x0E reserved

#define GYR_SLEEP_CONFIG 0x0D 
#define ACC_SLEEP_CONFIG 0x0C
#define GYR_CONFIG_1     0x0B
#define GYR_CONFIG_0     0x0A
#define MAG_CONFIG       0x09
#define ACC_CONFIG       0x08

// PAGE_ID still mapped to 0x07
// Registers 6-0 reserved
 

// SENSOR MODE
#define ACC_ONLY 


class BNO055 {
	public: 
		BNO055();
		BNO055(uint8_t address);
		
		uint8_t getSelfTest();
		bool verifySelfTest();
		
		uint8_t getAccelRange();
		void setAccelRange(uint8_t range);
		
		uint8_t getOperatingMode();
		void setOperatingMode(uint8_t mode);
		
		// TEMP_*OUT_* registers
		int8_t getTemperature();
		
		// ACCEL_*OUT_* registers
		void getAcceleration(int16_t *x, int16_t *y, int16_t *z);
		int16_t getAccelerationX();
		int16_t getAccelerationY();
		int16_t getAccelerationZ();
		
		// GYRO_*OUT_* registers
		void getRotation(int16_t *x, int16_t *y, int16_t *z);
		int16_t getRotationX();
		int16_t getRotationY();
		int16_t getRotationZ();
		
		// MAG_*OUT_* registers
		void getMag(int16_t *x, int16_t *y, int16_t *z); 
		int16_t getMagX();
		int16_t getMagY();
		int16_t getMagZ();
		
		// 9-AXIS_*OUT_* DataSet
		void get9AxisData(int16_t *ax, int16_t *ay, int16_t *az, int16_t *mx, int16_t *my, int16_t *mz, int16_t *gx, int16_t *gy, int16_t *gz);
		
		// FUSED EULER_*OUT_* Data
		void getEulerAngles(int16_t *h, int16_t *r, int16_t *p);
		
		// FUSED QUATERNION_*OUT_* Data
		void getQuaternions(int16_t *w, int16_t *x, int16_t *y, int16_t *z);

		// FUSED LINEAR_ACCELERATION_*OUT_* Data
		void getLinearAcceleration(int16_t *x, int16_t *y, int16_t *z);
		
		// FUSED GRAVITY_*OUT_* Data
		void getGravity(int16_t *x, int16_t *y, int16_t *z);
		
		
	private:
            uint8_t devAddr;
            uint8_t buffer[18];
};
#endif

