/**
   @file cansat2019.ino
   @brief CanSat Project 2019
   @auther Tomiyoshi Yuta
   @date Created: 2019/04/16
*/

#include <stdio.h>
#include <string.h>
#include "Arduino.h" // 便利だからいつもインクルードしてる
#include "constant.h" // 全ての定数を管理するファイル
#include "cansat.h" // 各センサの関数を統合した関数を管理するファイル

Cansat cansat;
//SoftwareSerial SerialGps(SOFT_RX, SOFT_TX);


void setup() {
  // put your setup code here, to run once:
  cansat.setup();
}

void loop() {
    cansat.sensor(); // センサの値をとってくる(フィルタリング処理込み)
    delay(50); // 動作を安定させるためにちょっと待つ
    cansat.sequence(); // センサの値やら現在のステートやらをもとにどう制御するか
    delay(50); // 動作を安定させるためにちょっと待つ
}
