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
 #include "radio.h"
 #include "motor.h"

  class Cansat{
    public:
    Cansat();
    ~Cansat();

    // オブジェクト生成
    // ピンも指定
    Light light=Light(LIGHT_PIN);
    Motor motor=Motor(VREF_PIN,IN1_PIN,IN2_PIN);
    // SPI通信
    Gps gps;
    // シリアル通信
    Sd sd;
    Radio radio;
    // I2C通信
    Bno055 bno055;


    // メイン関数
    void setup();
    void sensor();
    void sequence();
    void test();


    // sensor用関数 
    void writeSd();
    void sendXbee();


    // sequence用関数
    void preparing();
    void flying();
    void dropping();
    void landing();
    void releasing();
    void running();

    // 変数(ここを書き換える)
    int state=5;
    int laststate=4;

    // state管理用変数
    int countPreLoop=0;
    int countFlyLoop=0;
    int countDropLoop =0;
    int countRelLoop=0;

    // stateに入った時刻
    unsigned long preparingTime = 0;
    unsigned long flyingTime = 0;
    unsigned long droppingTime = 0;
    unsigned long landingTime = 0;
    unsigned long releasingTime = 0;
    unsigned long runningTime = 0;
    unsigned long NowRunningTime = 0;
     
  };

  #endif
 
  
