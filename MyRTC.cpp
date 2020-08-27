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

void MyRTC::setup() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
}

void MyRTC::setFlashConfig(FlashConfig *config) {
  this->config = config;
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
