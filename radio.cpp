/**
  @file xbee.cpp
  @author Yuta Tomiyoshi
  @date Created: 20190709
*/

/**
   必要なXBeeの16 bitアドレス
   R1：1FA4
   R2：312D
   R3：CD2B
   R4：5D43
   R5：33CE
*/

#include "radio.h"
Radio::Radio() {
}

Radio::~Radio() {
}

void Radio::setupRadio() {
  Serial3.begin(9600);
  manager.setSerial(Serial3);
}

void Radio::getData() {
  if (Serial3.available() > 17) {
    if (Serial3.read() == 0x7E) {//0x7Eは不変
      //なぜか、delayでプログラムの実行を遅延させないとシリアル値を途中で読み飛ばされて意図しない動作をします。
      delay(10);
      //センサー固有情報の直前まで、12byte読み飛ばします
      byte trash;
      for ( int i = 0; i < 12; i++) {
        delay(5);
        trash = Serial3.read();// 使わないゴミ（いろんな情報載ってるから使えるなら使いたいけど
        //        Serial.println(trash, HEX);
      }

      if (Serial3.read() == 0x63) {//0xCEはxBee毎に固有の値、xBeeを変える場合は注意！！(多分Gの16ビット識別番号(地震はない))
        //なぜか、delayでプログラムの実行を遅延させないとシリアル値を途中で読み飛ばされて意図しない動作をします。
        delay(10);
        //センサーの値の直前まで、3byte読み飛ばします
        for (int i = 0; i < 3; i++) {
          byte trash = Serial3.read();
          //          Serial.println(trash, HEX);
        }
        //センサーの値（2byte）を読み出します
        radio_get_data = Serial3.read();
      }
    }
  }
}

void Radio::sendData(String radio_data) {
  //  Serial.println(radio_data.length());
  for (int i = 0; i < radio_data.length(); i++) {
    payload[i] = radio_data.charAt(i);
    delay(5);
  }
  manager.send(zbTx);
  //    Serial.println(radio_data);
}

void Radio::getModuleData() {//
  for (int i = 0; i < 2; i++) {
    delay(10);
    byte trash;
    byte add1;
    byte add2;
    if (Serial3.available() > 15) {
      Serial3.readStringUntil(0x7E);//0x7Eは不変
      delay(10);
      //センサー固有情報の直前まで、12byte読み飛ばします
      for ( int i = 0; i < 12; i++) {
        trash = Serial3.read();// 使わないゴミ
      }
      // XBeeの16bitアドレス情報を格納
      add1 = Serial3.read();
      add2 = Serial3.read();
//            Serial.print(add1,HEX);
//            Serial.println(add2,HEX);

      /*
       * 子機1
       */
      if (add1 == 0x5D && add2 == 0x43) {//ここを書き換えます
        delay(10);
        //センサーの値の直前まで、5byte読み飛ばします(R2,R4は6)
        for ( int i = 0; i < 6; i++) {//ここを書き換えます
          trash = Serial3.read();
        }
        //センサーの値（2byte）を読み出します
        int hex_pre1 = Serial3.read();
        int hex_aft1 = Serial3.read();
        //センサーの値10進数に変換します
        if ((hex_pre1 * 256 + hex_aft1) >= 0 && (hex_pre1 * 256 + hex_aft1) < 1024) {
          module1 = (hex_pre1 * 256 + hex_aft1);
        }
      }

      /*
       * 子機2
       */
      if (add1 == 0x33 && add2 == 0xCE) { //ここを書き換えます
        delay(10);
        //センサーの値の直前まで、5byte読み飛ばします(R2,R4は6)
        for ( int i = 0; i < 5; i++) {//ここを書き換えます
          trash = Serial3.read();
        }
        //センサーの値（2byte）を読み出します
        int hex_pre2 = Serial3.read();
        int hex_aft2 = Serial3.read();
        //センサーの値10進数に変換します
        if ((hex_pre2 * 256 + hex_aft2) >= 0 && (hex_pre2 * 256 + hex_aft2) < 1024) {
          module2 = (hex_pre2 * 256 + hex_aft2);
        }
      }
    }
  }
}
//}
