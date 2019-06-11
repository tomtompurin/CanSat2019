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
  File dataFile = SD.open("GPStest.txt", FILE_WRITE);//.txtの前は半角、8文字まで
  String _log_data = log_data;  // ログ保存データ
  if (dataFile) {                                      //if the file in the SD card was open to wrihte, true or false
    dataFile.println(_log_data);                          // write data into the file,
    dataFile.close();                                  // close the file,
    Serial.println(_log_data);
  }
  else {                                              // if the file isn't open, pop up an error message,
    Serial.println("error opening file");
  }
}

void Sd::setupSd() {
  pinMode(SD_CARD, OUTPUT);
  SD.begin(SD_CARD);
  // SSピン（Unoは10番、Megaは53番）は使わない場合でも出力にする
  // そうしないと、SPIがスレーブモードに移行し、SDライブラリが動作しなくなる
//  Serial.println("SD read write test start...");
  Serial.print("Initializing SD card..........");          //check the Serial communication
  if (!SD.begin(SD_CARD)) {  // check the SD card is available or not,
    Serial.println("Card failed, or not present");  // in the case of SD card error,
  }
  else {
    Serial.println("Card initialized.");              //in the case of SD card is available,
  }
  
//  String log_name = "millis, state, light, lat, lon, ax, ay, az, deg, micf_freq, micf_vol, micr_freq, micr_vol, micl_freq, micl_vol, micb_freq, micb_vol, direct, distance soundvol guidanceTime";  // ログ保存データ名
  String log_name = "Time, Latitude, Longnitude";  // ログ保存データ名
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");
  printSd("     ");  
  printSd(log_name);
}
