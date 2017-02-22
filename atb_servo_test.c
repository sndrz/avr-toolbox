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
*/



#include "atb_servo.h"

/**
    An overflow vector for timer interruption.
*/
ISR(TIMER0_OVF_vect) {
    ATB_ServoReorder();
    atb_servo_timer_interrupt();
}

int main() {

    /* Add some servo motors. */
    ATB_ServoSetup(SERVO_1_ID, SERVO_1_PIN, ATB_SERVO_MG90S_PULSE_MIN, ATB_SERVO_MG90S_PULSE_MAX,
                    ATB_SERVO_MG90S_ANGLE_MAX);
    ATB_ServoSetup(SERVO_2_ID, SERVO_2_PIN, ATB_SERVO_MG90S_PULSE_MIN, ATB_SERVO_MG90S_PULSE_MAX,
                    ATB_SERVO_MG90S_ANGLE_MAX);

    /* Set servo motors angles. */
    ATB_ServoSetAngle(SERVO_1_ID, 20);
    ATB_ServoSetAngle(SERVO_1_ID, 160);

    sei();

    while(1) {

    } /* main loop */

    return 0;
} /* function main */
