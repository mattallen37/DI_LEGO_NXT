#pragma config(Sensor, S1,     DIMU,                sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: DIMU-test1.c 62 2011-08-20 14:35:20Z xander $
 */

/**
 * IMU-driver.h provides an API for the Dexter Industries IMU Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Dexter Industries for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 07 August 2011
 * version 0.1
 */

#include "drivers/DIMU-driver.h"

task main(){

  float x_val, y_val, z_val;      // Gyro axis values

  nxtDisplayCenteredTextLine(0, "Dexter Ind.");
  nxtDisplayCenteredBigTextLine(1, "IMU");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

  // Fire up the gyro and initialize it. Only needs to be done once.
  //DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_500);
  if (!DIMUconfigAccel(DIMU, DIMU_ACC_RANGE_2G))
    PlaySound(soundException);

  // Sets max readings for the Gyroscope to 2000 degrees per second.
  if(!DIMUconfigGyro(DIMU, DIMU_GYRO_RANGE_2000))
    PlaySound(soundException);

  // Here we'll setup to write to file.  We're going to write values to a file.
  const string sFileName = "GYRO2000.txt";  // Our destination File
  TFileIOResult nIoResult;
  TFileHandle hFileHandle;
  int nFileSize = 8500;
  hFileHandle = 0;
  Delete(sFileName, nIoResult);
  OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);

  for (int i = 0; i < 500; i++){

		// Read the GYROSCOPE
    // All at once, very convenient if you need all 3
    DIMUreadGyroAxes(DIMU, x_val, y_val, z_val);

    string str_x_val = (string)x_val;     // Turn it into a string to write to file.
    string str_y_val = (string)y_val;     // Turn it into a string to write to file.
    string str_z_val = (string)z_val;     // Turn it into a string to write to file.

    WriteString(hFileHandle, nIoResult, str_x_val);    // Write x value to file.
    WriteString(hFileHandle, nIoResult, ",");          // Write to file.
    WriteString(hFileHandle, nIoResult, str_y_val);    // Write y value to file.
    WriteString(hFileHandle, nIoResult, ",");          // Write to file.
    WriteString(hFileHandle, nIoResult, str_z_val);    // Write z value to file.
    WriteString(hFileHandle, nIoResult, "\r\n");       // Write return line to file.
    wait1Msec(50);
  }
}

/*
 * $Id: DIMU-test1.c 62 2011-08-20 14:35:20Z xander $
 */