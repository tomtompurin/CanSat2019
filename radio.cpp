/**
  @file xbee.cpp
  @author Yuta Tomiyoshi
  @date Created: 20190709
*/

/**
 * 必要なXBeeの16 bitアドレス
 * 
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
  for (int i = 0; i < 3; i++) {
    delay(10);
    byte trash;
    byte add1;
    byte add2;
    if (Serial3.available() > 15) {
      //      if (Serial3.read() == 0x7E) {//0x7Eは不変
      Serial3.readStringUntil(0x7E);//0x7Eは不変
      //なぜか、delayでプログラムの実行を遅延させないとシリアル値を途中で読み飛ばされて意図しない動作をします。
      delay(10);
      //センサー固有情報の直前まで、12byte読み飛ばします
      for ( int i = 0; i < 12; i++) {
        trash = Serial3.read();// 使わないゴミ（いろんな情報載ってるから使えるなら使いたいけど）
        //          Serial.println(trash,HEX);
      }
      // XBeeの16bitアドレス情報を格納
      add1 = Serial3.read();
      add2 = Serial3.read();
      //
      //        if (Serial3.read() == 0x4D) {//0x4DはxBee毎に固有の値、xBeeを変える場合は注意！！ // 1機目
      //        if (Serial3.read() == 0x1F) {//0x4DはxBee毎に固有の値、xBeeを変える場合は注意！！ // 2機目（アンテナ）
      if (add1 == 0x1F && add2 == 0xA4) { //1FA4はxBee毎に固有の値、xBeeを変える場合は注意！！ // 2機目（アンテナ）
        //なぜか、delayでプログラムの実行を遅延させないとシリアル値を途中で読み飛ばされて意図しない動作をします。
        delay(10);
        //センサーの値の直前まで、5byte読み飛ばします
        for ( int i = 0; i < 5; i++) {
          trash = Serial3.read();
          //            Serial.println(trash,HEX);
        }
        //センサーの値（2byte）を読み出します
        int hex_pre1 = Serial3.read();
        int hex_aft1 = Serial3.read();
        //          trash = Serial3.read();
        //      //センサーの値を16進数表示します
        //      Serial.print(String(hex_pre,HEX) +" " + String(hex_aft,HEX) );
        //センサーの値10進数に変換します
        if ((hex_pre1 * 256 + hex_aft1) >= 0 && (hex_pre1 * 256 + hex_aft1) < 1024) {
          module1 = (hex_pre1 * 256 + hex_aft1);
        }
      }
      //        trash = Serial3.read();
      //        if (Serial3.read() == 0x8B) {//0x8BはxBee毎に固有の値、xBeeを変える場合は注意！！ // 1機目
      //        if (Serial3.read() == 0x5A) {//0x8BはxBee毎に固有の値、xBeeを変える場合は注意！！ // 2機目（アンテナ)
      if (add1 == 0x2D && add2 == 0x5A) { //2D5AはxBee毎に固有の値、xBeeを変える場合は注意！！ // 2機目（アンテナ)
        //なぜか、delayでプログラムの実行を遅延させないとシリアル値を途中で読み飛ばされて意図しない動作をします。
        delay(10);
        //センサーの値の直前まで、5byte読み飛ばします
        for ( int i = 0; i < 5; i++) {
          trash = Serial3.read();
          //            Serial.println(trash,HEX);
        }
        //センサーの値（2byte）を読み出します
        int hex_pre2 = Serial3.read();
        int hex_aft2 = Serial3.read();
        //          trash = Serial3.read();
        //センサーの値10進数に変換します
        if ((hex_pre2 * 256 + hex_aft2) >= 0 && (hex_pre2 * 256 + hex_aft2) < 1024) {
          module2 = (hex_pre2 * 256 + hex_aft2);
        }
      }
    }
  }
}
//}
