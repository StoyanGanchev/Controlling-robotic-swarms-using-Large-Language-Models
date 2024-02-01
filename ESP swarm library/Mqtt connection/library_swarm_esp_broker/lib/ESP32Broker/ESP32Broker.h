#ifndef ESP32Broker_h
#define ESP32Broker_h

#include <WiFi.h>
#include <PubSubClient.h>

class ESP32Broker {
public:
  ESP32Broker();
  void setupBroker(const char* ssid, const char* password, const char* mqttBroker, int mqttPort);
  void loop();
  void publishMessage(const char* topic, const char* message);
  
private:
  WiFiServer wifiServer;
  WiFiClient wifiClient;
  PubSubClient mqttClient;
  const char* ssid;
  const char* password;
  const char* mqttBroker;
  int mqttPort;
  unsigned long lastPublishTime;
};

#endif
