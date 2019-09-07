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
    @brief AVR Toolbox: HD44780 display driver. Configuration.
    @author Sergei Ivanov <ivanov@sndrz.xyz>
    @copyright The MIT License (MIT)
*/

#ifndef __ATB_HD44780_CONFIG
#define	__ATB_HD44780_CONFIG

/** Display connection mode: via 8 or 4 data wires. */
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

/* Check connection mode */
#ifdef ATB_HD44780_8BIT

    #define ATB_HD44780_INITMODE   0b00111000

#else
#ifdef ATB_HD44780_4BIT

    #define ATB_HD44780_INITMODE  0b00101000
    const uint8_t ATB_HD44780_DATMASK[4] = {1, 2, 4, 7};

#else
    #error "Define ATB_HD44780_4BIT or ATB_HD44780_8BIT for proper connection mode choose."
#endif
#endif
/* End of check connection mode */

#endif /* __ATB_HD44780_CONFIG */
