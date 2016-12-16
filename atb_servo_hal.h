/*
	AVR Toolbox
	Control servo motors.

	atb_servo_hal.h

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

#ifndef __ATB_SERVO_HAL
#define __ATB_SERVO_HAL

    #include <avr/interrupt.h>
    #include <avr/io.h>

	#define ATB_SERVO_DDR           DDRB
    #define ATB_SERVO_PRT           PORTB
    #define ATB_SERVO_QUANTITY      2
    #define ATB_SERVO_PULSE_DELAY   50

    #define SERVO_1_ID              0
    #define SERVO_1_PIN             0
    #define SERVO_2_ID              1
    #define SERVO_2_PIN             1

    void atb_servo_timer_setup() {};
	void atb_servo_timer_prescaler_set_pulse() {};
	void atb_servo_timer_prescaler_set_idle() {};

#endif /* __ATB_SERVO_HAL */
