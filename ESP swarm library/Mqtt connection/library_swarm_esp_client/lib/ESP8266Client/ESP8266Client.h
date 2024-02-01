#ifndef ESP8266Client_h
#define ESP8266Client_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class ESP8266Client {
public:
  ESP8266Client();
  void setupClient(const char* ssid, const char* password, const char* mqttBroker, int mqttPort);
  void loop();
  void setMessageCallback(void (*callback)(char*, byte*, unsigned int));
  
private:
  WiFiClient wifiClient;
  PubSubClient mqttClient;
  const char* ssid;
  const char* password;
  const char* mqttBroker;
  int mqttPort;
};

#endif
