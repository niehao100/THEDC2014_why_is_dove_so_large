/*
* thedc.h
*
*  Created on: 2014年11月7日
*      Author: niehao
*/
#ifndef THEDC_H_
#define THEDC_H_
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pwm.h"
#include "C:/ti/TivaWare_C_Series-2.0.1.11577/driverlib/uartstdio.h"
#include <math.h>

extern char flag;
extern int t;
extern struct Player info;
extern struct Queue queue;
extern unsigned char Position[26];
extern int head_local[2],tail_local[2],center_local[2];
extern char S_flag;
extern char senser_flag;

void 	move();
void 	move_stright(int);
void 	turn_left();
void 	turn_right();
void 	turn_left_back();
void 	turn_right_back();
void 	UARTConfig();
void	PWMConfig();
int 	head(unsigned char,unsigned char);
void	move_to(unsigned char,unsigned char);
int 	head_exact(unsigned char,unsigned char);
void	move_to_exact(unsigned char,unsigned char);

void	UARTSend(const uint8_t *, uint32_t );
void  	UARTIntHandler(void);

//传感器
void	Timer0IntHandler(void);
void 	TimerConfig();
void	Timer1IntHandler(void);


#endif /* THEDC_H_ */
