#include "atb_math.h"

char* ATB_Math_IntToStr_10(int _value, char* _buffer, uint8_t _digits, uint8_t _mantiss, uint8_t _sign) {

    uint8_t _strSize;
    int _cnt, _m;
    char _buf[12];

    _cnt = _value;
    _strSize = 2; /* For the first iteration and '\0'. */
    while ( (_cnt /= 10) != 0 ) {
        _strSize++;
    }

    if (_mantiss != 0) { _strSize++; } /* For the '.' divider. */
    if (_sign == 1) { _strSize++; } /* For the sign symbol. */

    _buffer = (char*)malloc(_strSize);
    _buffer[_strSize-1] = '\0';

    if (_sign == 1) {
        if (_value < 0) {
            _buffer[0] = '-';
            _value *= -1;
        } else {
            _buffer[0] = '+';
        }
    }

    _cnt = _strSize - 2;
    _m = 0;
    while (_value > 0) {
        utoa( (_value % 10), _buf, 10);
        _buffer[_cnt] = _buf[0];
        _value /= 10;
        _m++;
        _cnt--;

        if (_m == _mantiss) {
            _buffer[_cnt] = '.';
            _cnt--;
        }
    }
    return _buffer;
}
