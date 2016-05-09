/*
 * motor_drive.h
 *
 *  Created on: Nov 4, 2015
 *      Author: Cornell Cup
 */
#pragma once 

#include "mraa.h"
#include "GLOBAL_DEFINES.h"


/*
 * motor direction function must be called before using drive or brake functions
 */
namespace Servo {
	extern mraa_pwm_context PWM_MOTOR_LEFT;
	extern mraa_gpio_context DIRECTION_MOTOR_LEFT;
	extern mraa_gpio_context BRAKE_MOTOR_LEFT;
	extern int pwm_pin;

	extern mraa_pwm_context PWM_MOTOR_RIGHT;
	extern mraa_gpio_context DIRECTION_MOTOR_RIGHT;
	extern mraa_gpio_context BRAKE_MOTOR_RIGHT;
	extern int pwm_pin2;

	extern int oldDirection_left;
	extern int oldDirection_right;


	int motorLeft_drive(float duty);
	int motorLeft_direction(int direction);
	int motorLeft_brake(void);
	int motorRight_drive(float duty);
	int motorRight_direction(int direction);
	int motorRight_brake(void);
	void drive_motors(float speed, int direction);
};

