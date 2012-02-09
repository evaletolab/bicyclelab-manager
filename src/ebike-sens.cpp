/*
 * accel functions
 *
 */
#include "config.h"
#include "ebike-sens.h"
#include <WProgram.h>
#include <math.h>


static double _amp_V=0;
static double _amp_I=0;


void sens_init(float vref){
  _amp_V=SENS_VOLTAGE_RATIO*vref/1024.0;
  _amp_I=SENS_CURRENT_RATIO*vref/1024.0;
}

float sens_battery_voltage(int pin ){
    return analogRead(pin)*_amp_V;
}  

// spec is 90.15A => 22.01ma/bit with 12bits adc => 0.8804 with 10bits adc
// spec are for 3.3V, for 5V => value x 1.5151
float sens_battery_current(int pin ){    
    return (analogRead(pin)-SENS_CURRENT_0)*_amp_I;
}

long sens_internal_vcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

