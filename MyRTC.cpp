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

    My own RTC class based on RTClib
*/
#include "MyRTC.h"

void MyRTC::setup(FlashConfig *config) {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  setFlashConfig(config);
}

void MyRTC::setFlashConfig(FlashConfig *config) {
  this->config = config;
  this->openingTime = this->config->getOpeningTime();
  this->closingTime = this->config->getClosingTime();
}

DateTime MyRTC::getNow() {
  return rtc.now();
}

void MyRTC::setNow(DateTime dt) {
  rtc.adjust(dt);
  //rtc.adjust(DateTime(2019, 7, 14, 19, 9, 0));
}

void MyRTC::setMqttNow(const char *iso8601DateTime) {
  rtc.adjust(DateTime(iso8601DateTime));
}

MyDoorAction MyRTC::getDesiredAction() {
  DateTime now = rtc.now();
  DateTime todayOpening = DateTime(now.year(), now.month(), now.day(),
    openingTime.hour(), openingTime.minute(), openingTime.second());
  DateTime todayClosing = DateTime(now.year(), now.month(), now.day(),
    closingTime.hour(), closingTime.minute(), closingTime.second());

  if (now > todayOpening && now < todayClosing) {
    return OPEN;
  } else {
    return CLOSE;
  }
}
