/**
 */
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>


// const char *ssid = "esp-webserver";
// const char *password = "password";

const char *ssid = "gnutard";
const char *password = "compiledwithgcc";

AsyncWebServer server(80);

const char *webpage =
	"<!DOCTYPE html>"
	"<html>"
	"<body>"
		"<h1>ESP WiFi Serial</h1>"
		"<div class=\"message-text\" contentEditable>""</div>"
	"</body>"
	"</html>"
	;

void handle_root(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", webpage);
}

void not_found(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
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

  if(WiFi.status() == WL_CONNECTED) {
	  if(MDNS.begin("esp8266")) {
		Serial.println("MDNS started");
	  }
  }

  server.on("/", handle_root);
  server.onNotFound(not_found);

  server.begin();
  Serial.println("Server started");
}

void loop() {}
