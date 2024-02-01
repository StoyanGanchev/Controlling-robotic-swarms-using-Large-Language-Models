#include <ESP8266WiFi.h>

const char* ssid = "esp-wifi";
const char* password = "esp-wifi";
const char* serverIP = "192.168.4.1"; // Default IP for ESP32 in Access Point (hotspot) mode
const int serverPort = 80;             // Default port for HTTP

const int ledPin = 5; // GPIO 5 on ESP8266 (D1)

WiFiClient client;
void connectToServer() {
  while (!client.connected()) {
    Serial.println("Connecting to server...");

    if (client.connect(serverIP, serverPort)) {
      Serial.println("Connected to server.");
    } else {
      Serial.println("Connection failed. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  delay(1000);
  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  // Connect to the server when WiFi is connected
  connectToServer();
}



void loop() {
  if (!client.connected()) {
    // Attempt to reconnect if the connection is lost
    connectToServer();
  }

  // Listen for messages from the server
  if (client.available()) {
    String message = client.readStringUntil('\n');
    message.trim();

    Serial.print("Received Message: ");
    Serial.println(message);

    // Check the message and control the LED accordingly
    if (message == "on") {
      digitalWrite(ledPin, HIGH); // Turn on the LED
    } else if (message == "off") {
      digitalWrite(ledPin, LOW);  // Turn off the LED
    }
  }

  // Send heartbeat message every 5 seconds to keep the connection alive
  static unsigned long heartbeatTimer = millis();
  if (millis() - heartbeatTimer >= 5000) {
    heartbeatTimer = millis();
    client.print("Heartbeat\n");
  }
}
