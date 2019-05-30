#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "connection/wifi.h"
#include "topic.h"

PubSubClient MQTTClient(wifiClient);

void connectClientMQTT();
void startMQTT();
void callback(char *topic, byte *payload, unsigned int length);

void connectClientMQTT() {
  while (!MQTTClient.connected()) {
    Serial.println("Tentando conexão MQTT...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (MQTTClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("Conectado: " + clientId);

      MQTTClient.subscribe(TOPICO_BOMBA);
    } else {
      Serial.print("Falha na conexão. rc=");
      Serial.println(MQTTClient.state());
      Serial.println("Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void startMQTT() {
  MQTTClient.setServer(MQTT_SERVER, MQTT_PORT);
  MQTTClient.setCallback(callback);
}

void callback(char *topic, byte *payload, unsigned int length) {
  DynamicJsonDocument doc(512);

  DeserializationError err = deserializeJson(doc, payload);

  if (err) {
    Serial.print(F("deserializeJson() falhou com código "));
    Serial.println(err.c_str());
    return;
  }

  String msg = doc["bomba"];
  tratarTopico(topic, msg);
  serializeJson(doc, Serial);
}