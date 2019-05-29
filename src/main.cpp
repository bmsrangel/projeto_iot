#include "config/config.h"
#include "connection/mqtt.h"
#include "sensors/dht11.h"
#include "sensors/lightsensor.h"
#include "sensors/soil.h"
#include <Arduino.h>

unsigned long readTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  readTime = 0;
  delay(10);

  if (connectWiFi()) {
    startMQTT();
    startGPIO();
    initSensorDHT11();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(WIFI, LOW);
    if (!MQTTClient.connected()) {
      connectClientMQTT();
    }

    if (millis() > readTime + 6000) {
      readTime = millis();
      readSensorDHT11();
      readSoilSensor();
      readLightSensor();
    }

    MQTTClient.loop();
  } else {
    if (connectWiFi()) {
      startMQTT();
    }
  }
}