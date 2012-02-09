/*
 * controller functions
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#ifdef __cplusplus
extern "C"{
#endif
#include "ebike-accel.h"

void 	controller_pwm_init(int imax,int itilt, int vmin, int pout);
int 	controller_pwm_on(Accel &accel, float I,float V, int dt);
void 	controller_pwm_off();
void 	controller_pwm_calibrate();

#ifdef __cplusplus
}
#endif
#endif

