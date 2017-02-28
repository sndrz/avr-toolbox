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

    ATB_servoMotors[_servoId].pulse_new = ( _angle * ATB_servoMotors[_servoId].angleRatio ) +
                                                ATB_servoMotors[_servoId].pulse_min;

} /* ATB_ServoSetAngle */

void ATB_ServoTimerInterrupt() {

    uint8_t _pulse, _i;
    _pulse = 0;

    if ( !(ATB_servoStatus & _BV(ATB_SERVO_STATUS_LOCK)) ) { /* Lock bit is down. */

        ATB_ServoReorder();
        ATB_servoStatus |= _BV(ATB_SERVO_STATUS_LOCK);
        _pulse = 1;

    } else { /* Lock bit is up. */

        for (_i = 0; _i <= ATB_SERVO_QUANTITY-1; _i++) {

            if (ATB_servoPointers[_i] != 0) {



            } /* if */

        } /* for _i */

    } /* if */

} /* ATB_ServoTimerInterrupt */

void ATB_ServoReorder() {

    if (ATB_SERVO_QUANTITY <= 1) { return; }

    uint8_t _i;
    uint16_t _pulse[2];
    ATB_ServoMotorPtr _exchange;
    ATB_ServoMotor _temp;

    for (_i = 0; _i <= ATB_SERVO_QUANTITY-1; _i++) {
        ATB_servoMotors[_i].pulse_current = ATB_servoMotors[_i].pulse_new;
    }

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

void ATB_ServoTimerSetup() {

    /* Set CTC (clear timer on compare match) mode. */
    TCCR1A &= ~_BV(COM1A1) & ~_BV(COM1A0) & ~_BV(WGM11) & ~_BV(WGM10);
    TCCR1B &= ~_BV(WGM13);
    TCCR1B |= _BV(WGM12);

    /* Set prescaler to 8. */
    TCCR1B &= ~_BV(CS12) & ~_BV(CS10);
    TCCR1B |= _BV(CS11);

    /* Enable timer interruption. */
    TIMSK |= _BV(OCIE1A);

} /* ATB_ServoTimerSetup */
