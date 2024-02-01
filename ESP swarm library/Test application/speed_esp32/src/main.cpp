#include <WiFi.h>

const char* ssid = "esp-wifi";
const char* password = "esp-wifi";  // Replace with your desired hotspot password

const int thermistorPin = 34; // Analog input pin for thermistor (GPIO 34 on ESP32)
int darkThreshold = 1000;     // Adjust this value based on your thermistor characteristics

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(thermistorPin, INPUT);

  WiFi.softAP(ssid, password); // Start ESP32 as a WiFi hotspot

  Serial.println("WiFi hotspot started!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  int thermistorValue = analogRead(thermistorPin);
  bool isDark = thermistorValue < darkThreshold;
  Serial.print("Thermistor value: ");
  Serial.println(thermistorValue);

  if (isDark) {
    Serial.println("Darkness detected. Sending 'on' to clients.");

    while (client) {
      // Send 'on' message to all connected clients
      client.print("on\n");

      // Move to the next client (if available)
      client = server.available();
    }
  } else {
    Serial.println("Light detected. Sending 'off' to clients.");

    while (client) {
      // Send 'off' message to all connected clients
      client.print("off\n");

      // Move to the next client (if available)
      client = server.available();
    }
  }

  // Add some delay to avoid excessive message sending
  delay(1000);
}
