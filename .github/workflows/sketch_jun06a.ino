
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266_SSL.h>
#define BLYNK_TEMPLATE_ID "TMPLSGAQ-Dov"
#define BLYNK_DEVICE_NAME "SmartBinAI"
#define BLYNK_AUTH_TOKEN "1If4c18gC7OZxnfK8aVfwNBmG7PPeD1I"
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "POCO X3";
char pass[] = "guesskarbsdk";

WidgetLED led1(V1);

BlynkTimer timer;

// V1 LED Widget is blinking
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 443);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}
