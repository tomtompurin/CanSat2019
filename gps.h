/**
   @file gps.h
   @brief CanSat Project 2019
   @author Tomiyoshi
   @date Created: 20190530
*/
#ifndef _GPS_H_
#define _GPS_H_

//#include <stdio.h>
#include <String.h>
#include <Arduino.h>
//#include <SoftwareSerial.h>



class Gps {
  public:
    // 関数
    Gps();
    ~Gps();
//    String NMEA2DMS(float val);  // NMEAの緯度経度を「度分秒」(DMS)の文字列に変換する
//    String NMEA2DM(float val); // (未使用)NMEAの緯度経度を「度分」(DM)の文字列に変換する
    String NMEA2DD(float val); // NMEAの緯度経度を「度」(DD)の文字列に変換する
//    String NMEA2NUM(int val); // NMEAの衛星番号を「」(NUM)の文字列に変換
    String UTC2GMT900(String str); // UTC時刻から日本の標準時刻に変換する(GMT+9:00)
    void readGps();
    void setupGps();
    // 変数
    String Lon="0";
    String Lat="0";
    String Time="0:0:0";
    String line;
    String list[7];
};

#endif
