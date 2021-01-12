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

    The "include <BlynkSimpleEsp8266.h>" must be in the main ino file ONLY.
*/
#ifndef _MY_BLYNK_H_
#define _MY_BLYNK_H_

#define BLYNK_PRINT Serial
#include "MyDoor.h"

void my_blynk_setup();
void blynk_update_door_mode();
void blynk_update_door_action();

#endif
