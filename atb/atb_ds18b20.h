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
    @brief AVR Toolbox: DS18B20 temperature sensor. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)
    @version 0.0.1

    Library allows to control DS18B20 temperature sensors via 1-wire interface.
*/

#ifndef __ATB_DS18B20
#define	__ATB_DS18B20


#include "atb_1wire.h"


/* Defines and variables */


#define ATB_DS18B20_MATCH_ROM   0x55
#define ATB_DS18B20_CONVERT     0x44
#define ATB_DS18B20_READ_SCRCH  0xBE

#define ATB_DS18B20_SENSORS_QUANTITY    2
uint64_t ATB_ds18b20Address[ATB_DS18B20_SENSORS_QUANTITY];

uint8_t ATB_ds18b20ScratchBuffer[9];


/* Functions */


void ATB_DS18B20Convert(uint8_t _id);
void ATB_DS18B20ScanAddress();
void ATB_DS18B20ReadScratch(uint8_t _id);


#endif /* __ATB_DS18B20 */
