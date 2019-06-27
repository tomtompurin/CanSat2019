/**
   @file cansat.cpp
   @author Tomiyoshi Yuta
   @date Created:20190611
*/

# include"cansat.h"

Cansat::Cansat() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}


Cansat::~Cansat() {
}

void Cansat::setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("Gps.ok");
  bno055.setupBno055();
  Serial.println("bno055.ok");
  sd.setupSd();
  delay(100);
}

void Cansat::test() {
  if (Serial2.available() > 0) {
    gps.readGps();
    gps.list[0] = "";
  }
  
  light.readLight();
  bno055.readgravity();
  bno055.readAcc();

  sd.log_data = gps.Time +  ",   ";
  sd.printSd(sd.log_data);
  //  Serial.println(log_data);
  sd.log_data = String(light.lightValue) + ",   ";
  sd.printSd(sd.log_data);
//  Serial.println(log_data);
  sd.log_data = gps.Lat +  ",   ";
  sd.printSd(sd.log_data);
//  Serial.println(log_data);
  sd.log_data = gps.Lon + ",   ";
  sd.printSd(sd.log_data);
//  Serial.println(log_data);
  sd.log_data = "g:( " + String(bno055.gx) + ", " + String(bno055.gy) + ", " + String(bno055.gz) + ")";
  sd.printSd(sd.log_data);
//  Serial.println(log_data);
  sd.log_data = "a:( " + String(bno055.ax) + ", " + String(bno055.ay) + ", " + String(bno055.az) + ")";
//  Serial.println(log_data);
  sd.printSd(sd.log_data);
  delay(10);
  sd.printSd("\n");
  sd.log_data="0";
}
