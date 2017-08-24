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

    Library allows to control several various (user defined) servo motors.
*/

#ifndef __ATB_SERVO
#define __ATB_SERVO

#include <avr/interrupt.h>
#include <avr/io.h>
#include "atb_servo_motors.h"


/* Defines and variables */


/** PWM pulse period for servo motors.
    @todo Actually, different motors could have different PWM periods, so there is a need
    in possibility to mix ones somehow.
*/
#define ATB_SERVO_PULSE_PERIOD  ATB_SERVO_MG90S_PULSE_PRIOD

/** Quantity of connected servo motors. */
#define ATB_SERVO_QUANTITY      3

/** Servos to MCU connection settings.
    @todo Allow to connect servos to different ports.
*/
#define ATB_SERVO_DDR           DDRB
#define ATB_SERVO_PRT           PORTB
#define SERVO_1_PIN             0
#define SERVO_2_PIN             1
#define SERVO_3_PIN             2


/** A structure to keep settings of an attached servo. */
typedef struct {
    uint8_t pulse_min, pulse_max;   /**< Minimum and maximum servo pulse length for PWM. */
    uint8_t angle_max;              /**< Maximum servo angle possible. */
    uint16_t angleRatio;            /**< A ratio to convert angle (degrees) to pulse (us). */
    uint16_t pulse;                 /**< Current servo pulse length set. */
    uint16_t pulse_new;             /**< New servo pulse length to update. */
    uint8_t pin;                    /**< Pin number, where motor is connected. */
} ATB_ServoMotor, *ATB_ServoMotorPtr;

/** An array for attached servo motors. */
ATB_ServoMotor ATB_servoMotors[ATB_SERVO_QUANTITY];

/** Pointers to attached motors array items. */
ATB_ServoMotorPtr ATB_servoPointers[ATB_SERVO_QUANTITY];


uint8_t ATB_servoPWMMotorCounter;
uint8_t ATB_servoPWMTime;
uint16_t ATB_servoPWMTimerCounter;


/* Functions */


/**
    Configure and store parameters of a servo motor.

    @param[in] _servoId A servo ID from atb_servo_motors variable.
    @param[in] _motorPin A MCU I/O port pin number where servo control is connected.
    @param[in] _pulseMin A pulse delay to set servo at minimun angle (ms).
    @param[in] _pulseMax A pulse delay to set servo at maximum angle (ms).
    @param[in] _angleMax Maximum angle range that servo can provide (degree).
    @note pulse_min, pulse_max and angle_ratio variables store values
    in microseconds (us) multipled by 10 to save a fractional part of time period.
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
void ATB_ServoTimerInterrupt();

/**
    Reorder servo motors by shortest pulse length to longest for
    atb_servo_timer_interrupt() correct run.
*/
void ATB_ServoApply();

void ATB_ServoAllStop();

void ATB_ServoSetTimer();

#endif /* __ATB_SERVO */
