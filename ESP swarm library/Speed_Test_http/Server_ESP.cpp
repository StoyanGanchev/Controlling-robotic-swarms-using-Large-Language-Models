#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");

    server.on("/", HTTP_GET, []() {
        server.send(200, "text/plain", "Hello from ESP32 Server!");
        });

    server.begin();
}

void loop() {
    server.handleClient();
}
