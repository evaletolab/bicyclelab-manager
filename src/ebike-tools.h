/*
 * tools functions
 *
 */

#ifndef TOOLS_H_
#define TOOLS_H_


#ifdef __cplusplus
extern "C"{
#endif

/**
 * Divides a given PWM pin frequency by a divisor.
 *
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 *
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 *
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 *
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1235060559/0#4
 */
void setPwmFrequency(int pin, int divisor);

// Return RC high-pass filter output sample, 
// x input sample, x¹ last sample (n-1) 
// y¹ last output sample (n-1), 
// dt time interval, 
// RC time constant, f[Hz]=1/(2*pi*RC)
float highpass(float x, float x1 , float y1, float dt, float RC);

// Return RC low-pass filter output sample, 
// x input sample, 
// y¹ last output sample (n-1), 
// dt time interval, 
// RC time constant, f[Hz]=1/(2*pi*RC)   
//                    our use case is an lp filter at 4.08[s]=>0.24[Hz] => RC=T/(2pi) => ratio=dt*(RC+dt) => Y=X*ratio+Y1*(1-ratio)
float lowpass(float x, float y1, float dt, float RC);

//
//average filter 40ms for 1 analogue value
double fanalogRead(int pin, int wait);

//
//R = SQRT( Rx^2 + Ry^2 + Rz^2)
#define module(X,Y,Z)   (sqrt(square(X)+square(Y)+square(Z)))

//
//
#define alpha(C,R)      acos(C/R)
#define aalpha(A,R)     (cos(A)*R)



#ifdef __cplusplus
}
#endif
#endif

