#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>

DHT dht(HUMTEMP, DHTTYPE);

float humidity = 0.0, temperature = 0.0;

boolean initSensorDHT11();
void readSensorDHT11();

boolean initSensorDHT11() {
  dht.begin();
  return true;
}

void readSensorDHT11(float tempHum[]) {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  tempHum[0] = temperature;
  tempHum[1] = humidity;
}