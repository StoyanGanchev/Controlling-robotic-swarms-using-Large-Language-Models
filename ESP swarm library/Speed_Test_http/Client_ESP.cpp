#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

const char* serverName = "http://esp32_server_ip/";

unsigned long startTime;
unsigned long endTime;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
}

void loop() {
    if ((WiFi.status() == WL_CONNECTED)) {
        HTTPClient http;

        http.begin(serverName);

        startTime = millis();
        int httpResponseCode = http.GET();
        endTime = millis();

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(response);
            Serial.print("Round-trip time: ");
            Serial.print(endTime - startTime);
            Serial.println(" ms");
        }
        else {
            Serial.print("Error on sending GET: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }
    delay(10000); // Wait for 10 seconds between each request
}
