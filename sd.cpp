/**
  @file sd.cpp
  @author Tomiyoshi Yuta
  @date Created: 20180531
*/
#include "sd.h"


Sd::Sd() {
  
}

Sd::~Sd() {
}


void Sd::printSd(String log_data) {
  // ファイルを開きます。一度に開くことができるファイルは1つだけなので
  // 別のファイルを開く前にこのファイルを閉じる必要があります。
  File dataFile = SD.open("E2E.txt", FILE_WRITE);//.txtの前は半角、8文字まで
//  String _log_data = log_data;  // ログ保存データ
  if (dataFile) {                                      //if the file in the SD card was open to wrihte, true or false
    dataFile.print(log_data);                          // write data into the file,
    dataFile.close();                                  // close the file,
    check_log=1;
  }
  else {                                              // if the file isn't open, pop up an error message,
    Serial.println(F("error opening file"));
    check_log=0;
  }
  Serial.print(log_data);
  
}

void Sd::printlnSd(String log_data) {
  // ファイルを開きます。一度に開くことができるファイルは1つだけなので
  // 別のファイルを開く前にこのファイルを閉じる必要があります。
  File dataFile = SD.open("E2E.txt", FILE_WRITE);//.txtの前は半角、8文字まで
//  String _log_data = log_data;  // ログ保存データ
  if (dataFile) {                                      //if the file in the SD card was open to wrihte, true or false
    dataFile.println(log_data);                          // write data into the file,
    dataFile.close();                                  // close the file,
    check_log=1;
  }
  else {                                              // if the file isn't open, pop up an error message,
    Serial.println(F("error opening file"));
    check_log=0;
  }
  Serial.println(log_data);
}

void Sd::setupSd() {
  pinMode(SD_CARD, OUTPUT);
  SD.begin(SD_CARD);
  // SSピン（Unoは10番、Megaは53番）は使わない場合でも出力にする
  // そうしないと、SPIがスレーブモードに移行し、SDライブラリが動作しなくなる
//  Serial.println("SD read write test start...");
  Serial.print(F("Initializing SD card.........."));          //check the Serial communication
  delay(100);
  if (!SD.begin(SD_CARD)) {  // check the SD card is available or not,
    Serial.println(F("Card failed, or not present"));  // in the case of SD card error,
  }
  else {
    Serial.println(F("Card initialized."));              //in the case of SD card is available,
  }
  
//  String log_name = "millis, state, light, lat, lon, ax, ay, az, deg, micf_freq, micf_vol, micr_freq, micr_vol, micl_freq, micl_vol, micb_freq, micb_vol, direct, distance soundvol guidanceTime";  // ログ保存データ名
  String log_name = "Time, Light ,Latitude, Longnitude, gravity              ,acc.";  // ログ保存データ名
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");
  printlnSd("\n");  
  printlnSd(log_name);
}
