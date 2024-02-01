#ifndef WiFiconnection32_h
#define WiFiconnection32_h

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

class WiFiconnection32 {
  public:
    WiFiconnection32(const char* ssid, const char* password, int serverPort = 1234);
    void begin();
    bool isConnected();
    bool connectWiFi();
    bool sendMessage(const char* message);
    bool receiveMessage(String& message);

  private:
    const char* ssid_;
    const char* password_;
    int serverPort_;
    WiFiServer server_;
    WiFiClient client_;
};

#endif
