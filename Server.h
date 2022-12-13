#include <ESP8266WebServer.h>
#include "Sensor.h"
#include "Led.h"

ESP8266WebServer server(80);

void handle_root(){
  String form = "<form action=\"/DATA\" method=\"POST\">";
  form += "<button style=\"background: red; width:150px; color:white; font-size:15px;\" type=\"submit\">Switch</button>";
  form += "</form>";
  server.send(200, "text/html", form);
}

// void handleLED(){
//   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//   server.sendHeader("Location", "/");
//   server.send(303);
// }

void handleSensor(){
  sensor = !sensor;
  server.sendHeader("Location", "/");
  server.send(303);
  // server.send(200, "text/html", String(data));
}

void handleNotFound(){
  server.send(404, "text/plain", "NOT FOUND!");
}

void server_init(){
  sensor_init();
  server.on("/", HTTP_GET, handle_root);
  // server.on("/LED", HTTP_POST, handleLED);
  server.on("/DATA", HTTP_POST, handleSensor);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server started at port 80");
}
