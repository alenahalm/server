#include "config.h"
#include "WiFi.h"
#include "Server.h"
#include "MQTT.h"
#include <SoftwareSerial.h>

#define ledPin 14

SoftwareSerial mySerial(5, 4);

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);

  pinMode(ledPin, OUTPUT);
  // // sensor_init();
  WiFi_init(false);
  server_init();
  MQTT_init();
  mqtt_cli.subscribe(String("esp8266BF15/DATA").c_str());
}

void loop() {
  mqtt_cli.loop();
  
  delay(1000);

  server.handleClient();
  int data = 0;
  if (sensor) {
    data = sensor_get_dist();
  } else {
    data = led_get_value();
  }
  mySerial.println(data);

  if (sensor) {
    if (cur < 20) {
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
  else {
  if (cur > maxNum) {
      maxNum = cur;
    }
    if (cur < maxNum/2) {
      digitalWrite(ledPin, HIGH);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
}