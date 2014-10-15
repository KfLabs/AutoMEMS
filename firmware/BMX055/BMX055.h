/* ============================================================================
BMX055 I2C device API
Based on BNO055 Bosch Data Sheet rev 1.0, July 2014 (BST-BNO055-DS000-10)
by: sheen yari
date: 5-10-2014

This software is intended for use by the Laboratory of Neurophysics at the 
University of California - San Diego. 

 Hardware setup:
 BMX055 ------------- Teensy 2.0
    VDD ------------- 3.3V
    SDA ------------- PD1
    SCL ------------- PD0
    GND ------------- GND

NOTE: THIS IS ONLY A PARTIAL RELEASE. THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE
DEVELOPMENT AND IS STILL MISSING IMPORTANT FEATURES. THIS CODE IS CURRENTLY ONLY TO 
SUPPORT SIMPLE PROTOTYPING OF THE BOSCH BNO055 FUSIONLIB LIBRARY
===============================================================================
*/

// BMX055 data sheet http://ae-bst.resource.bosch.com/media/products/dokumente/bmx055/BST-BMX055-DS000-01v2.pdf


// Accelerometer registers
#define ACC_WHO_AM_I	  0x00	// should return 0xFA
// Register 01 Reserved
#define ACC_X_LSB         0x02
#define ACC_X_MSB         0x03
#define ACC_Y_LSB         0x04
#define ACC_Y_MSB         0x05
#define ACC_Z_LSB         0x06
#define ACC_Z_MSB         0x07
#define ACC_TEMP          0x08
#define ACC_INT_STATUS_0  0x09
#define ACC_INT_STATUS_1  0x0A
#define ACC_INT_STATUS_2  0x0B
#define ACC_INT_STATUS_3  0x0C
// Register 0D Reserved
#define ACC_FIFO_STATUS   0x0E
#define ACC_PMU_RANGE     0x0F
#define ACC_PMU_BW        0x10
#define ACC_PMU_LPW       0x11
#define ACC_PMU_LOW_POWER 0x12
#define ACC_HBW           0x13
#define ACC_BGW_SOFTRESET 0x14
// Register 15 Reserved
#define ACC_INT_EN_0      0x16
#define ACC_INT_EN_1      0x17
#define ACC_INT_EN_2      0x18
#define ACC_INT_MAP_0     0x19
#define ACC_INT_MAP_1     0x1A
#define ACC_INT_MAP_2     0x1B
// Registers 1C and 1D Reserved
#define ACC_INT_SRC       0x1E
// Register 1F Reserved
#define ACC_INT_OUT_CTRL  0x20
#define ACC_INT_RST_LATCH 0x21
#define ACC_INT_0         0x22
#define ACC_INT_1         0x23
#define ACC_INT_2         0x24
#define ACC_INT_3         0x25
#define ACC_INT_4         0x26
#define ACC_INT_5         0x27
#define ACC_INT_6         0x28
#define ACC_INT_7         0x29
#define ACC_INT_8         0x2A
#define ACC_INT_9         0x2B
#define ACC_INT_A         0x2C
#define ACC_INT_B         0x2D
#define ACC_INT_C         0x2E
#define ACC_INT_D         0x2F
#define ACC_FIFO_CONFIG_0 0x30
// Register 31 Reserved
#define ACC_PMU_SELF_TEST 0x32
#define ACC_TRIM_NVM_CTRL 0x33
#define ACC_BGW_SPI3_WDT  0x34
// Register 35 Reserved
#define ACC_OFC_CTRL      0x36
#define ACC_OFC_SETTING   0x37
#define ACC_OFC_OFFSET_X  0x38
#define ACC_OFC_OFFSET_Y  0x39
#define ACC_OFC_OFFSET_Z  0x3A
#define ACC_TRIM_GPO      0x3B
#define ACC_TRIM_GP1      0x3C
// Register 3D Reserved
#define ACC_FIFO_CONFIG_1 0x3E
#define ACC_FIFO_DATA     0x3F


// To set the accelerometer output range
// Write these values to ACC_PMU_RANGE 
#define ACC_RANGE_2G  0x03
#define ACC_RANGE_4G  0x05
#define ACC_RANGE_8G  0x08
#define ACC_RANGE_16G 0x0B

