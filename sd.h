/**
  @file sd.h
  @author Tomiyoshi Yuta
  @date Created: 20180531
*/

#ifndef _SD_H_
#define _SD_H_
//#include <stdio.h>
#include "constant.h"
#include <string.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class Sd {
  public:
  // 関数
  Sd();
  ~Sd();
  void setupSd();  // setup
  void printSd(String log_data);  // log保存

  String log_data;
  };

  #endif
