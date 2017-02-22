/*
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/**
    @file
    @brief AVR Toolbox: Control servo motors. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

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
        A structure to keep settings of an attached servo.
    */
	typedef struct {
		uint8_t pulse_min, pulse_max;   /**< Minimum and maximum servo pulse length for PWM. */
		uint8_t angle_max;              /**< Maximum servo angle possible. */
		uint16_t angleRatio;
		uint16_t pulse_current;         /**< Current servo pulse length set. */
		uint8_t pin;                    /**< Pin number, where motor is connected. */
	} ATB_ServoMotor, *ATB_ServoMotorPtr;

	ATB_ServoMotor ATB_servoMotors[ATB_SERVO_QUANTITY];      /**< An array for attached servo motors. */
	ATB_ServoMotorPtr ATB_servoPointers[ATB_SERVO_QUANTITY]; /**< Pointers to attached motors array items. */

	/**
        Configure and store parameters of a servo motor.

        @param[in] _servoId A servo ID from atb_servo_motors variable.
        @param[in] _motorPin A MCU I/O port pin number where servo control is connected.
        @param[in] _pulseMin A pulse delay to set servo at minimun angle (ms).
        @param[in] _pulseMax A pulse delay to set servo at maximum angle (ms).
        @param[in] _angleMax Maximum angle range that servo can provide (degree).
	*/
	void ATB_ServoSetup( uint8_t _servoId, uint8_t _motorPin,
                         uint8_t _pulseMin, uint8_t _pulseMax,
						 uint8_t _angleMax );

    /**
        Set angle (pulse length) for specified servo by degrees (from 0 - servo minimum
        to angle_max - servo maximum).

        @param[in] _servoId A servo ID from atb_servo_motors variable.
        @param[in] _angle An angel to set (defgree).
    */
	void ATB_ServoSetAngle( uint8_t _servoId, uint8_t _angle );

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
	void ATB_ServoReorder();

#endif /* __ATB_SERVO */
