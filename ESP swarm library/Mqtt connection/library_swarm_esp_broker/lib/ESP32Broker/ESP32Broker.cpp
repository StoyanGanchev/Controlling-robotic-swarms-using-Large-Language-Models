#include "ESP32Broker.h"

ESP32Broker::ESP32Broker() : mqttClient(wifiClient) {
  // Initialize variables
}

void ESP32Broker::setupBroker(const char* ssid, const char* password, const char* mqttBroker, int mqttPort) {
  this->ssid = ssid;
  this->password = password;
  this->mqttBroker = mqttBroker;
  this->mqttPort = mqttPort;

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());
  
  wifiServer.begin();

  mqttClient.setServer(mqttBroker, mqttPort);
    Serial.println("MQTT server set");

}

void ESP32Broker::loop() {
  WiFiClient newClient = wifiServer.available();
  Serial.println("Waiting for new found client");
  if (newClient) {
    Serial.println("New client connected");
    wifiClient = newClient;
    mqttClient.setClient(wifiClient);
  }

  if (!mqttClient.connected()) {
    Serial.println("ERROR");
   Serial.println(mqttClient.state());
    if (mqttClient.connect("ESP32Broker")) {  //error
      Serial.println("Connected to MQTT broker");
    }
  }

  mqttClient.loop();

  // Publish a message every 5 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - lastPublishTime >= 5000) {
    lastPublishTime = currentMillis;
    publishMessage("topic/test", "Hello from broker!");
  }
}

void ESP32Broker::publishMessage(const char* topic, const char* message) {
  mqttClient.publish(topic, message);
}
