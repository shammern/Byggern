#include "PID.h"

static PID_parameters PID = {0,0,0,0,0,0,0};

void pid_init(float k_p, float k_i, float k_d, float timestep, int max_u){
    PID.max_u = max_u;
    PID.T = timestep;
    pid_set_parameters(k_d, k_i, k_d);
}

void pid_set_parameters(float k_p, float k_i, float k_d){
    PID.K_d = k_d;
    PID.K_i = k_i;
    PID.K_p = k_p;
}

void pid_reset_error(){
    PID.sum_error = 0;
    PID.prev_error = 0;
}

int pid_controller(int ref, int curr_val){
    int error = ref - curr_val;
    PID.sum_error += error;

    int u_p = PID.K_p * error;
    int u_i = PID.T * PID.K_i * PID.sum_error;
    int u_d = (PID.K_d / PID.T) * (error - PID.prev_error);

    int u = u_p + u_i + u_d;
    PID.prev_error = error;

    if(u > PID.max_u){
        u = PID.max_u;
    }else if(u < -PID.max_u){
        u = -PID.max_u;
    }

    return u;
}