#include "WiFiconnection32.h"

WiFiconnection32::WiFiconnection32(const char* ssid, const char* password, int serverPort) :
  ssid_(ssid),
  password_(password),
  serverPort_(serverPort),
  server_(serverPort)
{
}

void WiFiconnection32::begin() {
  WiFi.softAP(ssid_, password_);
  IPAddress serverIP = WiFi.softAPIP();
  Serial.print("Server IP address: ");
  Serial.println(serverIP);
  server_.begin();
}

bool WiFiconnection32::isConnected() {
  return client_.connected();
}

bool WiFiconnection32::connectWiFi() {
  WiFi.begin(ssid_, password_);
  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 30) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    retryCount++;
  }
  return WiFi.status() == WL_CONNECTED;
}

bool WiFiconnection32::sendMessage(const char* message) {
  if (!isConnected()) {
    return false;
  }
  client_.println(message);
  return true;
}

bool WiFiconnection32::receiveMessage(String& message) {
  client_ = server_.available();
  if (client_) {
    if (client_.available()) {
      message = client_.readStringUntil('\n');
      message.trim();
      return true;
    }
  }
  return false;
}
