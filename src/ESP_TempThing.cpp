#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Streaming.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "wificreds.h"
// Create a separate src/wificreds.h with the following (with actual values, of course):
// const char* ssid = "MY SSID";
// const char* password = "MY SUPERSECRET WIFI PASSWORD";

void handleLED();
void handleLEDon();
void handleLEDoff();
void handleRoot();
void handleTemp();
void handleNotFound();

// DS18B20 Temperature chip I/O
OneWire ds(12);
DallasTemperature sensors(&ds);
float tempC = 84.72;

String response = "";

MDNSResponder mdns;

ESP8266WebServer server(80);

const int led = 13;
const int led2 = 16;
bool state = 0;

void handleLED() {
  if(state == 0) {
    digitalWrite(led,1);
    digitalWrite(led2, 1);
    state = 1;
    server.send(200, "text/plain", "LED on!");
    digitalWrite(led, 0);
  }
  else {
    digitalWrite(led, 1);
    digitalWrite(led2, 0);
    state = 0;
    server.send(200, "text/plain", "LED off.");
    digitalWrite(led, 0);
  }
}

void handleLEDon() {
  digitalWrite(led,1);
  digitalWrite(led2,1);
  server.send(200, "text/plain", "1");
  digitalWrite(led,0);
}

void handleLEDoff() {
  digitalWrite(led, 1);
  digitalWrite(led2, 0);
  server.send(200, "text/plain", "0");
  digitalWrite(led, 0);
}

void handleRoot() {
  digitalWrite(led, 1);
  String message = "This is ESP1 - using the esp8266 platform for IoT (ugh).\n\n";
  message += "Now we're using PlatformIO to build/upload to the HUZZAH. Neat?\n";
  message += "To get the temperature where ESP1 is, GET /temp\n";
  message += "To toggle the red LED on the prototype, GET /led\n";
  message += "To turn the red LED on, GET /ledon\n";
  message += "To turn the red LED off, GET /ledoff\n\n";
  message += "There *might* be some other URIs to play with...\n";
  server.send(200, "text/plain", message);
  digitalWrite(led, 0);
}

void handleTemp() {
  digitalWrite(led,1);
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  response = "{\"temp\": "+String(tempC)+"}";
  server.send(200, "application/json", response);
  delay(200);
  //server.send(tempC);
  digitalWrite(led,0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "404\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led, 1);
  digitalWrite(led2, 0);
  // Tap the DS18B20 once. The first reading is ratty - 85C is unlikely to ever be the actual ambient temperature.
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp1", WiFi.localIP())) {
    Serial.println("MDNS responder started");

  }

  server.on("/", handleRoot);
  server.on("/temp", handleTemp);
  server.on("/led", handleLED);
  server.on("/ledon", handleLEDon);
  server.on("/ledoff", handleLEDoff);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(led, 0);
}

void loop(void){
  server.handleClient();
}
