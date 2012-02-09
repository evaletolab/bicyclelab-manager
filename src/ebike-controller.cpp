/*
 * output controller functions
 *
 */
#include "config.h"
#include "ebike-controller.h"
#include "ebike-tools.h"
#include <WProgram.h>
#include <math.h>



 /**
  * MANAGE PWM WITH CURRENT FEEDBACK
  * - maxpwm, calibration of the controller PWM
  * - lastcurrent, I-1
  * - current, I
  * - dt, sample time
  * - limit, current limit
  * - responcetime, amount of time to get effective the new PWM value. 
  *
  * Get inspired by the PID Controller (http://en.wikipedia.org/wiki/PID_controller) 
  * PID= Kp*Error + Ki*∫error*dt + Kd*(error-error1)/dt  
  *
  * 
  */
static int P_CONTROLLER;
  
void 	controller_pwm_init(int imax,int itilt, int vmin, int pout){
	P_CONTROLLER=pout;
	
	// Set pinout PWM frequency to 3906 Hz (31250/8 = 3906)
	// Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
	setPwmFrequency(P_CONTROLLER, 8);
}

int 	controller_pwm_on(Accel &accel, float I,float V, int dt){
  //no pedelec throttle is about 3.5V => 70% of 255 = 179
  #if 0
  if (no pedelec){
		analogWrite(P_CONTROLLER,179);
		return 0;
  }
  #endif
  //full throttle is 4.1V, 82% of 5V => 82% of 255 = 209
	analogWrite(P_CONTROLLER,209);
	return 1;
}

void 	controller_pwm_off(){
	analogWrite(P_CONTROLLER,0);
}

void 	controller_pwm_calibrate(){
}
