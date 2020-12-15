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
#ifndef _MY_MOTOR_H_
#define _MY_MOTOR_H_

#define motor1B D5
#define motor1A D3

class MyMotor {
  public:
    void setup();
    void turn_cw(int speed = 1023);
    void turn_ccw(int speed = 1023);
    void stop();
};

#endif
