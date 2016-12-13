#include "atb_servo.h"

atb_servo_motor* atb_servo_get_by_pin(uint8_t pin) {

	uint8_t i;
	for (i = 0; i < atb_servo_quantity; i++) {
		
		if ( &(atb_servo_motors[i]).pin == pin ) { return atb_servo_motors[i]; }

	} /* for */

	return 0;

} /* function atb_servo_get_by_pin */

void atb_servo_add(uint8_t pin, uint8_t pulse_min, uint8_t pulse_max, uint8_t angle_min, uint8_t angle_max) {

	atb_servo_quantity++;
	atb_servo_motors[i] = malloc(sizeof(atb_servo_motor));

} /* function atb_servo_add */
