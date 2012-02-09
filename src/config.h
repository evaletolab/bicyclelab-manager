

/**
 * battery life calculator
 * http://oregonembedded.com/batterycalc.htm
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define CONFIG_WITH_DEBUG
#define CONFIG_WITH_ACCEL_I2C
#define CONFIG_WITH_ECLIPSE
//#define CONFIG_WITH_LOGGER
#define CONFIG_WITH_NARCOLEPTIC
#define CONFIG_WITH_BLUETOOTH
//#define CONFIG_WITH_TIMER

//
// battery managment
#define I_MAX 11
#define I_TILT 14
#define V_MIN 28
#define SLEEP_CYCLE_UP 200
#define SLEEP_CYCLE_DOWN 800
#define SLEEP_AFTER_TIME 180000
#define SLEEP_WHEN_I_LOWER 0.03
#define SENS_VOLTAGE_RATIO 13.03

// ACS712 20A = 100 +-4 mv/A @5VCC => 0.066 @3.3VCC
#define SENS_CURRENT_RATIO 15.1515
// middle value is less than 5VCC, 4.85/2=2.425*0.66=1.605 => 497bits
#define SENS_CURRENT_0 497

// the refresh time is set to limit the bt I/O and preserve the battery 
#define BLUETOOTH_REFRESH 1000

// the average must be proportianal to the refresh time
#define BLUETOOTH_HPF 0.3
#define BLUETOOTH_LPF 0.7

#define X 0
#define Y 1
#define Z 2

//
//ARDUINO I/O

//mosfet switch
#define P_SWFET 4

//battery led status PWM pulse
#define P_BATT_STATUS  5

#define A_V 0
#define A_I 1
#define P_THROTTLE 3

//RFM12B
#define RFM_IRQ  2
#define RFM_SEL  10
#define RFM_MOSI 11
#define RFM_MISO 12
#define RFM_SCK  13

//button
#define P_POWER 6

// power
#define P_GND  7
#define P_VCC  8



//bluetooth (STD SERIAL)
//#define P_BT_RX  5
//#define P_BT_TX  6

//datalogger 
#define P_DL_RX  3
#define P_DL_TX  4


#define HPF 0.98
#define LPF (1-HPF)

#endif
