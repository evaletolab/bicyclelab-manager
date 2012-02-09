/*
 * sleep functions
 * ---------------
 * The bicycle controller turn to sleep when, 
 * 1) there is no activity since X secondes
 * 2) the current loaded by the power logic is bellow 50ma
 */

#ifndef SLEEP_H_
#define SLEEP_H_
#include "config.h" 
#include "ebike-accel.h" 


typedef void (*sleep_idle)	(void *data);
typedef void (*sleep_wakeup)(void *data);


#ifdef __cplusplus
extern "C"{
#endif

void 	sleep_init	(sleep_idle idle,sleep_wakeup wakeup, void * data);
void 	sleep_update(Accel &accel, int power,float i, int dt);
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void	sleep_delay	(int i);
#ifdef __cplusplus
}
#endif
#endif

