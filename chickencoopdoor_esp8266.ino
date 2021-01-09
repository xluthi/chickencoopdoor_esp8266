/*
   (c) © 2018 Xavier Lüthi xavier@luthi.eu
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   See LICENSE.txt for the full license text.
*/
#include <ESP8266WiFi.h>
#include "private.h"
#include "MqttBackend.h"
#include "FlashConfig.h"
#include "MyMotor.h"
#include "MySwitch.h"
#include "MyDoor.h"
#include "MyRTC.h"

#define DEBUG
#include "xl_debug.h"

WiFiClient espClient;
MqttBackend mqttClient(espClient);
FlashConfig flashConfig;
MyRTC rtc;
MyDoor door;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  delay(10);
#endif

  flashConfig.setup();

  connectWifi(wifi_ssid, wifi_password, flashConfig.getHostname().c_str());
  mqttClient.setup(MQTT_SERVER_IP, MQTT_SERVER_PORT, flashConfig.getHostname());
  mqttClient.setFlashConfig(&flashConfig);
  rtc.setup(&flashConfig);
  mqttClient.setMyRTC(&rtc);
  door.setup();
  mqttClient.setMyDoor(&door);

  my_switches_setup();
}

void loop() {
  mqttClient.reconnect();
  mqttClient.loop();

  if (door.state == NA) {
    // Normally, it should never happen, but in case, we switch back to automatic mode
    door.mode = AUTOMATIC;
  }

  if (door.mode == MANUAL) {
    if (rtc.getDesiredAction() == OPEN && door.state == DOOR_OPENED) {
      door.mode == AUTOMATIC;
    } else if (rtc.getDesiredAction() == CLOSED && door.state == DOOR_CLOSED) {
      door.mode == AUTOMATIC;
    }
  }

  if (door.mode == AUTOMATIC) {
    if (rtc.getDesiredAction() == OPEN) {
      door.open();
    } else {
      door.close();
    }
  }

  door.loop();
}
