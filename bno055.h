/**
  @file bno055.h
  @brief CanSat Project 2019
  @author Koh
  @date Created: 20190416
*/
#ifndef _BNO055_H_
#define _BNO055_H_

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Arduino.h"
#include <limits.h>
#include <math.h>

class Bno055{
  public:
  // 関数（適宜追加しよう）（引数も増やしていいよ）
  Bno055();// インストラクタ、やることはピン番号の指定、output,inputの決定
  ~Bno055();//();// デストラクタ、特にすることはなしでいいよ
  void setupBno055(); //もしbno055を起動したときに何かしないとうまく値とらないならここ使って
//  void readAcc();// 3軸の水平加速度のセンサ値を読む関数
//  void readGyro();// 3軸の角速度のセンサ値を読む関数
//  void readCompass();// 機体が今どの方角を向いているかを読む関数
//  void readEuler();//オイラー角
  void readLinearaccel();
  void readgravity();

  // 変数（適宜追加しよう
//  float x,y;
//  float wa;
//  float nx, ny, nz;
//  float theta;
  float gx, gy, gz;
//  float mx, my, mz;
  float Ax, Ay, Az;
//  float ax, ay, az;// ここに3軸の水平加速度のセンサ値を格納
//  float wx, wy, wz;// ここに3軸の角速度のセンサ値を格納
//  float direc;// ここに今どの方角を向いているのかを格納(0を北、90を東（西でもいい）みたいな感じ)
};

#endif
