/**
   @file cansat.cpp
   @author Tomiyoshi Yuta
   @date Created:20190611
*/

# include"cansat.h"

Cansat::Cansat() {
  // うん
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(RELEASING_PIN, OUTPUT);
  pinMode(RELEASING2_PIN, OUTPUT);
  pinMode(RELEASING3_PIN, OUTPUT);
}

Cansat::~Cansat() {
}

void Cansat::setup() {
  Serial.begin(9600);
  gps.setupGps();
  Serial.println(F("Gps.ok"));
  bno055.setupBno055();
  Serial.println(F("bno055.ok"));
  sd.setupSd();
  Serial.println(F("SD is ok"));
  radio.setupRadio();
  Serial.println(F("Radio is ok"));
  delay(100);
}

void Cansat::sensor() {
  /*データの読み込みをします*/
  gps.readGps();
  gps.list[0] = "";
//  Serial.println(F("Gps is ok"));
  light.readLight();
//  Serial.println(F("Light is ok"));
  bno055.readgravity();
  bno055.readLinearaccel();
//  Serial.println(F("Acc is ok"));
  /*データの読み込み終わり*/

  /*センサ値をSDカードに書き込みます*/
  writeSd();
//  Serial.println(F("log is ok"));
  /* 書き込み終わり*/

  /*xBeeで送ります*/
  if (state != FLYING) sendXbee();
//  Serial.println(F("radio is ok"));
  /*SD→xBeeの順番でやらないとバグります（仕様とかじゃなく今回のコード的に）*/
}

void Cansat::writeSd() {
  sd.log_data = String(millis()) + ","
                + String(state) + ","
                + String(sd.check_log) + ","
                + String(light.lightValue) + ","
                + String(gps.Lat) + ","
                + String(gps.Lon) + ","
                + String(bno055.gx) + ","
                + String(bno055.gy) + ","
                + String(bno055.gz) + ","
                + String(bno055.Ax) + ","
                + String(bno055.Ay) + ","
                + String(bno055.Az) + ","
                + String(motor.velocity) + ","
                + String(radio.module1) + ","
                + String(radio.module2) + ",";
//                + String(radio.radio_get_data)+",";
  sd.printlnSd(sd.log_data);
}

void Cansat::sendXbee() {
  sd.log_data = String(millis()) + ","
                + String(state) + ","
                + String(sd.check_log) + ","
                + String(light.lightValue) + ","
                + String(gps.Lat) + ","
                + String(gps.Lon) + ","
                + String(bno055.gx) + ","
                + String(bno055.gy) + ","
                + String(bno055.gz) + ","
                + String(motor.velocity) + ","
                + String(radio.module1) + ","
                + String(radio.module2) + ",";
  sd.log_data = sd.log_data + "e";
  radio.sendData(sd.log_data);
  sd.log_data = "0";
}

void Cansat::sequence() {
  ////////////////////////////////////////////////////
  //   地上局からstate変更
//  radio.getData();
//  if (state != radio.radio_get_data - 48) {
//    if (radio.radio_get_data - 48 > 0 && radio.radio_get_data - 48 < 6) {
//      state = radio.radio_get_data - 48;
//    }
//  }
  ///////////////////////////////////////////////////
  switch (state) {
    case PREPARING:
      preparing();
      break;
    case FLYING:
      flying();
      break;
    case DROPPING:
      dropping();
      break;
    case LANDING:
      landing();
      break;
    case RELEASING:
      releasing();
      break;
    case RUNNING:
      running();
      break;
      state = laststate; // どこにも引っかからない＝stateが頭おかしいのでstateをlaststateへ
  }
}

