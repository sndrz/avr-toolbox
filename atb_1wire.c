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
    @brief AVR Toolbox: 1-wire interface. Code file.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A code for a library header file.
*/

#include "atb_1wire.h"
#include "atb_macros.h"

uint8_t ATB_1wireLineReset() {

    cbi(ATB_1WIRE_PRT, ATB_1WIRE_BIT);
    sbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(480);
    cbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(60);
    _delay_ms(30);

    if (chb(ATB_1WIRE_PIN, ATB_1WIRE_BIT)) {
        return 0;
    } else {
        return 1;
    } /* if */

    _delay_ms(30);

} /* ATB_1wireLineReset */

uint8_t ATB_1wireLineRead() {

    cbi(ATB_1WIRE_PRT, ATB_1WIRE_BIT);
    sbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(15);
    cbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(15);

    if (chb(ATB_1WIRE_PIN, ATB_1WIRE_BIT)) {
        return 1;
    } else {
        return 0;
    } /* if */

    _delay_ms(30);

} /* ATB_1wireLineRead */

void ATB_1wireLineWriteHi() {

    cbi(ATB_1WIRE_PRT, ATB_1WIRE_BIT);
    sbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(15);
    cbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(45);

} /* ATB_1wireLineWriteHi */

void ATB_1wireLineWriteLo() {

    cbi(ATB_1WIRE_PRT, ATB_1WIRE_BIT);
    sbi(ATB_1WIRE_DDR, ATB_1WIRE_BIT);
    _delay_ms(60);

} /* ATB_1wireLineWriteLo */

uint8_t ATB_1wireReadByte() {

} /* ATB_1wireReadByte */

void ATB_1wireWriteByte(uint8_t _byt) {

    uint8_t _i;
    for (_i = 0; _i <= 7; _i++) {

        if (chb(_byt, _i)) {
            ATB_1wireLineWriteHi();
        } else {
            ATB_1wireLineWriteLo();
        }

    } /* for _i */

} /* ATB_1wireWriteByte */
