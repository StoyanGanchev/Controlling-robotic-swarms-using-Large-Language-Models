# Espressif microcontroller library for controlling swarms

## Overview
This project demonstrates the capabilities of ESP32, ESP8266 and ESP12 microcontrollers in establishing network connections and communicating over MQTT and HTTP protocols. It includes libraries for setting up MQTT and HTTP connections between ESP32 devices, code for testing the speed of HTTP connections using two ESP32s, and test applications that leverage these libraries to create real-world examples of inter-ESP communication between the participants of a swarm.


### 1. MQTT Connection Folder
This folder contains the library required for establishing MQTT connections between ESP devices. It includes the necessary code to set up an MQTT broker and clients.

- **/mqtt_connection/**
  - Code to set up an ESP32 as an MQTT broker.
  - Example code for configuring an ESP32 as an MQTT client.

### 2. HTTP Connection Folder
This folder holds the library for setting up HTTP connections. It's useful for scenarios where ESPs need to communicate via HTTP requests.

- **/http_connection/**
  - Initializes an ESP32 as an HTTP server.
  - Configures an ESP32 as an HTTP client.

### 3. HTTP Speed Test Code
A specialized set of scripts designed to measure the speed of HTTP connections between two ESP32 devices.

- **/http_speed_test/**
  - Code for the ESP32 acting as the HTTP server.
  - Code for the ESP32 acting as the HTTP client to test the connection speed.

### 4. Test Applications
Example applications that use the MQTT and HTTP libraries to demonstrate real-world uses of ESP-to-ESP communication.

## Getting Started
Make sure to modify the network credentials and other settings in the code according to your local setup.


