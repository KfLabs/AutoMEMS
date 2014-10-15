/* ============================================================================
BNO055 I2C device sketch
by: sheen yari
date: 10-4-2014

This software is intended for use by the Laboratory of Neurophysics at the 
University of California - San Diego. 
===============================================================================
*/

// Because we will be sending data to the microSD card, instead of the PC, it
// will be necessary to include the SD, SDFat, or SDFat32 library.
#include "SdFat.h"
#include "SdFatUtil.h"

#include "BufferedWriter.h"

BufferedWriter writer;


// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "BNO055.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include <Wire.h>
#include <SPI.h>

const uint8_t CS = 0;
bool tempFlag = true;


SdFat sd;

SdFile filefirst;
SdFile *file;
// class default I2C address is 0x28
// specific I2C addresses may be passed as a parameter here
// COM3 low = 0x28 (default for InvenSense evaluation board)
// COM3 high = 0x29
BNO055 sensor(BNO055_ADDRESS_COM3_LOW);

int16_t Data[9];
int16_t AccelX = 0;
int16_t MagX = 0;

void setup() {
    
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // wait for Leonardo
    while(!Serial){}  
    
    pinMode(CS, OUTPUT);
    
    // initialize the SD card at SPI_FULL_SPEED for the best performance.
    // try SPI_HALF_SPEED if bus error occurs.
    if(!sd.begin(CS, SPI_FULL_SPEED)) sd.initErrorHalt();
    
    //open or create file - truncate existing file.
    if(!filefirst.open("BENCH.txt", O_CREAT | O_TRUNC | O_RDWR)) 
    {
        if(!filefirst.open("BENCH234.txt", O_CREAT | O_TRUNC | O_RDWR))
        {
          if(!filefirst.open("testopen.txt", O_CREAT));
          {
                Serial.println("open failed"); 
          }
        }
    }
    file = &filefirst;
    writer.init(file);
    
    // initialize sensor
    initial();
	
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400); 
    
    // catch any reset/power up problems
    delay(400);
    
    Serial.print("Self Test Value: ");
    Serial.println(sensor.getSelfTest());
    Serial.print("Operating Mode Value: ");
    Serial.println(sensor.getOperatingMode());
}

void loop() {
if(tempFlag){
        /*
	Serial.println("\nOne print:");
        Serial.println(millis());
	writer.putNum(sensor.getAccelerationX());
	Serial.println(millis());

	Serial.println("\n\n10loops:");
        Serial.println(millis());
        for(int i = 0; i < 9; i++)
	{
	    Serial.print(sensor.getAccelerationX());
	}
	Serial.println(sensor.getAccelerationX());
	Serial.println(millis());

        Serial.println("\n\n50loops:");
        Serial.println(millis());
        for(int i = 0; i < 49; i++)
	{
	    Serial.print(sensor.getAccelerationX());
	}
	Serial.println(sensor.getAccelerationX());
	Serial.println(millis());


        Serial.println("\n\n50loops:");
        Serial.println(millis());
        for(int i = 0; i < 49; i++)
	{
	    Serial.print(sensor.getAccelerationX());
	}
	Serial.println(sensor.getAccelerationX());
	Serial.println(millis());
        
        
        Serial.println("\n\n100loops:");
        Serial.println(millis());
        for(int i = 0; i < 99; i++)
	{
	    Serial.print(sensor.getAccelerationX());
	}
	Serial.println(sensor.getAccelerationX());
	Serial.println(millis());


        Serial.println("\n\n200loops:");
        Serial.println(millis());
        for(int i = 0; i < 199; i++)
	{
	    Serial.print(sensor.getAccelerationX());
	}
	Serial.println(sensor.getAccelerationX());
	Serial.println(millis());

        Serial.println(" ");
	Serial.println(micros());
        */
        
        Serial.print("\n\n10: ");
        Serial.println(millis());
	for(int i = 0; i < 9; i++)
	{
	    sensor.get9AxisData(&Data[0], &Data[1], &Data[2], 
	               	        &Data[3], &Data[4], &Data[5], 
                                &Data[6], &Data[7], &Data[8]);

      	    writer.putNum(Data[0]); writer.putNum(Data[1]); writer.putNum(Data[2]);
            writer.putNum(Data[3]); writer.putNum(Data[4]); writer.putNum(Data[5]);
            writer.putNum(Data[6]); writer.putNum(Data[7]); writer.putNum(Data[8]);
	}
	Serial.println(millis());
        
        Serial.print("\n\n100: ");
        Serial.println(millis());
	for(int i = 0; i < 99; i++)
	{
	    sensor.get9AxisData(&Data[0], &Data[1], &Data[2], 
	               	        &Data[3], &Data[4], &Data[5], 
                                &Data[6], &Data[7], &Data[8]);

      	    writer.putNum(Data[0]); writer.putNum(Data[1]); writer.putNum(Data[2]);
            writer.putNum(Data[3]); writer.putNum(Data[4]); writer.putNum(Data[5]);
            writer.putNum(Data[6]); writer.putNum(Data[7]); writer.putNum(Data[8]);
	}
	Serial.println(" ");
	Serial.println(millis());

        Serial.print("\n\n500: ");
        Serial.println(millis());
	for(int i = 0; i < 499; i++)
	{
	    sensor.get9AxisData(&Data[0], &Data[1], &Data[2], 
	               	        &Data[3], &Data[4], &Data[5], 
                                &Data[6], &Data[7], &Data[8]);

      	    writer.putNum(Data[0]); writer.putNum(Data[1]); writer.putNum(Data[2]);
            writer.putNum(Data[3]); writer.putNum(Data[4]); writer.putNum(Data[5]);
            writer.putNum(Data[6]); writer.putNum(Data[7]); writer.putNum(Data[8]);
	}
	Serial.println(" ");
	Serial.println(millis());
        
        file->close();
        delay(9000);
        tempFlag = !tempFlag;
}
}

void initial()
{
    
    // Change ACCEL Range from +/- 4g to +/- 2g
    // OPTIONS:
    //    - 2G:  ACC_RANGE_2G
    //    - 4G:  ACC_RANGE_4G
    //    - 8G:  ACC_RANGE_8G
    //    - 16G: ACC_RANGE_16G
    sensor.setAccelRange(ACC_RANGE_2G);
    
    // Configure Operation Mode
    // The BNO055 always boots in CONFIG_MODE so an Operation Mode must be chosen upon each power-on cycle
    // OPTIONS:
    //    - IMU
    //    - COMPASS
    //    - M4G
    //    - NDOF_FMC_OFF
    //    - NDOF
    sensor.setOperatingMode(OPR_MODE_NDOF);
}
  
