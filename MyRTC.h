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
#ifndef _MY_RTC_H_
#define _MY_RTC_H_

#include <RTClib.h>
#include "FlashConfig.h"

#define MQTT_RTC_TOPIC "rtc"

class MyRTC {
  public:
    void setFlashConfig(FlashConfig *config);
    void setup();
    DateTime getNow();
    void setNow(DateTime dt);
    void setMqttNow(const char *iso8601DateTime);

  private:
    FlashConfig *config;
    RTC_DS1307 rtc;
};

#endif
