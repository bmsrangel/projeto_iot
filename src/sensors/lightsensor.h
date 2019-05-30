#include <ArduinoJson.h>

int reading;

char *createJsonLight(int reading);

int readLightSensor() {
  reading = analogRead(LDR);
  return reading;
}