// state0
void Cansat::preparing() {
  /*格納を検知したらステートを移動するだけの簡単なおしごと*/
  if (preparingTime == 0) {
    preparingTime = millis();
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
  motor.stop();
  //照度センサの値から格納を検知
  if (light.lightValue < LIGHT1_THRE) {
    countPreLoop++;
    if (countPreLoop >= COUNT_LIGHT1_LOOP_THRE) {
      state = FLYING;
      laststate = FLYING;
    }
  } else {
    countPreLoop = 0;
  }
}

// state1
void Cansat::flying() {
  /*格納中はおとなしく待機、放出されたらstate移行（光センサの値で管理するよ）*/
  if (flyingTime == 0) {
    flyingTime = millis();
    //    tone(BUZZER_PIN, 523, 5000);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
  motor.stop();
  if (light.lightValue > LIGHT2_THRE) {
    countFlyLoop++;
    if (countFlyLoop > COUNT_LIGHT2_LOOP_THRE) {
      state = DROPPING;
      laststate = DROPPING;
    }
  }
  else {
    countFlyLoop = 0;
  }
}

// state2
void Cansat::dropping() {
  /*落下中はおとなしく待機、着地を検知したらstate移行（bnoのなにかしらの値でやるよ）*/
  if (droppingTime == 0) {
    droppingTime = millis();
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
  // 加速度から着地検知
  if ((pow(bno055.Ax, 2) + pow(bno055.Ay, 2) + pow(bno055.Az, 2)) < pow(ACC_THRE, 2)) {
    countDropLoop++;
    if (countDropLoop > COUNT_ACC_LOOP_THRE) {
      state = LANDING;
      laststate = LANDING;
    }
  }
  else {
    countDropLoop = 0;
  }
  // 時間からも着地検知
//  if (droppingTime != 0) {
//    if (millis() - droppingTime > LANDING_TIME_THRE) {
//      state = LANDING;
//      laststate = LANDING;
//    }
//  }
}

// state3
void Cansat::landing() {
  /*焼き切り→ステート移行*/
  if (landingTime == 0) {
    landingTime = millis();
    //    tone(BUZZER_PIN, 523, 2000);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  analogWrite(RELEASING_PIN, 255);
  if (landingTime != 0) {
    if (millis() - landingTime > RELEASING_TIME_THRE ) {
      digitalWrite(RELEASING_PIN, LOW);
      state = RELEASING;
      laststate = RELEASING;
    }
  }
}

// state4
void Cansat::releasing() {
  /*タイヤを回す→子機を放出→ちょっと待ったらstate移行（ここが見せ場）*/
  if (runningTime == 0) {
    analogWrite(RELEASING_PIN, 0);// なんか知らんけどたまにテグス焼きっぱなしになって怖いので
    runningTime = millis();
    //    tone(BUZZER_PIN, 121, 2000);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  
  if (countRelLoop < COUNT_REL_LOOP_THRE) {
    motor.go(255);
    Serial.println("モーター回ってる");
  } else if (countRelLoop == COUNT_REL_LOOP_THRE) {
    motor.stopSlowly();
  } else {
    /*ここでなにかしらをして子機を放出*/
    if (releasingTime == 0) {
      releasingTime = millis();
    }
    
    if (releasingTime != 0) {
      if (millis() - releasingTime < RELEASING_TIME_THRE ) {
      analogWrite(RELEASING2_PIN, 255);
      Serial.println("焼いてる1");
      }
      if (millis() - releasingTime > RELEASING_TIME_THRE&& millis() - releasingTime < 2*RELEASING_TIME_THRE) {
        digitalWrite(RELEASING2_PIN, LOW);
        analogWrite(RELEASING3_PIN, 255);
        Serial.println("焼いてる2");
        }
       if(millis() - releasingTime > 2*RELEASING_TIME_THRE){
        digitalWrite(RELEASING3_PIN, LOW);
        /*子機を放出後、state移動*/
        state = RUNNING;
        laststate = RUNNING;
      }
    }
  }
  countRelLoop++;
}

// state5
void Cansat::running() {
  /*ここでようやく子機のセンサ値を受信→sdカードに書き込み*/
  /*タイヤを回す→子機を放出→ちょっと待ったらstate移行（ここが見せ場）*/
  if (runningTime == 0) {
    analogWrite(RELEASING2_PIN, 0);// なんか知らんけどたまにテグス焼きっぱなしになって怖いので
    analogWrite(RELEASING3_PIN, 0);// なんか知らんけどたまにテグス焼きっぱなしになって怖いので
    runningTime = millis();
    //    tone(BUZZER_PIN, 121, 2000);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
  radio.getModuleData();
  
}
