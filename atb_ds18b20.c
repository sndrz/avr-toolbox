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
    @brief AVR Toolbox: DS18B20 temperature sensor. Code file.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A code for a library header file.
*/

#include "atb_ds18b20.h"

/** @todo Replace hardcoded address with ATB_ds18b20Adress[_id]. */
void ATB_DS18B20Convert(uint8_t _id) {

    ATB_1wireLineReset();
    ATB_1wireWriteByte(ATB_DS18B20_MATCH_ROM);
    ATB_1wireWriteByte(0x30);
    ATB_1wireWriteByte(0xC5);
    ATB_1wireWriteByte(0xB8);
    ATB_1wireWriteByte(ATB_DS18B20_CONVERT);

} /* ATB_DS18B20Convert */


void ATB_DS18B20ReadScratch(uint8_t _id) {

} /* ATB_DS18B20ReadScratch */

void ATB_DS18B20ScanAddress() {

} /* ATB_DS18B20ScanAddress */
