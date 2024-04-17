/**
 */
#include "Arduino.h"

#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>

#include "wifi_info.h"

// const char *ssid = "esp-webserver";
// const char *password = "password";

AsyncWebServer server(80);

const char *webpage = "";

char* read_file(String file_name) {
	File f = LittleFS.open(file_name, "r");
	if(!f) {
		Serial.println("Failed to open file for reading");
		return NULL;
	}
	char* b = (char*)malloc(f.size()+1);
	
	f.readBytes(b, f.size());
	f.close();
	return b;
}

void handle_root(AsyncWebServerRequest *request) {
  request->send(200, "text/html", webpage);
}

void not_found(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void get_rx(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", "HELLO WORLD!\r\n");
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  // Serial.println("Configuring access point...");

  // WiFi.softAP(ssid, password);
  // IPAddress myIP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(myIP);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
	  delay(500);
	  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if(!LittleFS.begin()) {
	  Serial.println("An Error has occurred while mounting LittleFS");
	  return;
  }

  webpage = read_file("index.html");

  if(WiFi.status() == WL_CONNECTED) {
	  if(MDNS.begin("esp8266")) {
		Serial.println("MDNS started");
	  }
  }

  server.on("/", HTTP_GET, handle_root);
  server.on("/rx", HTTP_GET, get_rx);
  server.onNotFound(not_found);

  server.begin();
  Serial.println("Server started");
}

void loop() {}
