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
    @brief AVR Toolbox: DHT22 temperature/humidity sensor. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)
    @version 0.1.0

    Library allows to control LCD displays with HD44780 controller.
*/

#ifndef __ATB_DHT22
#define __ATB_DHT22

#include <avr/io.h>

#define ATB_DHT22_PORT  PORTC
#define ATB_DHT22_DDR   DDRC
#define ATB_DHT22_PIN   PINC
#define ATB_DHT22_BIT   4

#define ATB_DHT22_US_MASTER_PULL        1000
#define ATB_DHT22_US_MASTER_RELEASE     30
#define ATB_DHT22_US_SLAVE_PULL         80
#define ATB_DHT22_US_SLAVE_RELEASE      80
#define ATB_DHT22_US_SLAVE_SLOT_START   50
#define ATB_DHT22_US_SLAVE_SLOT_LOW     25
#define ATB_DHT22_US_SLAVE_SLOT_HIGH    70

uint8_t ATB_DHT22_dataBuffer[5];
uint8_t ATB_DHT22_flagCorrupted;

/**
    @note Sequence is working only with -03 optimization level.
*/
void ATB_DHT22_Read();

float ATB_DHT22_GetFloatHumidity();
float ATB_DHT22_GetFloatTemperature();

#endif /* __ATB_DHT22 */
