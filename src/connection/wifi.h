#include <ESP8266WiFi.h>

WiFiClient wifiClient;

boolean connectWiFi();

boolean connectWiFi() {
  wifiClient.stop();

  delay(500);

  Serial.println("Conectando-se à rede sem fio...");
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int contDelay = 0;
  while ((WiFi.status() != WL_CONNECTED) && (contDelay < 60)) {
    delay(1000);
    Serial.print(".");
    contDelay++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi não conectado");
    return false;
  }

  Serial.println("");
  Serial.println("Wifi conectado com sucesso!");
  Serial.print("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  return true;
}