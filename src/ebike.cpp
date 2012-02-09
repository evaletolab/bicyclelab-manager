/**
 * read value from accelerometer 
 *  roadmap:
 *  - get gravitation and init axes
 *  - make plan with orthogonal zvector
 *  - detect forward and backward
 * 
 *  # read post about pedale detection
 *  http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1252694516/30
 *  
 */


#include "config.h"
#include <WProgram.h>
#include "ebike-tools.h" 
#include "ebike-sens.h" 
#include "ebike-accel.h" 
#include "ebike-controller.h"
#include "ebike-bluetooth.h"
#include "ebike-sleep.h"
#include <NewSoftSerial.h>


#ifdef CONFIG_WITH_EEPROM
#include <EEPROM.h>
#endif



#ifdef CONFIG_WITH_ECLIPSE
extern "C" void __cxa_pure_virtual() {  }
#endif


static int		sleep_time=SLEEP_CYCLE_DOWN;
static long 	dt=0, lasttime=0;
static float i,v;

static Accel accel;
static float vref;



void onsleep(void* data){
	bluetooth_disconnect();
	digitalWrite(P_SWFET,LOW);
	sleep_time=SLEEP_CYCLE_DOWN;
	//Serial.println("DOWN");
}
void onwakeup(void* data){
	digitalWrite(P_SWFET,HIGH);
	sleep_time=SLEEP_CYCLE_UP;
	//Serial.println("WAKEUP");
}


void setup()   {                
  // initialize the digital pin as VCC
  pinMode(P_VCC, OUTPUT);     
  pinMode(P_GND, OUTPUT);     
  pinMode(P_SWFET, OUTPUT);     
  pinMode(P_THROTTLE, OUTPUT);     
  digitalWrite(P_SWFET, LOW);
  digitalWrite(P_VCC, HIGH);
  digitalWrite(P_GND, LOW);

  Serial.begin(115200);
  
  //
  // init power manager
  //sleep_init();
  //sleep_watchdog(8);
  
  // init accel
  accel_init();

  // i_max, i_tilte, v_min, throttle
  controller_pwm_init(I_MAX,I_TILT, V_MIN, P_THROTTLE);
	sleep_init	(onsleep,onwakeup, NULL);  
}


void loop(){		   

  //
  // stay in sleep mode? 
  //   if (!power AND SLEEP_CYCLE_DOWN) then powerdown arduino
  //
	delay(10); //in case of wakeup time
  int power=digitalRead(P_POWER);
  //Serial.print(power);Serial.print(" ,");
	if (sleep_time==SLEEP_CYCLE_DOWN){
		dt=sleep_time+10;
		// During this time power consumption is minimised
		if (!power){
			sleep_delay(sleep_time);
			return;
		}
	}else{
		dt=sleep_time;
	}
	//
	// read sensors (internal voltage, batt current, batt voltage)      
	sens_init(vref);
	vref=sens_internal_vcc()/1000.0;
	i=sens_battery_current(A_I);
	v=sens_battery_voltage(A_V);
  
  
  //
  // get accel data structure
  //   pedelec_a, first direction of the X force 
  //   pedelec_b, second direction of the X force 
  //   filtered_forward_force, Low path filter on F[N]=m*a
	accel_update(accel,vref,1.0);
	
  if (power){
    power=controller_pwm_on(accel,i,v,dt);    
  }  
  
  //cut power when button is up
  if (power==0){
    controller_pwm_off();
  }
  
  sleep_update(accel,power,i,dt);
	
		
	bluetooth_send_pedelec(i,v,accel.pedelec_a,accel.pedelec_b,accel.filtered_forward_force);
  
	delay(100);
}




