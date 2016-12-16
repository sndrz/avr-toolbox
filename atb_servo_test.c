/*
	AVR Toolbox
	Control servo motors.

	atb_servo_test.c

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

#define SERVO_COMMON_PULSE_MIN  1
#define SERVO_COMMON_PULSE_MAX  2
#define SERVO_COMMON_ANGLE_MAX  180

ISR(TIMER0_OVF_vect) {
    atb_servo_timer_interrupt();
}

int main() {

    atb_servo_setup(SERVO_1_ID, SERVO_1_PIN, SERVO_COMMON_PULSE_MIN, SERVO_COMMON_PULSE_MAX,
                    SERVO_COMMON_ANGLE_MAX);
    atb_servo_setup(SERVO_2_ID, SERVO_2_PIN, SERVO_COMMON_PULSE_MIN, SERVO_COMMON_PULSE_MAX,
                    SERVO_COMMON_ANGLE_MAX);

    atb_servo_set_angle(SERVO_1_ID, 20);
    atb_servo_set_angle(SERVO_1_ID, 160);

    atb_servo_timer_setup();

    sei();

    while(1) {

    } /* main loop */

    return 0;
} /* function main */
