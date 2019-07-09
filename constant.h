/**
   @file constant.h
   @brief CanSat Project 2019
   @auther Tomiyoshi Yuta
   @date Created: 2019/04/16
*/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_

//ピン番号指定
#define RED_LED_PIN A0 //仮置き
#define GREEN_LED_PIN A1 //仮置き
#define BLUE_LED_PIN A2 //仮置き
//#define SOFT_RX 5 //Uno
//#define SOFT_TX 6 //Uno
//#define SD_CARD 10 //Uno
#define SD_CARD 53 //MEGA
#define LIGHT_PIN A3 //照度センサ
#define VREF_PIN 45 //仮置き
#define IN1_PIN 44 //仮置き
#define IN2_PIN 46 //仮置き
#define RELEASING_PIN 30 //仮置き
#define RELEASING2_PIN 31 //仮置き
#define RELEASING3_PIN 32 //仮置き

//シーケンス
#define PREPARING 0 //電源on~格納検知
#define FLYING 1 //格納検知~放出検知
#define DROPPING 2 //放出検知~着陸検知
#define LANDING 3 //着陸検知～焼き切り
#define RELEASING 4 //子機を投げる 
#define RUNNING 5 //ミッション頑張るマン

// 閾値系
#define LIGHT1_THRE 200 //格納検知のための閾値
#define COUNT_LIGHT1_LOOP_THRE 10 //上に同じ
#define LIGHT2_THRE 700 //放出検知のための閾値
#define COUNT_LIGHT2_LOOP_THRE 10 //上に同じ
#define ACC_THRE 3//着地検知のための閾値
#define COUNT_ACC_LOOP_THRE 10 //上に同じ
const unsigned long LANDING_TIME_THRE=2400*1000; // FLYINGのstateに入って40分で着地を検知したことにする。
#define RELEASING_TIME_THRE 15000 // 焼き切りの時間（15秒）
#define COUNT_REL_LOOP_THRE 5 // 着地後のタイヤを回す回数に関わる数値


#endif
