#include <ArduinoJson.h>

int status;

char *createJsonSoil(int status);

void readSoilSensor() {
  status = digitalRead(HSOLO);
  Serial.print("Status do sensor: ");
  if (status == HIGH) {
    Serial.println("Desativado");
  } else {
    Serial.println("Ativado");
  }
  char *jsonSoilHum = createJsonSoil(!status);
  Serial.println(jsonSoilHum);
  MQTTClient.publish(TOPICO_HUM_SOLO, jsonSoilHum);
}

char *createJsonSoil(int status) {
  StaticJsonDocument<500> doc;
  doc["sensor"] = "SOIL";
  doc["typeSensor"] = "SoilHum";
  if (status == 0) {
    doc["reading"] = "baixa";
  } else {
    doc["reading"] = "alta";
  }

  char jsonSoil[256];
  serializeJson(doc, jsonSoil);

  return jsonSoil;
}