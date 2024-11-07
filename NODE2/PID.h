#pragma once

#include <stdint.h>

#ifndef PID_H
#define PID_H

typedef struct
{
    float K_p;
    float K_i;
    float K_d;
    int sum_error;
    int prev_error;
    float T;
    int max_u;
}PID_parameters;

void pid_init(float k_p, float k_i, float k_d, float timestep, int max_u);

void pid_set_parameters(float k_p, float k_i, float k_d);

void pid_reset_error();

int pid_controller(int ref);



#endif