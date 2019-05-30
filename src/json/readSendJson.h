#include <ArduinoJson.h>
#include "../connection/mqtt.h"
#include "../sensors/dht11.h"
#include "../sensors/lightsensor.h"
#include "../sensors/soil.h"

float tempHum[2];
float light;
bool soil;

void publishTopics() {
  const int capacity = JSON_ARRAY_SIZE(3) + 3 * JSON_OBJECT_SIZE(4);
  StaticJsonDocument<capacity> doc;
  JsonObject doc_dht = doc.createNestedObject();
  JsonObject doc_light = doc.createNestedObject();
  JsonObject doc_soil = doc.createNestedObject();

  readSensorDHT11(tempHum);
  light = readLightSensor();
  soil = readSoilSensor();

  // Serial.println(String(tempHum[0]).c_str());
  // Serial.println(String(tempHum[1]).c_str());
  // Serial.println(String(light).c_str());
  // Serial.println(String(soil).c_str());

  doc_dht["sensor"] = "DHT11";
  doc_dht["typeSensor"] = "TempHum";
  JsonArray readings = doc_dht.createNestedArray("data");
  readings.add(temperature);
  readings.add(humidity);

  doc_light["sensor"] = "LDR";
  doc_light["typeSensor"] = "Light";
  doc_light["data"] = light;

  doc_soil["sensor"] = "SOIL";
  doc_soil["typeSensor"] = "SoilHum";
  if (soil == 1) {
    doc_soil["data"] = "baixa";
  } else {
    doc_soil["data"] = "alta";
  }

  char json[256];
  serializeJson(doc, json);

  Serial.println(json);
  MQTTClient.publish(TOPICO_SENSORS, json);
}
