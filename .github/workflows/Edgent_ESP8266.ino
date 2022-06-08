
// Fill-in information from your Blynk Template here

#define BLYNK_TEMPLATE_ID "TMPLSGAQ-Dov"
#define BLYNK_DEVICE_NAME "SmartBinAI"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include<Servo.h>
#define ph_sensor A0//a0
Servo servoMain; // Define our Servo

BlynkTimer timer1;
const int trigpin2 = 12;//d5
const int echopin2 = 14;//d6
long dur;
int dist;
float ph_value, sensor_value = 0;
int trigpin =5;//d1
int pos = 0;
int echopin =4;//d2
int distance;
float duration;
float cm;
void datas(){
  Blynk.virtualWrite(V0,dist);
  Blynk.virtualWrite(V1,sensor_value);
}
void setup()
{
  //Serial.begin(115200);
  //delay(100);

  BlynkEdgent.begin();
  Serial.begin(9600);
  delay(100);

  BlynkEdgent.begin();
  
  servoMain.attach(13); // d7
  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  servoMain.write(0);
  timer1.setInterval(2000L,datas);
}

void loop() {
  BlynkEdgent.run();
   ph_value = analogRead(ph_sensor);
  sensor_value = (ph_value/10);
  Serial.print("ph_value=");
  Serial.println(sensor_value);
  delay(1000);

  digitalWrite(trigpin, LOW);
  delay(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  cm = (duration / 58.82);
  distance = cm;
  if (distance < 10)
  {
    servoMain.write(180); // Turn Servo back to center position (90 degrees)
    delay(1000);
  }
  else {
    servoMain.write(0);
    delay(50);
  }
  digitalWrite(trigpin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(10);


  dur = pulseIn(echopin2, HIGH);
  dist = 0.0343 * (dur / 2);
  Serial.print("Distance:");
  Serial.println(dist);
  timer1.run();
}
