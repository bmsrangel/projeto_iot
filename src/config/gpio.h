#include <Arduino.h>

#define LDR A0
#define BOMBA D1
#define HUMTEMP D3
#define DHTTYPE DHT11
#define HSOLO D7
#define WIFI D4

void startGPIO() {
  pinMode(LDR, INPUT);
  pinMode(HUMTEMP, INPUT);
  pinMode(HSOLO, INPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(WIFI, OUTPUT);
  digitalWrite(BOMBA, HIGH);
  digitalWrite(WIFI, HIGH);
}