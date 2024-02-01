#include <ESP8266Client.h>

// Replace these values with your Wi-Fi credentials and MQTT broker details
const char* client_ssid = "wifi ssid";
const char* client_password = "wifi password";
const char* client_mqttBroker = "ip of the mqtt broker";
int client_mqttPort = 1883;

ESP8266Client client;

void messageReceived(char* topic, byte* payload, unsigned int length) {
  // The messageReceived callback implementation
}

void setup() {
  Serial.begin(115200);
  client.setupClient(client_ssid, client_password, client_mqttBroker, client_mqttPort);
  client.setMessageCallback(messageReceived);
}

void loop() {
  client.loop();
  clien
  delay(5000);
}
