/*
 * tools functions
 *
 */
#include "config.h"
#include "ebike-bluetooth.h"
#include <WProgram.h>

#ifdef CONFIG_WITH_BLUETOOTH
	#include <MeetAndroid.h>
	MeetAndroid meetAndroid;
#endif


static long refresh=millis();
static double board[]={
	BLUETOOTH_PACKET_VERSION,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0
};

void bluetooth_send_pedelec(float i,float v,float p_a,float p_b,float ffx){
	board[1]=board[1]*BLUETOOTH_HPF +	i*BLUETOOTH_LPF;  
	board[2]=board[2]*BLUETOOTH_HPF +	v*BLUETOOTH_LPF;  
	board[3]=board[3]*BLUETOOTH_HPF +	p_a*BLUETOOTH_LPF;  
	board[4]=board[4]*BLUETOOTH_HPF +	p_b*BLUETOOTH_LPF;  
	board[5]=board[5]*BLUETOOTH_HPF +	ffx*BLUETOOTH_LPF;  
	
#ifdef CONFIG_WITH_BLUETOOTH
	long m=millis();
  if((m-refresh)>=BLUETOOTH_REFRESH){
 		refresh=m;
		meetAndroid.send(board,6);
	}
#endif
}


void  bluetooth_disconnect(){
#ifdef CONFIG_WITH_BLUETOOTH
	Serial.println("+++");
	delay(100);
	Serial.println("ATH");
	delay(500);
	//Serial.read(DISCONNECT '0CDF-A4-0F0EE5\n') ||timeout 3s	
#endif
}
