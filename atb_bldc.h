/*
	AVR-Toolbox libraries for ATMEL MCUs.
	Operating with brushless DC motors with no hardware sensors.

	atb_bldc.h

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

#ifndef __ATB_BLDC
#define __ATB_BLDC

#include <avr/io.h>
#include "atb_bldc_hal.h"

#define ATB_BLDC_U_HI_EN ( ATB_BLDC_U_HI_REG |= (1 << ATB_BLDC_U_HI_BIT) );
#define ATB_BLDC_U_HI_DS ( ATB_BLDC_U_HI_REG &= ~(1 << ATB_BLDC_U_HI_BIT) );
#define ATB_BLDC_U_LO_EN ( ATB_BLDC_U_LO_PRT |= (1 << ATB_BLDC_U_LO_BIT) );
#define ATB_BLDC_U_LO_DS ( ATB_BLDC_U_LO_PRT &= ~(1 << ATB_BLDC_U_LO_BIT) );

#define ATB_BLDC_V_HI_EN ( ATB_BLDC_V_HI_REG |= (1 << ATB_BLDC_V_HI_BIT) );
#define ATB_BLDC_V_HI_DS ( ATB_BLDC_V_HI_REG &= ~(1 << ATB_BLDC_V_HI_BIT) );
#define ATB_BLDC_V_LO_EN ( ATB_BLDC_V_LO_PRT |= (1 << ATB_BLDC_V_LO_BIT) );
#define ATB_BLDC_V_LO_DS ( ATB_BLDC_V_LO_PRT &= ~(1 << ATB_BLDC_V_LO_BIT) );

#define ATB_BLDC_W_HI_EN ( ATB_BLDC_W_HI_REG |= (1 << ATB_BLDC_W_HI_BIT) );
#define ATB_BLDC_W_HI_DS ( ATB_BLDC_W_HI_REG &= ~(1 << ATB_BLDC_W_HI_BIT) );
#define ATB_BLDC_W_LO_EN ( ATB_BLDC_W_LO_PRT |= (1 << ATB_BLDC_W_LO_BIT) );
#define ATB_BLDC_W_LO_DS ( ATB_BLDC_W_LO_PRT &= ~(1 << ATB_BLDC_W_LO_BIT) );

#define ATB_BLDC_REVEMF_COUNTER_MAX  200

volatile uint8_t atb_bldc_compha;
volatile uint8_t atb_bldc_revemf_cnt;

/**
* Rotate motor with low speed.
* Call from timer overflow vector to rotate motor without
*   reverse EMF information from sensoring circut.
*/
void atb_bldc_no_reverse_emf_timer_ovf();

/**
* Rotate motor with high speed.
* Detect reverse EMF from sensor circut via
*   analog comparator interruption.
*/
void atb_bldc_reverse_emf_ac_ovf();

/**
* Commutate motor phases.
*/
void atb_bldc_commutation();

/**
* Shutdown all power on motor.
*/
void atb_bldc_stop_motor();

/**
* First run initialization. */
void atb_bldc_initialize();

#endif /* __ATB_BLDC */
