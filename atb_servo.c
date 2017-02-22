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
    @brief AVR Toolbox: Control servo motors. Code file.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A code for a library header file.
*/

#include "atb_servo.h"

void ATB_ServoSetup( uint8_t _servoId, uint8_t _motorPin,
                     uint8_t _pulseMin, uint8_t _pulseMax,
                     uint8_t _angleMax ) {

    ATB_servoMotors[_servoId].pin = _motorPin;
    ATB_servoMotors[_servoId].pulse_min = _pulseMin;
    ATB_servoMotors[_servoId].pulse_max = _pulseMax;
    ATB_servoMotors[_servoId].angle_max = _angleMax;
    ATB_servoMotors[_servoId].angleRatio = (_pulseMax - _pulseMin) * 10000 / _angleMax;

    ATB_servoPointers[_servoId] = &ATB_servoMotors[_servoId];

} /* ATB_ServoSetup */

void ATB_ServoSetAngle( uint8_t _servoId, uint8_t _angle ) {

    ATB_servoMotors[_servoId].pulse_current = ( _angle * ATB_servoMotors[_servoId].angleRatio ) +
                                                ATB_servoMotors[_servoId].pulse_min;

} /* ATB_ServoSetAngle */

void atb_servo_timer_interrupt() {

} /* function atb_servo_timer_interrupt */

void ATB_ServoReorder() {

    if (ATB_SERVO_QUANTITY <= 1) { return; }

    uint8_t _i;
    uint16_t _pulse[2];
    ATB_ServoMotorPtr _exchange;
    ATB_ServoMotor _temp;

    for (_i = 1; _i <= ATB_SERVO_QUANTITY-1; _i++) {

        _temp = *ATB_servoPointers[_i-1];
        _pulse[0] = _temp.pulse_current;
        _temp = *ATB_servoPointers[_i];
        _pulse[1] = _temp.pulse_current;

        if ( _pulse[0] > _pulse[1] ) {
            _exchange = ATB_servoPointers[_i-1];
            ATB_servoPointers[_i-1] = ATB_servoPointers[_i];
            ATB_servoPointers[_i] = _exchange;
        }

    } /*  for _i */

} /* ATB_ServoReorder */
