#include <ArduinoJson.h>

int reading;

char *createJsonLight(int reading);

void readLightSensor() {
  reading = analogRead(LDR);
  Serial.print("Leitura do LDR: ");
  Serial.println(reading);

  char *jsonLight = createJsonLight(reading);
  Serial.println(jsonLight);
  MQTTClient.publish(TOPICO_LIGHT, jsonLight);
}

char *createJsonLight(int reading) {
  StaticJsonDocument<500> doc;
  doc["sensor"] = "LDR";
  doc["typeSensor"] = "Light";
  doc["reading"] = reading;

  char jsonLight[256];
  serializeJson(doc, jsonLight);

  return jsonLight;
}