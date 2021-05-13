/**
  @file xbee.cpp
  @author Hiroyuki Yoshihara
  @date Created: 20180512
*/
#include "radio.h"
Radio::Radio() {
}

Radio::~Radio() {
}

void Radio::setupRadio() {
  Serial1.begin(9600);
  String radio_name = "state, millis, light, lat, lon, ax, ay, az, deg, mic...";
  Serial1.println(F("state, millis, light, lat, lon, ax, ay, az"));
}

void Radio::getData() {
  Serial1.begin(9600);
  if (Serial1.available()) {
    radio_get_data = Serial1.parseInt();
  }
}

void Radio::sendData(String radio_data) {
  Serial1.end();
  Serial1.begin(9600);
  Serial1.println(radio_data);
  Serial.println(radio_data);
}
