#include <ArduinoJson.h>

int status;

bool readSoilSensor() {
  status = digitalRead(HSOLO);
  return status;
}