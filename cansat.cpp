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
  Serial.begin(115200);
  sd.setupSd();
  Serial.println("Gps.ok");
  bno055.setupBno055();
  Serial.println("bno055.ok");
  delay(100);
}

void Cansat::test(SoftwareSerial a) {
  a.begin(9600);
  delay(10);
  if (a.available() > 0) {
    gps.readGps(a);
  }
  bno055.readgravity();
  bno055.readAcc();
  String log_data = gps.Time +  ",   "
                    + gps.Lat +  ",   "
                    + gps.Lon + ",   "
                    + "g:( " + String(bno055.gx) + ", " + String(bno055.gy) + ", " + String(bno055.gz) + ")"
                    + "a:( " + String(bno055.ax) + ", " + String(bno055.ay) + ", " + String(bno055.az) + ")";
  Serial.println(log_data);
//  sd.printSd(log_data);
}
