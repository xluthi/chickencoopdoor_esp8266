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

    State machine to model the door
*/
#ifndef _MY_DOOR_H_
#define _MY_DOOR_H_

#include "MyMotor.h"

typedef enum { NA, DOOR_CLOSED, DOOR_OPENED, DOOR_OPENING, DOOR_CLOSING} MyDoorState;
/* Door states:
 *
 * NA: We do not know, we'll have to guess, or perform a kind of "reset" action
 * CLOSED: the door is fully CLOSED
 * OPENED: the door is fully opened
 * OPENING: the door is currently being opened. Action is ongoing
 * CLOSING: the door is currently being closed. Action is ongoing.
*/

// MyDoorAction is the action requested by external controller (MQTT, RTC, button...) and not yet processed.
typedef enum { NONE, STOP, OPEN, CLOSE} MyDoorAction;

/* Door mode:
 *  - automatic: last action was controlled by RTC
 *  - manual: last action was controlled by MQTT or a button
 */
typedef enum { AUTOMATIC, MANUAL} MyDoorMode;

/* State of any switch: opened or closed
 *
 * In our setup, we have one switch at the top of the door which is closed when the
 * door is opened, and one at the bottom which is closed when the door is closed.
 */
typedef enum { S_CLOSED, S_OPENED } switchState;

class MyDoor {
  public:
    void setup();
    void open();
    void close();
    void stop();

    void loop();
    MyDoorState state;
    MyDoorAction action;
    MyDoorMode mode;
    switchState topSwitch;
    switchState bottomSwitch;

  private:
    MyMotor motor;
};

#endif
