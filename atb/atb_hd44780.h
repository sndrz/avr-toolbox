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
    @version 0.1.0

    Library allows to control LCD displays with HD44780 controller.
*/

/*  Configuration note
    DO NOT FORGET to edit atb_hd44780_config.h.
*/

#ifndef __ATB_HD44780
#define	__ATB_HD44780

#include <avr/io.h>

#include "atb_hd44780_config.h"

/* Functions */

/** Wait until display is not busy. */
void _ATB_HD44780Wait();

/** Prepare display for work. */
void ATB_HD44780Init();

/** Send data command to display. */
void ATB_HD44780WriteDat(uint8_t _dat);

/** Send control command to display. */
void ATB_HD44780WriteCmd(uint8_t _cmd);

/**
    Send a command to display.

    @brief This function is not for direct usage. ATB_HD44780WriteDat()
    and ATB_HD44780WriteCmd() are wrappers for it.
    @param[in] _byt A command byte.
    @param[in] _isCmd Command type flag: 1 - for control, 0 - for data.
*/
void _ATB_HD44780Write(uint8_t _byt, uint8_t _isCmd);

/**
    Print a string on display.

    @brief Send _string to display at current cursor position.
    @todo Add a parameter to clear all the rest of the line.
    @todo Add a parameter to center a string on the line.
*/
void ATB_HD44780_PrintString(char* _string);

void ATB_HD44780_PrintLine(char _string[], uint8_t _line);

void _ATB_HD44780PrintByte(uint8_t _byte);

/**
    Set new cursor position.

    @param[in] _lin Display line.
    @param[in] _pos Position in line.
*/
void ATB_HD44780SetCursor(uint8_t _lin, uint8_t _pos);

#endif /* __ATB_HD44780 */
