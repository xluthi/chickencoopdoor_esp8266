/*
   Copyright (C) 2020 Xavier Lüthi

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

    Save and retrieve some configuration parameters in flash memory.
*/

#include "FlashConfig.h"

FlashConfig::FlashConfig() {
  config.magic = FLASH_CONFIG_MAGIC;
  address = 0;
}

void FlashConfig::setup() {
  EEPROM.begin(FLASH_CONFIG_SIZE);
  loadFromEeprom();
}

void FlashConfig::loadFromEeprom() {
    EEPROM.get(address,config);
    // Check if config has been already stored in EEPROM
    Serial.println("MAGIC number read in EEPROM : " + String(config.magic));
    if(config.magic != FLASH_CONFIG_MAGIC) {
      Serial.println("Config not initialised yet. Setting default values");
      // default values
      //strcpy(config.hostname, "ESP-SENSOR");
      sprintf(config.hostname, "ESP-%06X", ESP.getChipId());
      config.magic = FLASH_CONFIG_MAGIC;
      config.version=0;
      config.openingTime = DateTime(0,0,0,7 ,0,0); // default opening at 7AM
      config.closingTime = DateTime(0,0,0,20,0,0); // default closing at 8PM

      save();
    } else {
      Serial.println("Config read from EEPROM successfully");
      Serial.println(dumpConfig());
    }
}

void FlashConfig::save() {
  config.magic = FLASH_CONFIG_MAGIC;
  config.version++;
  EEPROM.put(address, config);
  EEPROM.commit();
}

String FlashConfig::dumpConfig() {
  String s;
  s += "Hostname: " + String(config.hostname) +
      ", Version: " + String(config.version) +
      ", opening time: ";
  char buffer[] = "hh:mm:ss";
  config.openingTime.toString(buffer);
  s += String(buffer) + ", closing time: ";
  config.closingTime.toString(buffer);
  s+= String(buffer);
  return s;
}

String  FlashConfig::getHostname() {
  return String(config.hostname);
}

void FlashConfig::setHostname(String h) {
  strcpy(config.hostname, h.c_str());
  save();
}

DateTime FlashConfig::getOpeningTime() {
  return config.openingTime;
}
DateTime FlashConfig::getClosingTime() {
  return config.closingTime;
}
void FlashConfig::setOpeningTime(DateTime dt) {
  config.openingTime = dt;
  save();
}
void FlashConfig::setClosingTime(DateTime dt) {
  config.closingTime = dt;
  save();
}
