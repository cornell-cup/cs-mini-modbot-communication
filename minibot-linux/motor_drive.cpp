/*
 * motor_drive.h
 *
 *  Created on: Nov 4, 2015
 *      Author: Cornell Cup
 */
#include "motor_drive.h"


using namespace Servo;
/*
 * motor direction function must be called before using drive or brake functions
 */

mraa_pwm_context Servo::PWM_MOTOR_LEFT = NULL;
mraa_gpio_context Servo::DIRECTION_MOTOR_LEFT = NULL;
mraa_gpio_context Servo::BRAKE_MOTOR_LEFT = NULL;
int Servo::pwm_pin;

mraa_pwm_context  Servo::PWM_MOTOR_RIGHT = NULL;
mraa_gpio_context Servo::DIRECTION_MOTOR_RIGHT = NULL;
mraa_gpio_context Servo::BRAKE_MOTOR_RIGHT = NULL;
int Servo::pwm_pin2;

int Servo::oldDirection_left = -1;
int Servo::oldDirection_right = -1;


int Servo::motorLeft_drive(float duty) {
		/* Set speed between minimum and maximum (set in motor_drive.h)
 * These are in float -> eg 0.3 = 30% duty
 *
 */
	mraa_result_t result;

	if (duty > MAX_DUTY){
		duty = MAX_DUTY;
	}

	if (duty < MIN_DUTY){
		duty = MIN_DUTY;
	}

	result = mraa_pwm_write(Servo::PWM_MOTOR_LEFT, duty);

	if (result == MRAA_SUCCESS){
		return 0;
	}
	else{
		return -1;
	}

}

int Servo::motorLeft_direction(int direction) {
	/* Configure motor driver for use with specified direction
	 * direction = either MOTOR_CW or MOTOR_CCW
	 * return value = 0 if direction setting was successful
	 * 				= -1 if it failed
	 */

	/* MOTOR+ = OUT1, MOTOR- = OUT2
	 * CCW OPERATION:
	 * 		CONTROL SIGNALS:
	 * 			OUT1 = VS, OUT2 = GND
	 * 			IN1 = 1, IN2 = 0
	 * 		PWM = IN1
	 * 		Servo::DIRECTION = IN2 = 0
	 * 	CW OPERATION:
	 * 		CONTROL SIGNALS:
	 * 			OUT1 = GND, OUT2 = VS
	 * 			IN1 = 0, IN2 = 1
	 *		PWM = IN2
	 *		Servo::DIRECTION = IN1 = 0
	 *
	 */

	if (direction == Servo::oldDirection_left){
		// direction already set, don't do anything
		return 0;
	}

	Servo::oldDirection_left = direction;

	// if pwm channel was initialized for a direction, close it to enable it to be
	// initialized to a different pin; similar for direction gpio pin
	if (Servo::PWM_MOTOR_LEFT != NULL){
		mraa_pwm_close(Servo::PWM_MOTOR_LEFT);
		Servo::PWM_MOTOR_LEFT = NULL;
	}

	if (Servo::DIRECTION_MOTOR_LEFT != NULL){
		mraa_gpio_close(Servo::DIRECTION_MOTOR_LEFT);
		Servo::DIRECTION_MOTOR_LEFT = NULL;
	}

	if (direction == MOTOR_CCW){
		Servo::PWM_MOTOR_LEFT = mraa_pwm_init(MOTOR_LEFT_1_PIN);
		Servo::DIRECTION_MOTOR_LEFT = mraa_gpio_init(MOTOR_LEFT_2_PIN);
		Servo::pwm_pin = MOTOR_LEFT_1_PIN;
	}
	else if (direction == MOTOR_CW){
		Servo::PWM_MOTOR_LEFT = mraa_pwm_init(MOTOR_LEFT_2_PIN);
		Servo::DIRECTION_MOTOR_LEFT = mraa_gpio_init(MOTOR_LEFT_1_PIN);
		Servo::pwm_pin = MOTOR_LEFT_2_PIN;
	}

	if (Servo::PWM_MOTOR_LEFT == NULL || Servo::DIRECTION_MOTOR_LEFT == NULL){
		fprintf(stderr, "Could not initialize left motor, MRAA error!\n");
		return -1;
	}

	// configure pwm settings
	mraa_pwm_period_us(Servo::PWM_MOTOR_LEFT, PERIOD_US);
	mraa_pwm_enable(Servo::PWM_MOTOR_LEFT, 1);

	// this sets pwm to work in correct direction
	mraa_gpio_dir(Servo::DIRECTION_MOTOR_LEFT, MRAA_GPIO_OUT);
	mraa_gpio_write(Servo::DIRECTION_MOTOR_LEFT, 0);

	return 0;

}

int Servo::motorLeft_brake(void) {
	// Free PWM so that pin can be used as GPIO
	if (Servo::PWM_MOTOR_LEFT != NULL){
		mraa_pwm_close(Servo::PWM_MOTOR_LEFT);
		Servo::PWM_MOTOR_LEFT = NULL;
	}

	Servo::oldDirection_left = -1;

	// Electrical brake when:
	// IN1 = 0, IN2 = 0,
	// or
	// IN1 = 1, IN2 = 1
	// Since direction pin is always set to 0 in motorLeft_direction(),
	// set brake pin to also be 0

	Servo::BRAKE_MOTOR_LEFT = mraa_gpio_init(Servo::pwm_pin);
	if (Servo::BRAKE_MOTOR_LEFT == NULL){
		return -1;
	}

	mraa_gpio_write(Servo::BRAKE_MOTOR_LEFT, 0);
	mraa_gpio_close(Servo::BRAKE_MOTOR_LEFT);

	return 0;
}

