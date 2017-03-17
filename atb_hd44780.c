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

#include "atb_hd44780.h"
#include "atb_macros.h"

void ATB_HD44780Init() {

	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_RW);
	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_RS);
	sbi(ATB_HD44780_CMD_DDR, ATB_HD44780_CMD_E);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
	cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);

	/* 8 bit LCD connection mode. */
	#ifdef ATB_HD44780_8BIT
		ATB_HD44780WriteCmd(0b00111000);

    /* 4 bit LCD connection mode. */
	#else
	#ifdef ATB_HD44780_4BIT
		ATB_HD44780WriteCmd(0b00101000);

	#else
		#error "Define ATB_HD44780_4BIT or ATB_HD44780_8BIT for proper connection mode choose."
	#endif
	#endif


	ATB_HD44780WriteCmd(0b00000001);	/* Clear display. */
	ATB_HD44780WriteCmd(0b00000110);	/* Forward / No scrolling. */
	ATB_HD44780WriteCmd(0b00001100);	/* Display ON. */

} /* ATB_HD44780Init */

void ATB_HD44780Wait() {

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

} /* ATB_HD44780Wait */

void ATB_HD44780WriteCmd(uint8_t _cmd) {
	ATB_HD44780Write(_cmd, 1);
} /* ATB_HD44780WriteCmd */

void ATB_HD44780WriteDat(uint8_t _dat) {
	ATB_HD44780Write(_dat, 0);
} /* ATB_HD44780WriteDat */

void ATB_HD44780Write(uint8_t _dat, uint8_t _cmd) {

	/* 8 bit LCD connection mode. */
	#ifdef ATB_HD44780_8BIT

		/* Prepare port. */
		ATB_HD44780_DAT_DDR = 0xff;

		/* Prepare command bits. */
		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
		if (_cmd == 1){
            cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
        } else {
            sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
        }

		/* Prepare data. */
		ATB_HD44780_DAT_PRT = _dat;
		_delay_ms(10);

		/* Commit transmission. */
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		ATB_HD44780Wait();

    /* 4 bit LCD connection mode. */
	#else
	#ifdef ATB_HD44780_4BIT

		/* Prepare port. */
		ATB_HD44780_DAT_DDR = (ATB_HD44780_DAT_DDR & 0b11100001) | 0b00011110;

		/* Prepare command bits. */
		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RW);
		if (_cmd == 1){
            cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
        } else {
            sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_RS);
        }

		/* Prepare 1-st part of data byte. */
		_delay_ms(100);
		ATB_HD44780_DAT_PRT = (ATB_HD44780_DAT_PRT & 0b11100001) | ( (_dat >> 3) & 0b00011110 );

		/* Commit transmission. */
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		/* ATB_HD44780Wait(); */
		_delay_ms(100);

		/* Prepare command bits. */
		sbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		_delay_ms(100);

		/* Prepare 2-st part of data byte. */
		ATB_HD44780_DAT_PRT = (ATB_HD44780_DAT_PRT & 0b11100001) | ( (_dat << 1) & 0b00011110);

		/* Commit transmission. */
		cbi(ATB_HD44780_CMD_PRT, ATB_HD44780_CMD_E);
		/* ATB_HD44780Wait(); */

	#endif /* ATB_HD44780_4BIT */
	#endif /* ATB_HD44780_8BIT */

} /* ATB_HD44780Write */
