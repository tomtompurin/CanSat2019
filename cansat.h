/**
 * @file cansat.h
 * @author Tomiyoshi Yuta
 * @date 20190611
 */
 #ifndef _CANSAT_H_
 #define _CANSAT_H_
 #include <stdio.h>
 #include <string.h>
// #include <SoftwareSerial.h>
 #include "gps.h"
 #include "sd.h"
 #include "bno055.h"
 #include "constant.h"
 #include "light.h"

  class Cansat{
    public:
    Cansat();
    ~Cansat();

    // オブジェクト生成
    // ピンも指定
    Light light=Light(LIGHT_PIN);

    
    // SPI通信
    Gps gps;
    // シリアル通信
    Sd sd;
    // I2C通信
    Bno055 bno055;

    // メイン関数
    void setup();
    void writeSd();
    void sendXbee();
    void test();
     
  };

  #endif
 
  
