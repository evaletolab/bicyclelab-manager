/*
 * accel functions
 *
 */
#include "config.h"
#include "ebike-accel.h"
#include "ebike-tools.h"
#include <WProgram.h>
#include <math.h>
#include "Adxl345.h"


// 3axes values to correct the Accel values to G
static double offset[]={
	ORTHOGONAL,
	ORTHOGONAL,
	0.0
};

Accelerometer adxl;

void accel_init(){
  // init adxl to 2g
  adxl.powerOn();
  adxl.setRangeSetting(2);
}

void 	accel_update(Accel& accel , double vref, double mass){
	float x1=0.0,y1=0.0;
	double v[3], angle[3];
  //read accelerometer 
  adxl.readG(&v[X],&v[Y],&v[Z]);  
  double r=module((v[X]),(v[Y]),(v[Z]));
  
  // rotate XYZ to fit G
  angle[X]=alpha((v[X]),r)+offset[X];
  angle[Y]=alpha((v[Y]),r)+offset[Y];
  angle[Z]=alpha((v[Z]),r)+offset[Z];

  // get the new projected vectors[x,y,z] after rotation and
  // compute the force  F[N]=m*accel
  accel.force[X]=aalpha(angle[X]+ORTHOGONAL,r) * 9.81 * mass ;
  accel.force[Y]=aalpha(angle[Y]+ORTHOGONAL,r) * 9.81 * mass ;
  accel.force[Z]=aalpha(angle[Z],r) * 9.81 * mass ;


  // low-freq force on X
  accel.filtered_forward_force=0.2*accel.force[X]+0.8*accel.filtered_forward_force;
  
  //
  // remove high freq for pedelec A,B
  float pedelec=highpass(accel.force[X],x1,y1,0.2,0.14);
  if (pedelec>0.0)
  	accel.pedelec_a= 0.6*pedelec + 0.4*accel.pedelec_a;
  else
  	accel.pedelec_b= 0.6*pedelec + 0.4*accel.pedelec_b;

  //rotate to the initial position
  if (offset[Z]==0.0 && offset[X]==ORTHOGONAL){
    offset[X]=offset[X]-accel.force[X];
    offset[Y]=offset[Y]-accel.force[Y];
    offset[Z]=offset[Z]-accel.force[Z];
  }

}


