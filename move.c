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
	if(v>0){
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, ahead);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x2);
		SysCtlDelay(v*SysCtlClockGet()/10000+1);//0.01s
	}
	else{
		v=-v;
		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, back);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
		SysCtlDelay(v*SysCtlClockGet()/10000+1);
	}
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3, stop);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay((12-v)*SysCtlClockGet()/10000+1);
}

void right_move(int v)
{
	if(v>0){
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, ahead);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x4);
		SysCtlDelay(v*SysCtlClockGet()/10000+1);
	}
	else{
		v=-v;
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, back);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 12);
		SysCtlDelay(v*SysCtlClockGet()/10000+1);
	}
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, stop);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay((12-v)*SysCtlClockGet()/10000+1);
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


	double a=0,angel=0,sum=0;
	int i=0,t=0,v=0;

head_begin:
	SysCtlDelay(SysCtlClockGet()/90);
	if(t==UART_flag) goto head_begin;
	t=UART_flag;
	IntMasterDisable();
	if(Position[25]!=0x0A) goto head_begin;
	if(Position[23]==0x00) {IntMasterEnable();return 0;}
	if(fabs(x-center_local[0])<5&&fabs(y-center_local[1])<5) {
			IntMasterEnable();
			return 1;
	}

	a=atan2((double)(head_local[1]-tail_local[1]),(double)(head_local[0]-tail_local[0]));
	angel=atan2((double)(y-center_local[1]),(double)(x-center_local[0]));
	angel=(angel>=0)?angel:(angel+2*3.1415926);
	a=(a>=0)?a:(a+2*3.1415926);
	if((angel-a)>=3.1415926){angel-=2*3.1415926;}
	if((a-angel)>=3.1415926){a-=2*3.1415926;}
	IntMasterEnable();
	sum+=angel-a;
		//PID控制
		v=(int)(5*(angel-a)+sum/(3));
		if(a<=(angel-5*0.0175)){
				for(i=0;i<v+5;i++) turn_right();
				goto head_begin;
		}
		if(a>=(angel+5*0.0175)){
				for(i=0;i<abs(v)+5;i++) turn_left();
				goto head_begin;
		}
	IntMasterEnable();
	return 1;
}


void move_to(unsigned char x,unsigned char y){
int i=0,v=0,t=0;

for(;S_flag==1;){
			if((abs(x-head_local[0])<20)&&(abs(y-head_local[1])<20)) break;
				head(x,y);
				if(Position[23]==0x00) return;
				t=(int)(sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1])));
			for(i=-0;i<t;i++) move_stright(8);
	}
return ;
}

void move_to_exact(unsigned char x,unsigned char y){
int i=0,v=0,t=0;

for(;S_flag==1;){

			if((abs(x-center_local[0])<5)&&(abs(y-center_local[1])<5)) return;

				t=(int)(3*sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1]))+10);

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
			if(Position[23]==0x00) return;
	}
return ;
}
