/*
 * sleep functions
 *
 */
#include "config.h"
#include "ebike-sleep.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>

#include <avr/wdt.h>
#include <avr/sleep.h>

#ifdef CONFIG_WITH_NARCOLEPTIC
#include <Narcoleptic.h>
#endif


#ifndef cbi
	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


#ifdef CONFIG_WITH_NARCOLEPTIC
  //Narcoleptic.disableTimer1();
  //Narcoleptic.disableTimer2();
  //Narcoleptic.disableSerial();
  //Narcoleptic.disableADC();
  //Narcoleptic.disableWire();
  //Narcoleptic.disableSPI();
#endif  


static long lasttime=0;
static sleep_idle _idle=0;
static sleep_wakeup _wakeup=0;
static void * _data=0;

void 	sleep_init	(sleep_idle idle,sleep_wakeup wakeup, void * data){
	_idle=idle;
	_wakeup=wakeup;
	_data=data;
	
  // CPU Sleep Modes 
  // SM2 SM1 SM0 Sleep Mode
  // 0    0  0 Idle
  // 0    0  1 ADC Noise Reduction
  // 0    1  0 Power-down
  // 0    1  1 Power-save
  // 1    0  0 Reserved
  // 1    0  1 Reserved
  // 1    1  0 Standby(1)

//  cbi( SMCR,SE );      // sleep enable, power down mode
//  cbi( SMCR,SM0 );     // power down mode
//  sbi( SMCR,SM1 );     // power down mode
//  cbi( SMCR,SM2 );     // power down mode	
}

void 	sleep_update(Accel &accel, int power,float i, int dt){
	if (lasttime>SLEEP_AFTER_TIME){
		_idle(_data);
		lasttime=0;
		return;
	}
	
	if(power && !lasttime){
		_wakeup(_data);
		lasttime=1;
	}

	if (lasttime>0)lasttime+=dt;
	
}

void	sleep_delay(int t){
#ifdef CONFIG_WITH_NARCOLEPTIC
		Narcoleptic.delay(t); 
#else
		delay(t);
#endif  
}

#ifdef CONFIG_WITH_CUSTOMSLEEP

//****************************************************************  
// set system into the sleep state 
// system wakes up when wtchdog is timed out
void sleep_now() {

  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

    sleep_disable();                     // System continues execution here when watchdog timed out 
    sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON

}

//****************************************************************
// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void sleep_watchdog(int ii) {

  unsigned char bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);


}
void sleep_delay(int ii){
	sleep_watchdog(ii);
	sleep_now();
}

// Watchdog Interrupt Service / is executed when  watchdog timed out
ISR(WDT_vect) {
}
#endif
