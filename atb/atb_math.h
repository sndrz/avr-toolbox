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
    @brief AVR Toolbox: Common functions and defines.
    @author Sergei Ivanov <ivanov@sndrz.xyz>
    @copyright The MIT License (MIT)

    Some math for usability.
*/

#ifndef __ATB_MATH
#define __ATB_MATH

#include <avr/io.h>

#define cbi(byt, bit)   ( byt &= ~_BV(bit) )
#define sbi(byt, bit)   ( byt |= _BV(bit) )
#define chb(byt, bit)   ( byt & _BV(bit) )
#define inb(byt, bit)   ( byt ^= _BV(bit) )

#define sym(byt, msk)   ( ( byt & ^msk ) | msk )
#define cym(byt, msk)   ( byt & ^msk )

/**
    @brief Convert integer to string with divide by 10 method.
    @date 23.05.2019-24.05.2019
    @warning That algorithm could be indecently unoptimized.

    @param _value A source integer to convert.
    @param _digits A number of digits in _value.
    @param _mantiss A number of digits in _value to be separated into fraction.
    @param _sign Set 1 to display _value sign, and 0 - to do not.

    @note Do I really need a malloc here?
*/
char* ATB_Math_IntToStr_10(int _value, char* _buffer, uint8_t _digits, uint8_t _mantiss, uint8_t _sign);

#endif /* __ATB_MATH */
