

// Because we will be sending data to the microSD card, instead of the PC, it
// will be necessary to include the SD, SDFat, or SDFat32 library.
#include "SdFat.h"
#include "SdFatUtil.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include <Wire.h>
#include <SPI.h>

#define FILE_SIZE_MB 5
#define FILE_SIZE (1000000UL*FILE_SIZE_MB)
#define BUF_SIZE 250
#define FINAL_LOOP 3000

// store error strings in flash to save RAM
#define error(s) sd.errorHalt_P(PSTR(s))

// uncomment the next 2 lines if you want to flash the blinkState
// #define LED_PIN 13
// bool blinkState = false;

// class default I2C address is 0x28
// specific I2C addresses may be passed as a parameter here
// COM3 low = 0x28 (default for InvenSense evaluation board)
// COM3 high = 0x29
MPU6050 sensor;

// SD chip select pin
const uint8_t CS = 0;

// buffer for file input
// not using currently BUT I NEED TO
uint16_t buf[BUF_SIZE];

// file system
SdFat sd;

// test file
SdFile file;

//String outToSD = "";
int16_t Data[9];
int16_t AccelX = 0;
int16_t MagX = 0;

// Benchmarking variables
// time_i will store the value of micros() immediately before a benchmark
// delTime will store the value of micros() after a benchmark minus time_i
int time_i = 0;
int delTime = 0;

void setup() {
    
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    // wait for Leonardo
    while(!Serial){}  
    
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);
	
	// Make sure the default chip select pin is set to output.
    pinMode(CS, OUTPUT);
	
	// initialize the SD card at SPI_FULL_SPEED for the best performance.
    // try SPI_HALF_SPEED if bus error occurs.
    if(!sd.begin(CS, SPI_FULL_SPEED)) sd.initErrorHalt();
	
    Serial.print("\nType is FAT");
    Serial.println(int(sd.vol()->fatType()));
	
	//open or create file - truncate existing file.
    if(!file.open("BENCH.txt", O_CREAT | O_TRUNC | O_RDWR)) error("open failed"); 
    
	// Initialize device
    //sensor.initialize();
    
    //Serial.println(pstr("\nUse a freshly formated SD for the best performance."));
	
    // To flash led
    // pinMode(LED_PIN, OUTPUT);
    
    // catch any reset/power up problems
    delay(400);
}

void loop() {
    
	Serial.print("\nFree RAM: ");
        Serial.println(FreeRam());

        // Average speed to write x-Acceleration data to SD over 1000 intervals
	Serial.println(micros());
	for(int i = 0; i < 999; i++)
	{
	    file.write(sensor.getAccelerationX());
	}
        //delTime = micros() - time_i;
	Serial.print("\n\nx-Acceleration only, data rate = ");
	Serial.println(micros());

	// Average speed to write x-Magnetometer to SD over 1000 intervals
	//time_i = micros();
	//for(int i = 0; i < 999; i++)
	//{
	//    file.write(sensor.getMagX());
	//}
        //delTime = micros() - time_i;
	//Serial.print("\n\nx-Magnetometer only, data rate = ");
        //Serial.println(delTime/(1000));
    
        // Measure average speed to write 9-axis data to SD over 1000 intervals 
        //time_i = micros();
        Serial.println(micros());
	for(int i = 0; i < 999; i++)
	{
	    sensor.getMotion9(&Data[0], &Data[1], &Data[2], 
	               	        &Data[3], &Data[4], &Data[5], 
                                &Data[6], &Data[7], &Data[8]);

      	    file.write(Data, 9);
	}
	//delTime = micros() - time_i;
	Serial.print("\n\n9-axis data rate = ");
	Serial.println(micros());

	// Measure speed to read 250 x-Acceleration values, then write to a 
	// buffer and stream data to file BENCH.DAT 
	// NOTE: This test will not measure the lags between buffer writes
	//time_i = micros();
        Serial.println(micros());
	for(int i = 0; i < 250; i++)
	{
	    buf[i] = sensor.getAccelerationX();
	}
	if(file.write(buf, sizeof(buf)) != sizeof(buf)) error("write failed");
	delTime = micros() - time_i;
	Serial.print("\n\nBuffer write x-Acceleration data rate(250) = ");
        Serial.println(delTime);
	// 1/((delTime*250)/1000000) = delTime/4000 <- Probably going to be this (aka the line below)
	Serial.print("\nBuffer write x-Acceleration data rate(4000) = ");
        Serial.println(micros());
        //Serial.print(delTime/4000);
	
	// close file
	file.close();
	
    // uncomment the next 2 lines to blink LED
    // blinkState = !blinkState;
    // digitalWrite(LED_PIN, blinkState);
}

void initialize()
{
	Serial.println("Initializing I2C devices...");
    
    // verify sensor connection
    Serial.println("Testing device connections...");
    delay(3000);
    
    // Change ACCEL Range from +/- 4g to +/- 2g
    // OPTIONS:
    //    - 2G:  ACC_RANGE_2G
    //    - 4G:  ACC_RANGE_4G
    //    - 8G:  ACC_RANGE_8G
    //    - 16G: ACC_RANGE_16G
    //sensor.setAccelRange(ACC_RANGE_2G);
    
    // Configure Operation Mode
    // The BNO055 always boots in CONFIG_MODE so an Operation Mode must be chosen upon each power-on cycle
    // OPTIONS:
    //    - IMU
    //    - COMPASS
    //    - M4G
    //    - NDOF_FMC_OFF
    //    - NDOF
    //sensor.setOperatingMode(OPR_MODE_NDOF);
}









