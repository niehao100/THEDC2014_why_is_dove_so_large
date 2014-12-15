/*
* move.c
*
*  Created on: 2014年11月7日
*      Author: niehao
*/
#include "thedc.h"
#include <math.h>
int head_local[2],tail_local[2],center_local[2];
extern int UART_flag;
extern struct Player info;

void left_move(int v)
{
	int i=0,j=0;
	if(v>0){
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, ahead);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x2);
		SysCtlDelay(v*1600+1);
	}
	else{
		v=-v;
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, back);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
		SysCtlDelay(v*1600+1);
	}
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, stop);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay((12-v)*1600+1);
}

void right_move(int v)
{
	int i=0,j=0;
	if(v>0){
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, ahead);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x4);
		SysCtlDelay((v+2)*1600+1);
	}
	else{
		v=-v;
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, back);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 12);
		SysCtlDelay((v+2)*1600+1);
	}
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, stop);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay((10-v)*1600+1);
}

void move_stright(int v){
	right_move(v);
	left_move(v);
}

void turn_left(){
	right_move(5);
	left_move(-5);
}

void turn_right(){
	right_move(-5);
	left_move(5);
}
void turn_left_back(){
	right_move(0);
	left_move(-4);
}
void turn_right_back(){
	right_move(-4);
	left_move(0);
}

//朝向x，y的方向
int head(unsigned char x,unsigned char y){


	double a=0,angel=0,sum=0,d=0;
	int i=0,t=0,v=0;

head_begin:
	SysCtlDelay(SysCtlClockGet()/3000);
	if(t==UART_flag) goto head_begin;
	t=UART_flag;
	if(Position[25]!=0x0A) goto head_begin;
	if(Position[23]!=1) return 0;
	if((abs(x-center_local[0])<5)&&(abs(y-center_local[1])<5)) {
				return 1;
	}
	IntMasterDisable();
	a=atan2((double)(head_local[1]-tail_local[1]),(double)(head_local[0]-tail_local[0]));
	angel=atan2((double)(y-center_local[1]),(double)(x-center_local[0]));
	angel=(angel>=0)?angel:(angel+2*3.1415926);
	a=(a>=0)?a:(a+2*3.1415926);
	if((angel-a)>=3.1415926){angel=-2*3.1415926+(angel-a);}
	else {if((a-angel)>=3.1415926)
		   angel=2*3.1415926-(-angel+a);
			else angel-=a;
	}
		sum+=angel;
		if(sum>200000) sum=0;
		IntMasterEnable();
		//PID控制
		v=(int)(4.0*angel+0.30*sum);//+8*(angel-d));
		d=angel;
		if(angel>=0.0872){
				for(i=0;i<abs(v)+4;i++) turn_right();
				goto head_begin;
		}
		if(angel<=-0.0872){
				for(i=0;i<abs(v)+4;i++) turn_left();
				goto head_begin;
		}
}


void move_to(unsigned char x,unsigned char y){
int i=0,v=0,t=0;

for(;;){
			if(S_flag<1) return;
			if((abs(x-head_local[0])<20)&&(abs(y-head_local[1])<20)) break;
				head(x,y);
				if(Position[23]==0x00) exit(0);
					t=(int)(0.9*sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1])));
				for(i=-0;i<t;i++) move_stright(7);
	}
return ;
}

void move_to_exact(unsigned char x,unsigned char y){
int i=0,v=0,t=0;

for(;;){
			if(S_flag<1) return;
			if(Position[23]==0x00) exit(0);
			if(score_change!=score) break;
			if((Position[22]-time)<5) break;
				if((abs(x-center_local[0])<4)&&(abs(y-center_local[1])<4)) return;

				t=(int)(0.9*sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1]))+10);

				if(	 ((head_local[0]-tail_local[0])*(x-center_local[0])+(head_local[1]-tail_local[1])*(y-center_local[1]))<0	 )
				{
					v=-4;
					head((unsigned char)(2*center_local[0]-x),(unsigned char)(2*center_local[1]-y));
				}
				else	{
					v=4;
					head(x,y);
				}
				if((abs(x-center_local[0])<5)&&(abs(y-center_local[1])<5)) return;
			for(i=0;i<t;i++) move_stright(v);
	}
return ;
}
