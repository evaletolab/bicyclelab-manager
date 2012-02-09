/*
 * tools functions
 *
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_


#ifdef __cplusplus
extern "C"{
#endif

#define BLUETOOTH_PACKET_VERSION 1.0

void 	bluetooth_send_pedelec	(float i,float v,float p_a,float p_b,float ffx);
void  bluetooth_disconnect		();

#ifdef __cplusplus
}
#endif
#endif

