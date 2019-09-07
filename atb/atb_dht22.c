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
    @brief AVR Toolbox: DHT22 temperature/humidity sensor. Code file.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A code for a library header file.
*/

#include <util/delay.h>

#include "atb_dht22.h"
#include "atb_math.h"

void ATB_DHT22_Read() {

    /* Master pull the line to ground. */
    sbi(ATB_DHT22_DDR, ATB_DHT22_BIT);
    cbi(ATB_DHT22_PORT, ATB_DHT22_BIT);
    _delay_us(ATB_DHT22_US_MASTER_PULL);

    /* Master release the line (external resistor pull-up to VDD). */
    cbi(ATB_DHT22_DDR, ATB_DHT22_BIT);
    cbi(ATB_DHT22_PORT, ATB_DHT22_BIT);
    _delay_us(ATB_DHT22_US_MASTER_RELEASE);

    /* Sensor response by pulling the line to ground ... */
    _delay_us(ATB_DHT22_US_SLAVE_PULL);
    /* ... and release it after that. */
    _delay_us(ATB_DHT22_US_SLAVE_RELEASE);

    /* Sensor is now ready to send 40 bits of data. */

    uint8_t _i, _j; /* Counters. */
    uint8_t _byte; /* Temporary variable to receive a byte. */

    /* Wait for the first time slot begins with starting low. */
    _delay_us(ATB_DHT22_US_SLAVE_SLOT_START);

    /* Receive 5 bytes (40 bits) [HUM_HI, HUM_LOW, TEMP_HI, TEMP_LO, PARITY]. */
    for (_i = 0; _i <= 4; _i++) {

        _byte = 0x00; /* Clear a byte for receiving. */
        for (_j = 0; _j <= 7; _j++) {

            /* Jumping over the low slot timing to ensure to
               get into high time slot or next bit starting low ... */
            _delay_us(2 * ATB_DHT22_US_SLAVE_SLOT_LOW);

            /* ... if it is the high bit (line is pulled up) ... */
            if chb(ATB_DHT22_PIN, ATB_DHT22_BIT) {
                sbi(_byte, (7-_j)); /* Set a bit. */

                /* Wait for the rest of a bit slot time. */
                _delay_us(ATB_DHT22_US_SLAVE_SLOT_HIGH - 2*ATB_DHT22_US_SLAVE_SLOT_LOW);
                /* Skip next bit start marker. */
                _delay_us(ATB_DHT22_US_SLAVE_SLOT_START);

            /* ... or it was the low bit (line is pulled down). */
            } else {
                /* Wait for the rest of a starting slot time. */
                _delay_us(ATB_DHT22_US_SLAVE_SLOT_START - ATB_DHT22_US_SLAVE_SLOT_LOW);
            }
        } /* for _j */
        ATB_DHT22_dataBuffer[_i] = _byte;
    } /* for _i */
    /* Sensor release the line. */
    _delay_us(ATB_DHT22_US_SLAVE_PULL);

    /* Mask permanent zero bits to reduce errors. */
    ATB_DHT22_dataBuffer[0] &= 0x03;
    ATB_DHT22_dataBuffer[2] &= 0x83;

    /* Check parity bit. */
    uint8_t _parity;
    _parity = ATB_DHT22_dataBuffer[0] + ATB_DHT22_dataBuffer[1] +
              ATB_DHT22_dataBuffer[2] + ATB_DHT22_dataBuffer[3];

    ATB_DHT22_flagCorrupted = 0;
    /* Data corrupted. */
    if (_parity != ATB_DHT22_dataBuffer[4]) {
        ATB_DHT22_flagCorrupted = 1;
    }
}

float ATB_DHT22_GetFloatHumidity() {
    return (ATB_DHT22_dataBuffer[0] * 256 + ATB_DHT22_dataBuffer[1]) * 0.1;
}

float ATB_DHT22_GetFloatTemperature() {

    float _value;
    _value = ( (ATB_DHT22_dataBuffer[2] & 0x7F) * 256 + ATB_DHT22_dataBuffer[3] ) * 0.1;
    /* If negative temperature bit is present. */
    if chb(ATB_DHT22_dataBuffer[2], 7) {
        _value = -_value;
    }
    return _value;
}
