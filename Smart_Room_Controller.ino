#include <SPI.h>
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define ON LOW
#define OFF HIGH

#include <DHT.h>

char auth[] = "7d6c94a6916f4d0395c0e8b5ab4699f6";

char ssid[] = "Dulan";
char pass[] = "DPN634719hp$";

#define DHTPIN D2

#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, t);
}
void notifyOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = !digitalRead(D1);
  if (isButtonPressed) {
    Serial.println("Button is pressed.");

    // Note:
    //   We allow 1 notification per 15 seconds for now.
    Blynk.notify("Yaaay... button is pressed!");
  }
}


int relay1 = D1;
int relay2 = D3;
int relay3 = D4;
int relay4 = D5;
int relay5 = D6;
int relay6 = D7;
int relay7 = D8;
int relay8 = D0;

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);

  Blynk.begin(auth, ssid, pass);
  //specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  dht.begin();
  timer.setInterval(1000L, sendSensor);

  attachInterrupt(digitalPinToInterrupt(2), notifyOnButtonPress, CHANGE);

  digitalWrite(relay1, OFF);
  digitalWrite(relay2, ON);
  digitalWrite(relay3, ON);
  digitalWrite(relay4, ON);
  digitalWrite(relay5, ON);
  digitalWrite(relay6, ON);
  digitalWrite(relay7, ON);
  digitalWrite(relay8, ON);
}
BLYNK_WRITE(V5)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay1, ON);
  } else {
    digitalWrite(relay1, OFF);
  }
}
BLYNK_WRITE(V6)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay2, ON);
  } else {
    digitalWrite(relay2, OFF);
  }
}
BLYNK_WRITE(V7)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay3, ON);
  } else {
    digitalWrite(relay3, OFF);
  }
}
BLYNK_WRITE(V8)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay4, ON);
  } else {
    digitalWrite(relay4, OFF);
  }
}


BLYNK_WRITE(V9)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay5, ON);
  } else {
    digitalWrite(relay5, OFF);
  }
}
BLYNK_WRITE(V10)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay6, ON);
  } else {
    digitalWrite(relay6, OFF);
  }
}
BLYNK_WRITE(V11)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay7, ON);
  } else {
    digitalWrite(relay7, OFF);
  }
}
BLYNK_WRITE(V12)
{
  int pinValue = param.asInt();

  if (pinValue == 1) {
    digitalWrite(relay8, ON);
  } else {
    digitalWrite(relay8, OFF);
  }
}
void loop()
{
  Blynk.run();
  timer.run();
}
