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
    @brief AVR Toolbox: HD44780 display driver. Test firmware.
    @author Sergei Ivanov <nsndrz@hotmail.org>
    @copyright The MIT License (MIT)

    A test program for HD44780 displays.
    A MCU is atmega8, frequency is 8 MHz.
*/

#include "atb_hd44780.h"

int main() {

    ATB_HD44780Init();

    ATB_HD44780SetCursor(1, 2);
    ATB_HD44780Print("Hello, ATmega!");
    ATB_HD44780SetCursor(2, 3);
    ATB_HD44780Print("AVR_Toolbox");

    return 0;
} /* function main */
