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

    My DC motor controlled by a L9110S controller
*/
#include <Arduino.h>
#include "MyMotor.h"

void MyMotor::setup() {
  Serial.println("MyMotor initialized, but nothing special to do so far...");
}

void MyMotor::turn_cw(int speed) {
  analogWrite(motor1A, speed);
  analogWrite(motor1B, 0);
}
void MyMotor::turn_ccw(int speed) {
  analogWrite(motor1A, 0);
  analogWrite(motor1B, speed);
}
void MyMotor::stop() {
  analogWrite(motor1A, 0);
  analogWrite(motor1B, 0);

}
