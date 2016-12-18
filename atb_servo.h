/*
	AVR Toolbox
	Control servo motors.

	atb_servo.h

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

#ifndef __ATB_SERVO
#define __ATB_SERVO

    #include "atb_servo_motors.h"
    #include "atb_servo_hal.h"

    #ifndef ATB_SERVO_DDR
		#error No ATB_SERVO_DDR defined.
	#endif

	#ifndef ATB_SERVO_PRT
		#error No ATB_SERVO_PRT defined.
	#endif

    #ifndef ATB_SERVO_QUANTITY
        #error No ATB_SERVO_QUANTITY defined.
    #endif

	#ifndef ATB_SERVO_PULSE_PERIOD
		#define ATB_SERVO_PULSE_PERIOD	20
		#warning No ATB_SERVO_PULSE_PERIOD defined. Defalut value taken.
	#endif

	typedef struct {
		uint8_t pulse_min, pulse_max;
		uint8_t angle_max;
		uint16_t pulse_current;
		uint8_t pin;
	} atb_servo_motor, *atb_servo_motor_ptr;

	atb_servo_motor atb_servo_motors[ATB_SERVO_QUANTITY];
	atb_servo_motor_ptr atb_servo_pointers[ATB_SERVO_QUANTITY];

	void atb_servo_setup( uint8_t servo_id, uint8_t motor_pin,
						  uint8_t pulse_min, uint8_t pulse_max,
						  uint8_t angle_max );
	void atb_servo_set_angle( uint8_t servo_id, uint8_t angle );
	void atb_servo_timer_interrupt();
	void atb_servo_reorder();

#endif /* __ATB_SERVO */
