#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>

DHT dht(HUMTEMP, DHTTYPE);

float humidity = 0.0, temperature = 0.0;

char *createJson(float temperature, float humidity);
boolean initSensorDHT11();
void readSensorDHT11();

boolean initSensorDHT11() {
  dht.begin();
  return true;
}

void readSensorDHT11() {
  humidity = dht.readHumidity();
  Serial.print("Umidade: ");
  Serial.println(humidity);

  temperature = dht.readTemperature();
  Serial.print("Temperatura: ");
  // Serial.println(temperature);
  Serial.println(String(temperature).c_str());
  char *jsonTempHum = createJson(temperature, humidity);
  Serial.println(jsonTempHum);
  MQTTClient.publish(TOPICO_TEMP, jsonTempHum);
  MQTTClient.publish(TOPICO_HUM_DHT11, String(humidity).c_str());
}

char *createJson(float temperature, float humidity) {
  StaticJsonDocument<500> doc;

  doc["sensor"] = "DHT11";
  doc["typeSensor"] = "TempHum";
  JsonArray readings = doc.createNestedArray("data");
  readings.add(temperature);
  readings.add(humidity);

  char json[256];
  serializeJson(doc, json);

  return json;
}