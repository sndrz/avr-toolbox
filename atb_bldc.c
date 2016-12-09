/*
	AVR-Toolbox libraries for ATMEL MCUs.
	Operating with brushless DC motors with no hardware sensors.

	atb_bldc.c

    Copyright (C) 2016-2017 Sergei Ivanov <nsndrz@hotmail.org>
*/

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "atb_bldc.h"

void atb_bldc_no_reverse_emf_timer_ovf() {

    atb_bldc_commutation();
    atb_bldc_revemf_cnt = 0;

} /* function atb_bldc_no_reverse_emf_timer_ovf */

void atb_bldc_reverse_emf_ac_ovf() {

    if (atb_bldc_revemf_cnt < ATB_BLDC_REVEMF_COUNTER_MAX) {
        atb_bldc_revemf_cnt++;
    } else {
        atb_bldc_commutation();
    }

} /* function atb_bldc_reverse_emf_ac_ovf */

void atb_bldc_commutation() {

} /* function atb_bldc_commutation */

void atb_bldc_stop_motor() {

    ATB_BLDC_U_HI_DS;
    ATB_BLDC_V_HI_DS;
    ATB_BLDC_W_HI_DS;
    ATB_BLDC_U_LO_DS;
    ATB_BLDC_V_LO_DS;
    ATB_BLDC_W_LO_DS;

} /* function atb_bldc_commutation */

void atb_bldc_initialize() {

    /* Set up IO ports */

    /* Shutdown all motor phases */

    atb_bldc_stop_motor();

    /* Set initial values */

    atb_bldc_compha = 0;
    atb_bldc_revemf_cnt = 0;

    /* Set up AC for sensor circut */

    /* Disable ADC */
    ADCSRA &= ~(1 << ADEN);
    /* Connect AC negative input to ADCx pins */
    ADCSRB |= (1 << ACME);
    /* Enable AC interruptions */
    ACSR |= (1 << ACIE);

} /* function atb_bldc_init */
