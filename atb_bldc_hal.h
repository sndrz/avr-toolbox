/*
	AVR-Toolbox libraries for ATMEL MCUs.
	Operating with brushless DC motors with no hardware sensors.

	atb_bldc_hal.h
	Redefine these values for current MCU and layout.

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

#ifndef __ATB_BLDC_HAL
#define __ATB_BLDC_HAL

/** Transistors control pins */

#define	ATB_BLDC_U_HI_DDR	0x17
#define	ATB_BLDC_U_HI_PRT	0x18
#define	ATB_BLDC_U_HI_BIT	1

#define	ATB_BLDC_U_LO_DDR	0x17
#define	ATB_BLDC_U_LO_PRT	0x18
#define	ATB_BLDC_U_LO_BIT	1

#define	ATB_BLDC_V_HI_DDR	0x17
#define	ATB_BLDC_V_HI_PRT	0x18
#define	ATB_BLDC_V_HI_BIT	1

#define	ATB_BLDC_V_LO_DDR	0x17
#define	ATB_BLDC_V_LO_PRT	0x18
#define	ATB_BLDC_V_LO_BIT	1

#define	ATB_BLDC_W_HI_DDR	0x17
#define	ATB_BLDC_W_HI_PRT	0x18
#define	ATB_BLDC_W_HI_BIT	1

#define	ATB_BLDC_W_LO_DDR	0x17
#define	ATB_BLDC_W_LO_PRT	0x18
#define	ATB_BLDC_W_LO_BIT	1

/** PWM input pin */

#define	ATB_BLDC_INP_PWM_DDR	0x17
#define	ATB_BLDC_INP_PWM_PRT	0x18
#define	ATB_BLDC_INP_PWM_BIT	1

#endif // __ATB_BLDC_HAL
