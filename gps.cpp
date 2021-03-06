/**
   @file gps.cps
   @brief CanSat Project 2019
   @author Tomiyoshi
   @date Created: 20190530
*/

#include "gps.h"



Gps::Gps() {
}

Gps::~Gps() {
}

//String Gps::NMEA2DMS(float val) {
//  int d = val / 100;
//  int m = ((val / 100.0) - d) * 100.0;
//  float s = ((((val / 100.0) - d) * 100.0) - m) * 60;
//  return String(d) + "度" + String(m) + "分" + String(s, 1) + "秒";
//}

//String Gps::NMEA2DM(float val) {
//  int d = val / 100;
//  float m = ((val / 100.0) - d) * 100.0;
//  return String(d) + "度" + String(m, 4) + "分";
//}

String Gps::NMEA2DD(float val) {
  int d = val / 100;
  int m = (((val / 100.0) - d) * 100.0) / 60;
  float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
  return String(d + m + s, 6);
}

//String Gps::NMEA2NUM(int val) {
//  int num = val;
//  return String(num);
//}

String Gps::UTC2GMT900(String str) {
  int hh = (str.substring(0, 2).toInt()) + 9;
  if (hh > 24) hh = hh - 24;
  return String(hh, DEC) + ":" + str.substring(2, 4) + ":" + str.substring(4, 6);
}


void Gps::setupGps() {
  Serial2.begin(9600);
}

void Gps::readGps() {
  if (Serial2.available() > 0) {
  while (list[0] != "$GPGGA") {
    // 1つのセンテンスを読み込む
    line = Serial2.readStringUntil('\n');
    if (line != "") {
      int i, index = 0, len = line.length();
      String str = "";
      // StringListの生成(簡易);
      for (i = 0; i < 7; i++) {
        list[i] = "";
        }

      // 「,」を区切り文字として文字列を配列にする
      for (i = 0; i < len; i++) {
        if (line[i] == ',') {
          list[index++] = str;
          if (index > 6) {
            break;
          }
          str = "";
          continue;
        }
        str += line[i];
      }
      line="";
      // $GPGGAセンテンスのみ読み込む
      if (list[0] == "$GPGGA") {
        // ステータス
        if (list[6] != "0") {
          // 現在時刻
          Time = UTC2GMT900(list[1]);
          // 緯度
          Lat = NMEA2DD(list[2].toFloat());
          // 経度
          Lon = NMEA2DD(list[4].toFloat());
          Serial.println(Time);
        } else {
          Serial.println(F("測位できませんでした。"));
        }
      }
    }
  }
}else{
  Serial.println(F("GPSが検出されませんでした"));
}
}
