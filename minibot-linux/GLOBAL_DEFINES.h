/*
 * GLOBAL_DEFINES.h
 *
 *  Created on: Nov 3, 2015
 *      Author: Cornell Cup
 */

#pragma once

#define PWM_FREQUENCY 	1000
#define PERIOD_US		(int) ((1/(float)PWM_FREQUENCY)*1000000.0)
#define DUTY_STEP		0.01
#define DUTY_DT_US		50000


// PWM pins are 3, 5, 6, 9, 10, 11
#define MOTOR_LEFT_1_PIN	5
#define MOTOR_LEFT_2_PIN	3
#define MOTOR_RIGHT_1_PIN	6
#define MOTOR_RIGHT_2_PIN	9


#define PULSEIN_PIN_L		8
#define PULSEIN_PIN_R		11

#define MOTOR_CW	0
#define MOTOR_CCW	1

#define MAX_DUTY	0.95
#define MIN_DUTY	0.05

#define MAX_SPEED	455 //in RPM
#define MIN_SPEED	60 //in RPM

//Target speeds
extern float TARGET_SPEED_L; //in RPM
extern float TARGET_SPEED_R; //in RPM

#define CIRCUMFERENCE 3.14*0.07 //in centimeters

#define DIRECTION_STOP		0
#define DIRECTION_FORWARD	1
#define DIRECTION_BACKWARD	2
#define DIRECTION_LEFT		3
#define DIRECTION_RIGHT		4
#define DIRECTION_NULL		5

//PID terms
#define PTerm  1.0
#define ITerm  0.0
#define DTerm  0.0

#define IMUlog_file			"/home/imu.txt"
