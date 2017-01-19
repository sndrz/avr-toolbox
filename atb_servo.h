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

/**
    @file
    @brief AVR Toolbox: Control servo motors. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright GNU GPL v.3

    Library allows to control several variuos (user defined) servo motors.
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

	/**
        A structure to keep settings of attached servo.
    */
	typedef struct {
		uint8_t pulse_min, pulse_max;   /**< Minimum and maximum servo pulse length for PWM. */
		uint8_t angle_max;              /**< Maximum servo angle possible. */
		uint16_t pulse_current;         /**< Current servo pulse length set. */
		uint8_t pin;                    /**< Pin number, where motor is connected. */
	} atb_servo_motor, *atb_servo_motor_ptr;

	atb_servo_motor atb_servo_motors[ATB_SERVO_QUANTITY];       /**< An array for attached servo motors. */
	atb_servo_motor_ptr atb_servo_pointers[ATB_SERVO_QUANTITY]; /**< Pointers to attached motors array items. */

	/**
        Configure and store parameters of a servo motor.

        @param[in] servo_id A servo ID from atb_servo_motors variable.
        @param[in] motor_pin A MCU I/O port pin number where servo control is connected.
        @param[in] pulse_min A pulse delay to set servo at minimun angle (ms).
        @param[in] pulse_max A pulse delay to set servo at maximum angle (ms).
        @param[in] angle_max Maximum angle range that servo can provide (degree).
	*/
	void atb_servo_setup( uint8_t servo_id, uint8_t motor_pin,
						  uint8_t pulse_min, uint8_t pulse_max,
						  uint8_t angle_max );

    /**
        Set angle (pulse length) for specified servo by degrees (from 0 - servo minimum
        to angle_max - servo maximum).

        @param[in] servo_id A servo ID from atb_servo_motors variable.
        @param[in] angle An angel to set (defgree).
    */
	void atb_servo_set_angle( uint8_t servo_id, uint8_t angle );

	/**
        A hook to be called from MCU timer interrupt.

        In definition of timer counter it will set level of motors pins hi or low
        by each servo current angle pulse length setting.
    */
	void atb_servo_timer_interrupt();

	/**
        Reorder servo motors by longest pulse length to shortest for
        atb_servo_timer_interrupt() correct run.
	*/
	void atb_servo_reorder();

#endif /* __ATB_SERVO */
