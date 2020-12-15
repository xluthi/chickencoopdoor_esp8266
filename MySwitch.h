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

    My own Switch
*/
#ifndef _MY_SWITCH_H_
#define _MY_SWITCH_H_

#define BOTTOM_SWITCH_PIN D6
#define TOP_SWITCH_PIN D7 //??

extern MyDoor door;

void my_switches_setup();
ICACHE_RAM_ATTR void my_switch_bottom_callback();
ICACHE_RAM_ATTR void my_switch_top_callback();

#endif
