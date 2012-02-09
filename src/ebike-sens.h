/*
 * current & voltage sens functions
 *
 */

#ifndef SENS_H_
#define SENS_H_


#ifdef __cplusplus
extern "C"{
#endif

//
// spec is 90.15A => 22.01ma/bit with 12bits adc => 0.8804 with 10bits adc
// spec are for 3.3V, for 5V => value x 1.5151
//
void 		sens_init							(float vref);
float 	sens_battery_voltage	(int pin );
float 	sens_battery_current	(int pin );

//
// get arduino voltage reference (3.3V or 5V)
// 
long    sens_internal_vcc			();



#ifdef __cplusplus
}
#endif
#endif