#define ACC_RANGE_SEL_BIT 0
#define ACC_RANGE_SEL_LENGTH 4

// To set the acceleration data filter bandwidth 
// Write these values to ACC_PMU_BW
#define ACC_BW_7_81HZ  0x08
#define ACC_BW_15_63HZ 0x09
#define ACC_BW_31_25HZ 0x10
#define ACC_BW_62_5HZ  0x11
#define ACC_BW_125HZ   0x12
#define ACC_BW_250HZ   0x13
#define ACC_BW_500HZ   0x13
#define ACC_BW_1000HZ  0x13

#define ACC_BW_SEL_BIT 0
#define ACC_BW_SEL_LENGTH 5

// To trigger a soft reset. All other values will be ignored
#define ACC_RESET 0xB6

#define ACC_STEST_AMP_LOW 0  // Deflection low
#define ACC_STEST_AMP_HIGH 1  // Deflection high

#define ACC_STEST_AMP_SEL_BIT    4
#define ACC_STEST_AMP_SEL_LENGTH 1

#define ACC_STEST_NEG 0
#define ACC_STEST_POS 1

#define ACC_SELF_TEST_SIGN_SEL_BIT    2
#define ACC_SELF_TEST_SIGN_SEL_LENGTH 1

#define ACC_STEST_DISABLED 0x00
#define ACC_STEST_X_AXIS 0x01
#define ACC_STEST_Y_AXIS 0x02
#defnie ACC_STEST_Z_AXIS 0x03

#define ACC_STEST_AXIS_SEL_BIT    0
#define ACC_STEST_AXIS_SEL_LENGTH 2


#define FIFO_MODE_BYPASS 0x00
#define FIFO_MODE_FIFO 0x01
#define FIFO_MODE_STREAM 0x02

#define FIFO_MODE_SEL_BIT    6
#define FIFO_MODE_SEL_LENGTH 2

#define FIFO_DATA_CONFIG_XYZ 0x00
#define FIFO_DATA_CONFIG_X 0x01
#define FIFO_DATA_CONFIG_Y 0x02
#define FIFO_DATA_CONFIG_Z 0x03

#deine FIFO_DATA_CONFIG_SEL_BIT     0
#define FIFO_DATA_CONFIG_SEL_LENGTH 2


// BMX055 Gyroscope Registers
#define GYR_WHO_AM_I         0x00  // should return 0x0F
// Register 01 Reserved
#define GYR_RATE_X_LSB       0x02
#define GYR_RATE_X_MSB       0x03
#define GYR_RATE_Y_LSB       0x04
#define GYR_RATE_Y_MSB       0x05
#define GYR_RATE_Z_LSB       0x06
#define GYR_RATE_Z_MSB       0x07
// Register 08 Reserved
#define GYR_INT_STATUS_0     0x09
#define GYR_INT_STATUS_1     0x0A
#define GYR_INT_STATUS_2     0x0B
#define GYR_INT_STATUS_3     0x0C
// Register 0D Reserved 
#define GYR_FIFO_STATUS      0x0E
#define GYR_RANGE            0x0F
#define GYR_BW               0x10
#define GYR_LPM1             0x11
#define GYR_LPM2             0x12
#define GYR_RATE_HBW         0x13
#define GYR_BGW_SOFTRESET    0x14
#define GYR_INT_EN_0         0x15
#define GYR_INT_EN_1         0x16
#define GYR_INT_MAP_0        0x17
#define GYR_INT_MAP_1        0x18
#define GYR_INT_MAP_2        0x19
#define GYR_INT_SRC_1        0x1A
#define GYR_INT_SRC_2        0x1B
#define GYR_INT_SRC_3        0x1C
// Register 1D Reserved
#define GYR_FIFO_EN       0x1E
// Registers 1F and 20 Reserved
#define GYR_INT_RST_LATCH 0x21
#define GYR_HIGH_TH_X     0x22
#define GYR_HIGH_DUR_X    0x23
#define GYR_HIGH_TH_Y     0x24
#define GYR_HIGH_DUR_Y    0x25
#define GYR_HIGH_TH_Z     0x26
#define GYR_HIGH_DUR_Z    0x27
// Registers 28-30 Reserved
#define GYR_SOC           0x31
#define GYR_A_FOC         0x32
#define GYR_TRIM_NVM_CTRL 0x33
#define GYR_BGW_SPI3_WDT  0x34
// REgister 35 Reserved
#define GYR_OFC1          0x36
#define GYR_OFC2          0x37
#define GYR_OFC3          0x38
#define GYR_OFC4          0x39
#define GYR_TRIM_GP0      0x3A
#define GYR_TRIM_GP1      0x3B
#define GYR_BIST          0x3C
#define GYR_FIFO_CONFIG_0 0x3D
#define GYR_FIFO_CONFIG_1 0x3E

