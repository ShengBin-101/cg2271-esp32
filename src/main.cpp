#include <Arduino.h>
#include <ESPmDNS.h>
#include <AsyncJson.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

#include "wifi_credentials.h"

#define BUILTIN_LED 2

#define RXD2 16
#define TXD2 17
const int output26 = 26;

AsyncWebServer server(80);

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

String redStatus = "OFF";
String greenStatus = "OFF";
String blueStatus = "OFF";

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(output26, HIGH);

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  if (!MDNS.begin("esp32")) {
    Serial.println("Error starting mDNS");
    return;
  }

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Routes to handle LED control via HTTP GET requests
  server.on("/redOn", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(output26, HIGH);
    redStatus = "ON";
    Serial.println("redOn");
    request->send(200, "text/plain", "RED LED ON");
  });

  server.on("/redOff", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(output26, LOW);
    redStatus = "OFF";
    Serial.println("redOff");
    request->send(200, "text/plain", "RED LED OFF");
  });

  server.on("/greenOn", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(output26, HIGH);
    greenStatus = "ON";
    Serial.println("greenOn");
    request->send(200, "text/plain", "GREEN LED ON");
  });

  server.on("/greenOff", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(output26, LOW);
    greenStatus = "OFF";
    Serial.println("greenOff");
    request->send(200, "text/plain", "GREEN LED OFF");
  });

  server.on("/blueOn", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(output26, HIGH);
    blueStatus = "ON";
    Serial.println("blueOn");
    request->send(200, "text/plain", "BLUE LED ON");
  });

  server.on("/blueOff", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(output26, LOW);
    blueStatus = "OFF";
    Serial.println("blueOff");
    request->send(200, "text/plain", "BLUE LED OFF");
  });

  server.begin();
}

void loop() {
  // No need to handle clients manually, AsyncWebServer handles it
}