#include "WiFiconnection32.h"

const char* ssid = "SERVER_AP_SSID";
const char* password = "SERVER_AP_PASSWORD";

WiFiconnection32 wiFiConnection(ssid, password);

void setup() {
  Serial.begin(115200);
  wiFiConnection.begin();

  // Add your other setup code here
}

void loop() {
  // Handle communication
  if (wiFiConnection.isConnected()) {
    String receivedMessage;
    if (wiFiConnection.receiveMessage(receivedMessage)) {
      Serial.println("Received message: " + receivedMessage);
      // Add your code to process the received message here
    }
  }

  // Add your other loop tasks here

  delay(100); // Add a small delay for stability
}
