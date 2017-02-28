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
    @brief AVR Toolbox: Control servo motors. Test firmware.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A test program for servo motor functions.
    The MCU is atmega8, frequency is 8 MHz.
*/

#include "atb_servo.h"

/**
    A compare vector for timer interruption.
*/
ISR(TIMER1_COMPA_vect) {
    ATB_ServoTimerInterrupt();
}

int main() {

    ATB_ServoTimerSetup();

    /* Add some servo motors. */
    ATB_ServoSetup(0, SERVO_1_PIN, ATB_SERVO_MG90S_PULSE_MIN, ATB_SERVO_MG90S_PULSE_MAX,
                    ATB_SERVO_MG90S_ANGLE_MAX);
    ATB_ServoSetup(1, SERVO_2_PIN, ATB_SERVO_MG90S_PULSE_MIN, ATB_SERVO_MG90S_PULSE_MAX,
                    ATB_SERVO_MG90S_ANGLE_MAX);

    /* Set servo motors angles. */
    ATB_ServoSetAngle(0, 20);
    ATB_ServoSetAngle(1, 160);

    /* Enable global interruptions. */
    sei();

    while(1) {

    } /* main loop */

    return 0;
} /* function main */