int Servo::motorRight_drive(float duty) {
			/* Set speed between minimum and maximum (set in motor_drive.h)
	 * These are in float -> eg 0.3 = 30% duty
	 *
	 */
	mraa_result_t result;

	if (duty > MAX_DUTY){
		duty = MAX_DUTY;
	}

	if (duty < MIN_DUTY){
		duty = MIN_DUTY;
	}

	result = mraa_pwm_write(Servo::PWM_MOTOR_RIGHT, duty);

	if (result == MRAA_SUCCESS){
		return 0;
	}
	else{
		return -1;
	}
}

int Servo::motorRight_direction(int direction) {
			/* Configure motor driver for use with specified direction
	 * direction = either MOTOR_CW or MOTOR_CCW
	 * return value = 0 if direction setting was successful
	 * 				= -1 if it failed
	 */

	/* MOTOR+ = OUT1, MOTOR- = OUT2
	 * CCW OPERATION:
	 * 		CONTROL SIGNALS:
	 * 			OUT1 = VS, OUT2 = GND
	 * 			IN1 = 1, IN2 = 0
	 * 		PWM = IN1
	 * 		Servo::DIRECTION = IN2 = 0
	 * 	CW OPERATION:
	 * 		CONTROL SIGNALS:
	 * 			OUT1 = GND, OUT2 = VS
	 * 			IN1 = 0, IN2 = 1
	 *		PWM = IN2
	 *		Servo::DIRECTION = IN1 = 0
	 *
	 */

	if (direction == Servo::oldDirection_right){
		// direction already set, don't do anything
		return 0;
	}

	Servo::oldDirection_right = direction;

	// if pwm channel was initialized for a direction, close it to enable it to be
	// initialized to a different pin; similar for direction gpio pin
	if (Servo::PWM_MOTOR_RIGHT != NULL){
		mraa_pwm_close(Servo::PWM_MOTOR_RIGHT);
		Servo::PWM_MOTOR_RIGHT = NULL;
	}

	if (Servo::DIRECTION_MOTOR_RIGHT != NULL){
		mraa_gpio_close(Servo::DIRECTION_MOTOR_RIGHT);
		Servo::DIRECTION_MOTOR_RIGHT = NULL;
	}

	if (direction == MOTOR_CCW){
		Servo::PWM_MOTOR_RIGHT = mraa_pwm_init(MOTOR_RIGHT_1_PIN);
		Servo::DIRECTION_MOTOR_RIGHT = mraa_gpio_init(MOTOR_RIGHT_2_PIN);
		Servo::pwm_pin2 = MOTOR_RIGHT_1_PIN;
	}
	else if (direction == MOTOR_CW){
		Servo::PWM_MOTOR_RIGHT = mraa_pwm_init(MOTOR_RIGHT_2_PIN);
		Servo::DIRECTION_MOTOR_RIGHT = mraa_gpio_init(MOTOR_RIGHT_1_PIN);
		Servo::pwm_pin2 = MOTOR_RIGHT_2_PIN;
	}

	if (Servo::PWM_MOTOR_RIGHT == NULL || Servo::DIRECTION_MOTOR_RIGHT == NULL){
		fprintf(stderr, "Could not initialize right motor, MRAA error!\n");
		return -1;
	}

	// configure pwm settings
	mraa_pwm_period_us(Servo::PWM_MOTOR_RIGHT, PERIOD_US);
	mraa_pwm_enable(Servo::PWM_MOTOR_RIGHT, 1);

	// this sets pwm to work in correct direction
	mraa_gpio_dir(Servo::DIRECTION_MOTOR_RIGHT, MRAA_GPIO_OUT);
	mraa_gpio_write(Servo::DIRECTION_MOTOR_RIGHT, 0);

	return 0;


}

int Servo::motorRight_brake(void) {
	// Free PWM so that pin can be used as GPIO
	if (Servo::PWM_MOTOR_RIGHT != NULL){
		mraa_pwm_close(Servo::PWM_MOTOR_RIGHT);
		Servo::PWM_MOTOR_RIGHT = NULL;
	}

	Servo::oldDirection_right = -1;

	// Electrical brake when:
	// IN1 = 0, IN2 = 0,
	// or
	// IN1 = 1, IN2 = 1
	// Since direction pin is always set to 0 in motorLeft_direction(),
	// set brake pin to also be 0

	Servo::BRAKE_MOTOR_RIGHT = mraa_gpio_init(Servo::pwm_pin2);
	if (Servo::BRAKE_MOTOR_RIGHT == NULL){
		return -1;
	}

	mraa_gpio_write(Servo::BRAKE_MOTOR_RIGHT, 0);
	mraa_gpio_close(Servo::BRAKE_MOTOR_RIGHT);

	return 0;
}

void Servo::drive_motors(float speed, int direction) {
	//Prevents duty cycle from going above 0.95 or below 0.14 (motors behave weirdly anything below this)
	if (speed < MIN_SPEED){
		speed = MIN_SPEED;
	}
	if (speed > MAX_SPEED){
		speed = MAX_SPEED;
	}

	float duty;
	duty = (speed + 8.4643)/486.54;

	//Brake both motors
	if (direction == DIRECTION_STOP){
		motorLeft_brake();
		motorRight_brake();
	}

	switch (direction){
	//FORWARD: drive both motors at target speed in forward direction
	case DIRECTION_FORWARD:
		motorLeft_direction(MOTOR_CCW);
		motorRight_direction(MOTOR_CCW);
		motorLeft_drive(duty);
		motorRight_drive(duty);
		break;
		//BACKWARD: drive both motors at target speed in backwards direction
	case DIRECTION_BACKWARD:
		motorLeft_direction(MOTOR_CW);
		motorRight_direction(MOTOR_CW);
		motorLeft_drive(duty);
		motorRight_drive(duty);
		break;
	}
}