// Data to select for writing to Gyroscope registers
#define GYR_RANGE_2000 0x00
#define GYR_RANGE_1000 0x01
#define GYR_RANGE_500  0x02
#define GYR_RANGE_250  0x03
#define GYR_RANGE_125  0x04

#define GYR_RANGE_SEL_BIT    0
#define GYR_RANGE_SEL_LENGTH 3

// To set the Gyroscope data filter bandwidth 
// Write these values to GYR_BW
#define GYR_BW_32HZ        0x07
#define GYR_BW_64HZ        0x06
#define GYR_BW_12HZ        0x05
#define GYR_BW_23HZ        0x04
#define GYR_BW_47HZ        0x03
#define GYR_BW_116HZ       0x02
#define GYR_BW_230HZ       0x01
#define GYR_BW_UNFILTERED  0x00

#define GYR_BW_SEL_BIT    0
#define GYR_BW_SEL_LENGTH  4

// Options for selecting Gyroscope power mode will
// need to be coded directly as functions

// BMX055 magnetometer registers
#define MAG_WHO_AM_I       0x40  // should return 0x32
// Register 0x41 Reserved
#define MAG_X_LSB          0x42
#define MAG_X_MSB          0x43
#define MAG_Y_LSB          0x44
#define MAG_Y_MSB          0x45
#define MAG_Z_LSB          0x46
#define MAG_Z_MSB          0x47
#define MAG_R_LSB          0x48
#define MAG_R_MSB          0x49
#define MAG_INT_STATUS     0x4A
#define MAG_PWR_CNTL1      0x4B
#define MAG_PWR_CNTL2      0x4C
#define MAG_INT_EN_1       0x4D
#define MAG_INT_EN_2       0x4E
#define MAG_LOW_THS        0x4F
#define MAG_HIGH_THS       0x50
#define MAG_REP_XY         0x51
#define MAG_REP_Z          0x52

// To choose the Magnetometer ODR
#define MAG_ODR_10HZ 0x00 //Default
#define MAG_ODR_2HZ  0x00
#define MAG_ODR_6HZ  0x02
#define MAG_ODR_8HZ  0x03
#define MAG_ODR_15HZ 0x04
#define MAG_ODR_20HZ 0x05
#define MAG_ODR_25HZ 0x06
#define MAG_ODR_30HZ 0x07

#define MAG_ODR_SEL_BIT    0
#define MAG_ODR_SEL_LENGTH 3

/* Trim Extended Registers */
#define BMM050_DIG_X1       0x5D // needed for magnetic field calculation
#define BMM050_DIG_Y1       0x5E  
#define BMM050_DIG_Z4_LSB   0x62
#define BMM050_DIG_Z4_MSB   0x63
#define BMM050_DIG_X2       0x64  
#define BMM050_DIG_Y2       0x65  
#define BMM050_DIG_Z2_LSB   0x68  
#define BMM050_DIG_Z2_MSB   0x69  
#define BMM050_DIG_Z1_LSB   0x6A  
#define BMM050_DIG_Z1_MSB   0x6B  
#define BMM050_DIG_XYZ1_LSB 0x6C 
#define BMM050_DIG_XYZ1_MSB 0x6D 
#define BMM050_DIG_Z3_LSB   0x6E
#define BMM050_DIG_Z3_MSB   0x6F
#define BMM050_DIG_XY2      0x70 
#define BMM050_DIG_XY1      0x71  

// I2C slave addresses are ACC = 0x18, GYR = 0x68, MAG = 0x10
#define ACC_ADDRESS    0x18   // Address of BMX055 accelerometer
#define GYR_ADDRESS    0x68   // Address of BMX055 gyroscope
#define MAG_ADDRESS    0x10   // Address of BMX055 magnetometer
#define MS5637_ADDRESS 0x76   // Address of altimeter

















