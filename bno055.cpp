/**
  @file bno055.cpp
  @brief CanSat Project 2019
  @author Koh
  @date Created: 20190416
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Arduino.h"
#include <limits.h>
#include <math.h>
#include "bno055.h"

Adafruit_BNO055 bno = Adafruit_BNO055();



Bno055::Bno055(){
}

Bno055::~Bno055(){
}

void Bno055::setupBno055(){
//  Serial.println("Orientation Sensor  Test"); 
    if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print(F("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"));
//    while(1);
  }
// while(!bno.isFullyCalibrated());
// Serial.println("calibration finished!");
//
// delay(1000);
//
// //bno.setMode();
// bno.setExtCrystalUse(true); 
}

void Bno055::readLinearaccel(){
    imu::Vector<3> linearaccel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
    Ax=linearaccel.x();
    Ay=linearaccel.y();
    Az=linearaccel.z();
}

//void Bno055::readAcc(){
//    imu::Vector<3> accelerometer = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
//    ax = accelerometer.x();
//    ay = accelerometer.y();
//    az = accelerometer.z();
//}

//void Bno055::readGyro(){
//    imu::Vector<3> gyroscope = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
//    wx = gyroscope.x()*M_PI/180;
//    wy = gyroscope.y()*M_PI/180;
//    wz = gyroscope.z()*M_PI/180;
//}

//void Bno055::readCompass(){
//    imu::Vector<3> magnetometer = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
//    mx = magnetometer.x();
//    my = magnetometer.y();
//    mz = magnetometer.z();
//    wa = gx*gx+gy*gy;
//    theta=atan(sqrt(wa)/gz);
//    nx=ay*Az-Ay*az;
//    ny=Ax*az-ax*Az;
//    nz=ax*Ay-ay*Ax;
//    x=mx*(nx*nx*(1-cos(theta))+cos(theta))+my*(nx*ny*(1-cos(theta)))+mz*ny*sin(theta);
//    y=mx*(nx*ny*(1-cos(theta)))+my*(ny*ny*(1-cos(theta))+cos(theta))-mz*nx*sin(theta);
//    direc = atan2(y, x);
//    if(direc < 0){
//    direc += 2*PI;
//    }
//    direc = -(direc * 180/M_PI+270-8)+360; 
//}

void Bno055::readgravity(){
    imu::Vector<3> gravity  = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
    gx=gravity.x();
    gy=gravity.y();
    gz=gravity.z();
}
