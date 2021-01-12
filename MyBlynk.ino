/*
   Copyright (C) 2021 Xavier Lüthi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Integration with the Blynk app (blynk.cc) to control the door via Internet
    and a smartphone app.

    List of virtual PIN used in the Blynk app:
     * V0: Switch to control door mode (automatic, manual)
     * V1: label to display door state (NA, OPENED, OPENING, CLOSED, CLOSING)
     * V2: Switch to control desired action (STOP, OPEN, CLOSED)
*/

#include "MyBlynk.h"

void my_blynk_setup(String hostname) {
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting (with Blynk) to ");
  Serial.println(wifi_ssid);

  WiFi.hostname(hostname.c_str());
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi_ssid, wifi_password, BLYNK_SERVER, BLYNK_PORT);

  Serial.println("WiFi connected (with Blynk)");
  Serial.println(getWifiInfo());

  /* VO : virtual switch to control door mode */
  Blynk.setProperty(V0, "onLabel", "MANUEL");
  Blynk.setProperty(V0, "offLabel", "AUTO");
  blynk_update_door_mode();
  blynk_update_door_action();
}

void blynk_update_door_mode() {
  Blynk.virtualWrite(V0, door.mode);
}

void blynk_update_door_action() {
  Blynk.virtualWrite(V2, door.action);
}

BLYNK_WRITE(V0) {
  int v = param.asInt();
  if (v == 1) {
    Serial.println("[Blynk] door mode set to MANUAL.");
    door.mode = MANUAL;
  } else {
    Serial.println("[Blynk] door mode set to AUTOMATIC.");
    door.mode = AUTOMATIC;
  }
}

BLYNK_WRITE(V2) {
  int v = param.asInt();
  switch (v) {
    case 1: // STOP
      door.stop();
      door.mode = MANUAL;
      Serial.println("[Blynk] door action set to STOP.");
      break;
    case 2: // OPEN
      door.open();
      door.mode = MANUAL;
      Serial.println("[Blynk] door action set to OPEN.");
      break;
    case 3: // CLOSE
      door.close();
      door.mode = MANUAL;
      Serial.println("[Blynk] door action set to CLOSE.");
      break;
    default:
    Serial.print("[Blynk] door action unknown: ");
    Serial.println(v);
  }
  blynk_update_door_mode();
}


BLYNK_READ(V1) {
  char buffer[20];
  switch (door.state) {
    case NA:
      strncpy(buffer, "NA", 20);
      break;
    case DOOR_CLOSED:
      strncpy(buffer, "DOOR CLOSED", 20);
      break;
    case DOOR_OPENED:
      strncpy(buffer, "DOOR OPENED", 20);
      break;
    case DOOR_OPENING:
      strncpy(buffer, "DOOR OPENING", 20);
      break;
    case DOOR_CLOSING:
      strncpy(buffer, "DOOR CLOSING", 20);
      break;
  }
  Blynk.virtualWrite(V1, buffer);
}
