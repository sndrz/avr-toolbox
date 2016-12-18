/*
	AVR Toolbox
	Control servo motors.

	atb_servo.c

    Copyright (C) 2016-2017 Sergei Ivanov <nsndrz@hotmail.org>
*/

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "atb_servo.h"

void atb_servo_setup( uint8_t servo_id, uint8_t motor_pin,
                      uint8_t pulse_min, uint8_t pulse_max,
                      uint8_t angle_max ) {

    atb_servo_motors[servo_id].pin = motor_pin;
    atb_servo_motors[servo_id].pulse_min = pulse_min;
    atb_servo_motors[servo_id].pulse_max = pulse_max;
    atb_servo_motors[servo_id].angle_max = angle_max;

} /* function atb_servo_setup */

void atb_servo_set_angle( uint8_t servo_id, uint8_t angle ) {

    uint16_t angle_ratio = (atb_servo_motors[servo_id].pulse_max - atb_servo_motors[servo_id].pulse_min) *
                            10000 / atb_servo_motors[servo_id].angle_max;
    atb_servo_motors[servo_id].pulse_current = ( angle * angle_ratio ) +
                                                 atb_servo_motors[servo_id].pulse_min;

} /* function atb_servo_set_angle */

void atb_servo_timer_interrupt() {

} /* function atb_servo_timer_interrupt */

void atb_servo_reorder() {

}
