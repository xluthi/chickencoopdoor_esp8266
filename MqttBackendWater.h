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

    MQTT backend for a pulse sensor counting water liter.
*/
#ifndef _MQTT_BACKEND_WATER_H_
#define _MQTT_BACKEND_WATER_H_

#include "MqttBackend.h"

#define MQTT_SENSOR_TOPIC "/house/sensors/water/city"

class MqttBackendWater: public MqttBackend {
  public:
    MqttBackendWater(WiFiClient& wifiClient);
    bool sendLiter(float value);
};

#endif
