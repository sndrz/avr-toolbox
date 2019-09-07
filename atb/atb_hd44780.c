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
    @brief AVR Toolbox: HD44780 display driver. Code file.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A code for a library header file.
*/

#include <util/delay.h>
#include <string.h>

#include "atb_hd44780.h"
#include "atb_math.h"

void ATB_HD44780Init() {

	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_RW);
	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_RS);
	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_E);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);

	ATB_HD44780WriteCmd(ATB_HD44780_INITMODE);
	ATB_HD44780WriteCmd(0b00000001);	/* Clear display. */
	ATB_HD44780WriteCmd(0b00000110);	/* Forward / No scrolling. */
	ATB_HD44780WriteCmd(0b00001100);	/* Display ON. */

} /* ATB_HD44780Init */

void _ATB_HD44780Wait() {

	uint8_t _pin = 0x00;

	while ( chb(_pin, 7) ){
		ATB_HD44780_DAT_DDR = 0x00;
		ATB_HD44780_DAT_PRT = 0xff;

		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		_delay_ms(10);
		_pin = ATB_HD44780_DAT_PIN;
		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
	}

} /* _ATB_HD44780Wait */

void ATB_HD44780WriteCmd(uint8_t _cmd) {
    _ATB_HD44780Write(_cmd, 1);
} /* ATB_HD44780WriteCmd */

void ATB_HD44780WriteDat(uint8_t _dat) {
    _ATB_HD44780Write(_dat, 0);
} /* ATB_HD44780WriteDat */

#ifdef ATB_HD44780_8BIT
void _ATB_HD44780Write(uint8_t _byt, uint8_t _isCmd) {

    /* Prepare port. */
    ATB_HD44780_DAT_DDR = 0xff;

    /* Prepare command bits. */
    sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
    if (_isCmd == 1){
        cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
    } else {
        sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
    }

    /* Prepare data. */
    ATB_HD44780_DAT_PRT = _byt;
    _delay_ms(10);

    /* Commit transmission. */
    cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    /* _ATB_HD44780Wait(); */

} /* _ATB_HD44780Write */
#endif /* ATB_HD44780_8BIT */

#ifdef ATB_HD44780_4BIT
void _ATB_HD44780Write(uint8_t _byt, uint8_t _isCmd) {

    uint8_t _mask, _i;

    /* Prepare port. */
    for (_i = 0; _i < 4; _i++) {
        sbi(ATB_HD44780_DAT_DDR, ATB_HD44780_DATMASK[_i]);
    }

    /* Prepare command bits. */
    sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
    if (_isCmd == 1){
        cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
    } else {
        sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
    }

    /** @todo Mask applying does not work! */
    /* Prepare 1-st part of data byte. */
    _delay_ms(100);

    _mask = _byt;
    cym(_mask, 0xf0);
    sym(ATB_HD44780_DAT_PRT, _mask);

    /* Commit transmission. */
    cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    /* ATB_HD44780Wait(); */
    _delay_ms(100);

    /* Prepare command bits. */
    sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    _delay_ms(100);

    /* Prepare 2-st part of data byte. */
    _mask = _byt;
    cym(_mask, 0x0f);
    sym(ATB_HD44780_DAT_PRT, _mask);

    /* Commit transmission. */
    cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
    /* ATB_HD44780Wait(); */

} /* _ATB_HD44780Write */
#endif /* ATB_HD44780_4BIT */

void ATB_HD44780_PrintString(char* _string) {

    while ( (*_string) != '\0') {
        ATB_HD44780WriteDat( (*_string) );
        _string++;
    }
} /* ATB_HD44780_PrintString */

void ATB_HD44780_PrintLine(char _string[], uint8_t _line) {
    char _str[ATB_HD44780_DIGITS+1];
    uint8_t _i, _j;
    int _position_start, _position_end;

    if ((_line > 0) && (_line <= ATB_HD44780_LANES)) {

        _position_start = (ATB_HD44780_DIGITS / 2) - (strlen(_string) / 2);
        if (_position_start <= 0) {
            _position_start = 0;
            _position_end = ATB_HD44780_DIGITS - 1;
        } else {
            _position_end = _position_start + strlen(_string) - 1;
        }

        _j = 0;
        for (_i = 0; _i < ATB_HD44780_DIGITS; _i++) {
            if ( (_i >= _position_start) && (_i <= _position_end ) ) {
                _str[_i] = _string[_j];
                _j++;
            } else {
                _str[_i] = ' ';
            }
        }
        _str[ATB_HD44780_DIGITS] = '\0';

        ATB_HD44780SetCursor(_line, 0);
        ATB_HD44780_PrintString(_str);

    }
} /* ATB_HD44780_PrintLine */

void _ATB_HD44780PrintByte(uint8_t _byte) {
    uint8_t _i;
    /** @todo I don't get why it isn't work with 7 to 0 oder. So I use (7-_i). */
    for (_i = 0; _i <= 7; _i++) {
        if chb(_byte, (7-_i)) {
            ATB_HD44780WriteDat('1');
        } else {
            ATB_HD44780WriteDat('0');
        }
    } /* for _i */
}

void ATB_HD44780SetCursor(uint8_t _lin, uint8_t _pos) {

    uint8_t _addr;
    _addr = 0x00; /* Display has one line. */

    if (_lin == 2) { _addr = 0x40; }
    _addr += _pos;

    sbi(_addr, 7);
    ATB_HD44780WriteCmd(_addr);

} /* ATB_HD44780SetCursor */
