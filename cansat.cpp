/**
 * @file cansat.cpp
 * @author Tomiyoshi Yuta
 * @date Created:20190611
 */

 # include"cansat.h"

 Cansat::Cansat(){
  pinMode(RED_PIN,OUTPUT);
  pinMode(YELLOW_PIN,OUTPUT);
  pinMode(BLUE_PIN,OUTPUT);
 }


 Cansat::~Cansat(){ 
 }

 void Cansat::setup(){
  Serial.begin(9600);
  sd.setupSd();
  Serial.println("Gps.ok");
  delay(100);
 }

 void Cansat::test(SoftwareSerial a){
  a.begin(9600);
  delay(10);
  if(a.available()>0){
    gps.readGps(a);
  }
   
  String log_data = gps.Time+  "," +gps.Lat+  "," +gps.Lon;
//  Serial.println(log_data);
  sd.printSd(log_data);
 }
 
