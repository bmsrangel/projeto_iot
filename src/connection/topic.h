#include <ArduinoJson.h>
#include "../config/gpio.h"

#define TOPICO_BOMBA "/projetoIoT"
#define TOPICO_TEMP "/projetoIoT/dht/temp"
#define TOPICO_HUM_DHT11 "/projetoIoT/dht/hum"
#define TOPICO_HUM_SOLO "/projetoIoT/soil"
#define TOPICO_LIGHT "/projetoIoT/light"
#define TOPICO_SENSORS "/projetoIoT/sensors"

int statusBomba = HIGH;

void tratarTopico(char *topic, String msg) {
  DynamicJsonDocument doc(512);

  DeserializationError err = deserializeJson(doc, msg);

  if (err) {
    Serial.print(F("Função deserializeJson() do tópico falhou com erro: "));
    Serial.println(err.c_str());
    return;
  }

  if (strcmp(topic, TOPICO_BOMBA) == 0) {
    if (doc["status"] == ("1")) {
      statusBomba = LOW;
    }
    if (doc["status"] == ("0")) {
      statusBomba = HIGH;
    }
  }

  // Serial.println();
  // Serial.print("Status da bomba: ");
  // if (statusBomba == HIGH) {
  //   Serial.println("Desligada");
  // } else {
  //   Serial.println("Ligada");
  // }

  digitalWrite(BOMBA, statusBomba);
}