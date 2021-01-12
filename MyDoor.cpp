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

    My Door global object with one motor.
*/
#include <Arduino.h>
#include "MyDoor.h"

void MyDoor::setup() {
  Serial.println("MyDoor initialized, but nothing special to do so far...");
  state = NA;
  action = NONE;
  mode = AUTOMATIC;
  motor.setup();
}

void MyDoor::open() {
  action = OPEN;
}

void MyDoor::close() {
  action = CLOSE;
}

void MyDoor::stop() {
  action = STOP;
}

void MyDoor::loop() {
  switch(action) {
    case NONE:
    case STOP:
      motor.stop();
      if (state == DOOR_OPENING || state == DOOR_CLOSING) {
        state = NA;
      }
      return;

    case OPEN:
      if (state != DOOR_OPENED && topSwitch == S_OPENED) {
        motor.turn_ccw();
        state = DOOR_OPENING;
      } else {
        state = DOOR_OPENED;
        motor.stop();
      }
      return;

    case CLOSE:
      if (state != DOOR_CLOSED && bottomSwitch == S_OPENED) {
        motor.turn_cw();
        state = DOOR_CLOSING;
      } else {
        state = DOOR_CLOSED;
        motor.stop();
      }
      return;
  }
}
