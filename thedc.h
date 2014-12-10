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
#include "C:/ti/TivaWare_C_Series-2.0.1.11577/driverlib/uartstdio.h"

/*struct Player
{
	//小车的编号(1——4之间的某一个)
	unsigned char player_loc;
	//小车1头尾坐标及分数(若是对手，则头尾的坐标一样)
	unsigned char player1_head_x;
	unsigned char player1_head_y;
	unsigned char player1_rear_x;
	unsigned char player1_rear_y;
	unsigned char player1_score;
	//小车2头尾坐标及分数(若是对手，则头尾的坐标一样)
	unsigned char player2_head_x;
	unsigned char player2_head_y;
	unsigned char player2_rear_x;
	unsigned char player2_rear_y;
	unsigned char player2_score;
	//小车3（若存在，否则发0）头尾坐标及分数,(若是对手，则头尾的坐标一样)
	unsigned char player3_head_x;
	unsigned char player3_head_y;
	unsigned char player3_rear_x;
	unsigned char player3_rear_y;
	unsigned char player3_score;
	//小车4（若存在，否则发0）头尾坐标及分数,(若是对手，则头尾的坐标一样)
	unsigned char player4_head_x;
	unsigned char player4_head_y;
	unsigned char player4_rear_x;
	unsigned char player4_rear_y;
	unsigned char player4_score;
	//坑的占用情况
	unsigned char available;
	//比赛剩余时间
	unsigned char time;
	//比赛结束信号，1表示开始，0结束
	unsigned char is_over;
	//结尾校验位
	unsigned char end0;//0x0D;
	unsigned char end1;//0x0A;
};
struct Player info;
*/



extern char flag;
extern int t;
extern struct Player info;
extern struct Queue queue;
extern unsigned char Position[26];
extern int head_local[2],tail_local[2],center_local[2];
extern char S_flag;//传感器状态
extern char senser_flag;//判断是那个传感器
//move
#define ahead 0x4
#define back 0x8
#define stop 0xc
void move_stright(int);
void left_move();
void right_move();
void turn_left();
void turn_right();
void turn_left_back();
void turn_right_back();
int head(unsigned char,unsigned char);
void move_to(unsigned char,unsigned char);
void move_to_exact(unsigned char x,unsigned char y);
//通信函数
void UARTSend(const uint8_t *, uint32_t );
void UARTConfig();
void UARTIntHandler(void);

//传感器
void Timer0IntHandler(void);
void TimerConfig();
void Timer1IntHandler(void);
void GPIOA6INT(void);

//逻辑
void target1(int judge);
void target2(int judge);
void target3(int judge);
void target4(int judge);
extern void (*target[4])(int judge);
extern int check[4];
#endif /* THEDC_H_ */
