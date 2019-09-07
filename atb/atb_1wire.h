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
    @brief AVR Toolbox: 1-wire interface. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)
    @version 0.0.1

    Software realization of Atmel 1-wire interface.
*/

#ifndef __ATB_1WIRE
#define	__ATB_1WIRE


#include <util/delay.h>
#include <avr/io.h>


/* Defines and variables */


#define ATB_1WIRE_DDR   DDRB
#define ATB_1WIRE_PRT   PORTB
#define ATB_1WIRE_PIN   PINB
#define ATB_1WIRE_BIT   7


/* Functions */


uint8_t ATB_1wireLineReset();
uint8_t ATB_1wireLineRead();
void ATB_1wireLineWriteHi();
void ATB_1wireLineWriteLo();
uint8_t ATB_1wireReadByte();
void ATB_1wireWriteByte(uint8_t _byt);


#endif /* __ATB_1WIRE */

