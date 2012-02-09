/*
 * tools functions
 *
 */
#include "config.h"
#include "ebike-tools.h"
#include <WProgram.h>
#include <math.h>

// filtered input value
static double fADC[6] = {0,0,0,0,0,0};

//
//average filter 40ms for 1 analogue value
//
double fanalogRead(int pin, int wait){
  if (fADC[pin]==0)
    fADC[pin]=analogRead(pin);
  for (int i=0;i<10;i++){
    fADC[pin] = 0.90 * fADC[pin] + 0.10 * analogRead(pin); 
    delay(wait);               
  }
  return fADC[pin];
}


// Return RC high-pass filter output sample, 
// x input sample, x¹ last sample (n-1) 
// y¹ last output sample (n-1), 
// dt time interval, 
// RC time constant
float highpass(float x, float x1 , float y1, float dt, float RC){
   double alpha = RC / (RC + dt);
   return  alpha * y1 + alpha * (x - x1);
}


// Return RC low-pass filter output sample, 
// x input sample, 
// y¹ last output sample (n-1), 
// dt time interval, 
// RC time constant
float lowpass(float x, float y1, float dt, float RC){
   float alpha=dt/(RC + dt);
   //return  alpha * x + (1-alpha) * y1;
   return  y1 + alpha * (x - y1);
}


void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}


