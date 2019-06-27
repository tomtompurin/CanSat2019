/**
   @file constant.h
   @brief CanSat Project 2019
   @auther Tomiyoshi Yuta
   @date Created: 2019/04/16
*/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_

//ピン番号指定
#define RED_PIN A0 //仮置き
#define YELLOW_PIN A1 //仮置き
#define BLUE_PIN A2 //仮置き
#define SOFT_RX 5
#define SOFT_TX 6
//#define SD_CARD 10 //Uno
#define SD_CARD 53 //MEGA
#define LIGHT_PIN A3


//シーケンス
#define PREPARING 0 //電源on~格納検知
#define STORED 1 //格納検知~放出検知
#define RELEASE 2 //放出検知~飛行開始
#define FLYING 3 //飛行開始~着陸態勢まで
#define LANDING 4 //着陸態勢~着陸(着陸検知)（作るかどうかは未定）
#define GOAL 5 //着陸~



#endif
