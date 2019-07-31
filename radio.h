/**
  @file xbee.h
  @author Yuta Tomiyoshi
  @date Created: 20190709
*/

#ifndef _RADIO_H_
#define _RADIO_H_
#include "Arduino.h"
#include <XBee.h>

class Radio{
  public:
  Radio();
  ~Radio();
  void setupRadio();
  void getModuleData();
  void getData();  // 地上局からステートが送られてきたら受け取る
  void sendData(String radio_data);  // データ送信

  int module1;
  int module2;
  // 変数  
  int radio_get_data = 48;

  // よくわからない子たち
  XBee manager;
  uint8_t payload[90];
  XBeeAddress64 addr64 = XBeeAddress64(0x13A200, 0x4154CBE0);// 実際の送信先64bitアドレスを記入します。(ここもxBee毎に固有の値、地上局のXbeeのアドレス)
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));// 上で定義したpayloadのデータサイズを指定します。
};

#endif
