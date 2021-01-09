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

    My switch base functions
*/

#include "MySwitch.h"

void my_switches_setup() {
  pinMode(BOTTOM_SWITCH_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BOTTOM_SWITCH_PIN), my_switch_bottom_callback, CHANGE);

  pinMode(TOP_SWITCH_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(TOP_SWITCH_PIN), my_switch_top_callback, CHANGE);

  // init to current value
  my_switch_bottom_callback();
  my_switch_top_callback();

}

ICACHE_RAM_ATTR void my_switch_bottom_callback() {
  if (digitalRead(BOTTOM_SWITCH_PIN) == LOW) {
    door.bottomSwitch = S_CLOSED;
    Serial.println("Interupt for bottom switch: CLOSED");
  } else {
    door.bottomSwitch = S_OPENED;
    Serial.println("Interupt for bottom switch: OPENED");
  }
}

ICACHE_RAM_ATTR void my_switch_top_callback() {
  Serial.println("Interupt for top switch!");
  if (digitalRead(TOP_SWITCH_PIN) == LOW) {
    door.topSwitch = S_CLOSED;
  } else {
    door.topSwitch = S_OPENED;
  }
}
