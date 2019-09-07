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
#include "atb_math.h"


void ATB_ServoSetup( uint8_t _servoId, uint8_t _motorPin,
                     uint8_t _pulseMin, uint8_t _pulseMax,
                     uint8_t _angleMax ) {

    ATB_servoMotors[_servoId].pin = _motorPin;
    ATB_servoMotors[_servoId].pulse_min = _pulseMin;
    ATB_servoMotors[_servoId].pulse_max = _pulseMax;
    ATB_servoMotors[_servoId].angle_max = _angleMax;
    ATB_servoMotors[_servoId].angleRatio = (_pulseMax - _pulseMin) * 1000 / _angleMax;

    ATB_servoPointers[_servoId] = &ATB_servoMotors[_servoId];

    sbi(ATB_SERVO_DDR, _motorPin);
    cbi(ATB_SERVO_PRT, _motorPin);

} /* ATB_ServoSetup */


void ATB_ServoSetAngle( uint8_t _servoId, uint8_t _angle ) {

    ATB_servoMotors[_servoId].pulse_new = ( _angle * ATB_servoMotors[_servoId].angleRatio ) +
                                          ( ATB_servoMotors[_servoId].pulse_min * 1000 );

} /* ATB_ServoSetAngle */


void ATB_ServoTimerInterrupt() {

    if (ATB_servoPWMTimerCounter == 0) {

        if (ATB_servoPWMMotorCounter < ATB_SERVO_QUANTITY) {
            ATB_SERVO_PRT &= ~_BV((*ATB_servoPointers[ATB_servoPWMMotorCounter]).pin);
            ATB_servoPWMMotorCounter++;
        } else {
            ATB_servoPWMMotorCounter = 0;
        }
        ATB_ServoSetTimer();

    } else {
        ATB_servoPWMTimerCounter--;
    }

} /* ATB_ServoTimerInterrupt */


void ATB_ServoSetTimer() {

    uint32_t _temp;
    _temp = 0;

    if (ATB_servoPWMMotorCounter == 0) {

        _temp = (*ATB_servoPointers[0]).pulse;

        uint8_t _i;
        for (_i = 0; _i <= ATB_SERVO_QUANTITY-1; _i++) {
            sbi(ATB_SERVO_PRT, ATB_servoMotors[_i].pin);
        } /* for */

    } else if (ATB_servoPWMMotorCounter < ATB_SERVO_QUANTITY) {

        _temp = (*ATB_servoPointers[ATB_servoPWMMotorCounter]).pulse -
                           (*ATB_servoPointers[ATB_servoPWMMotorCounter-1]).pulse;

    } else if (ATB_servoPWMMotorCounter == ATB_SERVO_QUANTITY) {

        _temp = (ATB_SERVO_PULSE_PERIOD * 1000L ) -
                (*ATB_servoPointers[ATB_SERVO_QUANTITY-1]).pulse;
    }

    /**
        @todo Allow flexible F_CPU setting (it's hardcoded 8MHz for now).
        So minimum timer step is 1/8000000 * 256 * PRSC = 0,032 ms * PRSC.
        That settings are good with 8-bit counter variable and PRSC = 8.
        So one timer tick is 0,032 * 8 = 0,256 ms = 256 us.
    */
    ATB_servoPWMTimerCounter = _temp / 256;

} /* ATB_ServoSetTimer */


void ATB_ServoApply() {

    /* Disable timer interruption. */
    cbi(TIMSK, TOIE0);

    uint8_t _i, _j;
    ATB_ServoMotorPtr _exchange;

    /* Apply new pulses length (angles) to motors. */
    for (_i = 0; _i <= ATB_SERVO_QUANTITY-1; _i++) {
        ATB_servoMotors[_i].pulse = ATB_servoMotors[_i].pulse_new;
    } /* for _i */

    /* Do reorder from short pulses to long. */
    /** @todo Change "bubble" sorting method for something more. */
    _j = ATB_SERVO_QUANTITY;
    while (_j > 1) {
        for (_i = 0; _i <= _j-2; _i++) {
            if ( (*ATB_servoPointers[_i]).pulse > (*ATB_servoPointers[_i+1]).pulse ) {
                _exchange = ATB_servoPointers[_i];
                ATB_servoPointers[_i] = ATB_servoPointers[_i+1];
                ATB_servoPointers[_i+1] = _exchange;
            } /* if */
        } /*  for _i */
        _j--;
    } /* while */

    ATB_servoPWMMotorCounter = 0;
    ATB_ServoSetTimer();

    /* Enable timer interruption. */
    sbi(TIMSK, TOIE0);

} /* ATB_ServoApply */


void ATB_ServoAllStop() {

    /* Disable timer interruption. */
    cbi(TIMSK, TOIE0);

    uint8_t _i;
    for (_i = 0; _i <= ATB_SERVO_QUANTITY-1; _i++) {
        cbi(ATB_SERVO_PRT, ATB_servoMotors[_i].pin);
    } /* for */

} /* ATB_ServoAllStop */
