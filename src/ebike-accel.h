/*
 * accel functions
 *
 */

#ifndef ACCEL_H_
#define ACCEL_H_
#include "config.h" 


#define r2deg 57.2957795
#define ORTHOGONAL 1.5707963

#ifdef __cplusplus
extern "C"{
#endif

typedef struct Accel{
	float pedelec_a;
	float pedelec_b;
	float filtered_forward_force;
	double force[3];
};

void 	accel_init	();
void 	accel_update(Accel& accel , double vref, double mass);

//
//
// update vector values for 
//   angles a[x,y,z] 
//   coordinates v[x,y,z], 
//   coordinates after rotation v1[x,y,z], 
//   force in newton for 60kg mass n[x,y,z], 
//   input vref value
int accel_update2(double*, double*, double*, double*, double vref, double mass);


#ifdef __cplusplus
}
#endif
#endif

