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
    @brief AVR Toolbox: HD44780 display driver. Headers.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    Library allows to control LCD displays with HD44780 controller.
*/

#ifndef __ATB_HD44780
#define	__ATB_HD44780

    #include <util/delay.h>
    #include <avr/io.h>

    #define ATB_HD44780_8BIT
    /* #define ATB_HD44780_4BIT */

    #define ATB_HD44780_LANES   2
    #define ATB_HD44780_DIGITS  16

    #define ATB_HD44780_DAT_PRT     PORTD
    #define ATB_HD44780_DAT_DDR     DDRD
    #define	ATB_HD44780_DAT_PIN	    PIND
    #define ATB_HD44780_CMD_PRT	    PORTC
    #define ATB_HD44780_CMD_DDR	    DDRC

    #define ATB_HD44780_CMD_RS  	1
    #define ATB_HD44780_CMD_RW	    2
    #define ATB_HD44780_CMD_E	    3

    void ATB_HD44780Wait();
    void ATB_HD44780Init();
    void ATB_HD44780WriteDat(uint8_t _dat);
    void ATB_HD44780WriteCmd(uint8_t _cmd);
    void ATB_HD44780Write(uint8_t _byt, uint8_t _isCmd);
    void ATB_HD44780Print(char _string[]);
    void ATB_HD44780SetCursor(uint8_t _lin, uint8_t _pos);

#endif /* __ATB_HD44780 */
