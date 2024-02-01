#include <ESP32Broker.h>

// Replace these values with your Wi-Fi credentials and MQTT broker details
const char* ssid = "ssid of wifi";
const char* password = "wifi password";
const char* mqttBroker = "broker ip";
int mqttPort = 1883;

ESP32Broker broker;

void setup() {
  Serial.begin(115200);
  broker.setupBroker(ssid, password, mqttBroker, mqttPort);
}

void loop() {
  broker.loop();
  delay(5000);
}
