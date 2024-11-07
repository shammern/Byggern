/*
 * PID.c
 *
 * Created: 06.11.2024 10:21:43
 *  Author: torstepu
 */ 

#include "PID.h"

//static PID_parameters PID = {0.2,0,0.1,0,0,0.0001,100};
static int sum_error = 0; 
static int prev_error = 0;
#define MAX_U 100
	
#define K_P 2
#define K_I 0
#define K_D 1

#define MAX_U 100

// 
// void pid_init(float k_p, float k_i, float k_d, float timestep, int max_u){
// 	PID.max_u = max_u;
// 	PID.T = timestep;
// 	pid_set_parameters(k_d, k_i, k_d);
// }
// 
// void pid_set_parameters(float k_p, float k_i, float k_d){
// 	PID.K_d = k_d;
// 	PID.K_i = k_i;
// 	PID.K_p = k_p;
// }
// 
// void pid_reset_error(){
// 	PID.sum_error = 0;
// 	PID.prev_error = 0;
// }

float pid_controller(int ref, int curr_val){
	float K_p = 0.08;
	float K_i = 5;
	float K_d = 0;
	float T = 1e-3;
	
	
	int error = (ref - curr_val);
	printf("ERROR_prosent: %d\n", error);
	sum_error += error;

	float u_p = K_p * error;
	float u_i = (T * K_i * sum_error);
	float u_d = (K_d / T) * (error - prev_error);

	float u = u_p + u_i + u_d;
	prev_error = error;

	if(u > 100.0){
		u = 100.0;
	}
	else if(u < -100.0){
		u = -100.0;
	}
	return u;
}

#define ENCODER_MIDPOINT 2790
#define KP 0.5   // Proportional gain, adjust to tune
#define KI 0.1   // Integral gain, adjust to tune
#define KD 0.05  // Derivative gain, adjust to tune
#define JOYSTICK_DEADZONE 5
#define MOTOR_SPEED_MIN 0
#define MOTOR_SPEED_MAX 100
#define ENCODER_MAX 5580
#define ENCODER_MIN 0

int motor_position_controller(uint32_t encoder_value, int joystick_value) {
	static int previous_error = 0;
	static int integral = 0;
	int target_position;
	
	// Map joystick value to encoder range
	if (joystick_value != 0) {
		target_position = ENCODER_MIDPOINT + (joystick_value * (ENCODER_MAX - ENCODER_MIN) / 200);
		} else {
		// Set target to midpoint when joystick is released
		target_position = ENCODER_MIDPOINT;
	}
	
	// Calculate error
	int error = target_position - encoder_value;
	
	// If within deadzone, stop the motor
	if (abs(error) <= JOYSTICK_DEADZONE) {
		integral = 0;  // Reset integral term when within deadzone
		return 0;      // Stop the motor
	}
	
	// Integral calculation (accumulates error)
	integral += error;
	
	// Derivative calculation (rate of change of error)
	int derivative = error - previous_error;
	
	// PID formula
	int motor_speed = (KP * error) + (KI * integral) + (KD * derivative);
	
	// Clamp motor_speed to be within MOTOR_SPEED_MIN and MOTOR_SPEED_MAX
	if (motor_speed > MOTOR_SPEED_MAX) {
		motor_speed = MOTOR_SPEED_MAX;
		} else if (motor_speed < MOTOR_SPEED_MIN) {
		motor_speed = MOTOR_SPEED_MIN;
	}
	
	// Update previous error for the next iteration
	previous_error = error;
	
	return motor_speed;
}
