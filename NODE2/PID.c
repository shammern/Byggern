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
#define F_CPU 84000000
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
	if(curr_val > 100){
		curr_val = 100; 
	}else if(curr_val < -100){
		curr_val = -100;
	}
	
	float K_p = 0.5; 
	float K_i = 2;
	float K_d = 0;
	float T = 0.0001; //Same as periode for PWM signal
	int error = ref - curr_val;
	sum_error += error;
	
	if(sum_error > 3000){ //Integrator wind up
		sum_error = 1000;
	}else if (sum_error < -3000){
		sum_error = -1000;
	}
	

	float u_p = K_p * error;
	float u_i = (T * K_i * sum_error * error); 
	float u_d = (K_d / T) * (error - prev_error);

	float u = u_p + u_i + u_d;
	prev_error = error;
	
	if(u < 0){
		u *= 1.5; //Fix for larger friction when driving left
	}
	
	if(u > 100.0){
		u = 100.0;
	}
	else if(u < -100.0){
		u = -100.0;
	}
	return u;
}






