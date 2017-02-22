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
    @brief AVR Toolbox: Control servo motors. HAL headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    Constants and variables to redefine for specified MCU and PCB.

    @note Feel free to edit this file for your needs.
*/

#ifndef __ATB_SERVO_HAL
#define __ATB_SERVO_HAL

    #include <avr/interrupt.h>
    #include <avr/io.h>

	#define ATB_SERVO_DDR           DDRB    /**< MCU DDR there servo motors are connected. */
    #define ATB_SERVO_PRT           PORTB   /**< MCU port there servo motors are connected. */
    #define ATB_SERVO_QUANTITY      2       /**< Quantity of connected servo motors. */

    /**
        PWM pulse period for servo motors.

        @todo Actually, different motors could have different PWM periods, so there is a need
        in possibility to mix ones somehow.
    */
    #define ATB_SERVO_PULSE_PERIOD  ATB_SERVO_MG90S_PULSE_PRIOD

    #define SERVO_1_ID              0
    #define SERVO_1_PIN             0
    #define SERVO_2_ID              1
    #define SERVO_2_PIN             1

    void atb_servo_timer_setup();
	void atb_servo_timer_prescaler_set_pulse();
	void atb_servo_timer_prescaler_set_idle();

#endif /* __ATB_SERVO_HAL */
