/*
* move.c
*
*  Created on: 2014年11月7日
*      Author: niehao
*/
#include "thedc.h"
#define ahead 0x4
#define back 0x8
#define stop 0xc
int UART_flag;

void PWMConfig(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	  SysCtlDelay(2);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);

	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6|GPIO_PIN_7);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_1,
	                     PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

	PWMGenConfigure(PWM0_BASE, PWM_GEN_0,
	                     PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0,100);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1,100);
}

void move(int vl,int vr)
{
    uint32_t lout=vl>0?PWM_OUT_2:PWM_OUT_3,rout=vr>0?PWM_OUT_0:PWM_OUT_1,
    			lb=vl>0?PWM_OUT_2_BIT:PWM_OUT_3_BIT,rb=vr>0?PWM_OUT_0_BIT:PWM_OUT_1_BIT;
    vl=vl>0?vl:-vl;
    vr=vr>0?vr:-vr;

    PWMPulseWidthSet(PWM0_BASE, lout, vl);
    PWMPulseWidthSet(PWM0_BASE, rout, vr);
    PWMOutputState(PWM0_BASE,PWM_OUT_0_BIT|PWM_OUT_1_BIT|PWM_OUT_2_BIT|PWM_OUT_3_BIT, false);
    PWMOutputState(PWM0_BASE,lb|rb, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    SysCtlDelay(SysCtlClockGet()/10);

}
/*
void right_move(int v)
{
	if(v>0){
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, ahead);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x4);
		SysCtlDelay((1.5+v)*SysCtlClockGet()/10000+1);
	}
	else{
		v=-v;
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3, back);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 12);
		SysCtlDelay((1.5+v)*SysCtlClockGet()/10000+1);
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

//朝向x，y的方向 	较为粗略的
int head(unsigned char x,unsigned char y){

	double a=0,angel=0;
	int i=0,t=0,v=0,sum=0;

head_begin:
	SysCtlDelay(SysCtlClockGet()/90);
	if(t==UART_flag) goto head_begin;
	t=UART_flag;
	IntMasterDisable();
	if(Position[25]!=0x0A) goto head_begin;
	if(Position[23]==0x00) {IntMasterEnable();return 0;}
	center_local[0]=(int)((head_local[0]+tail_local[0])/2);
	center_local[1]=(int)((head_local[1]+tail_local[1])/2);

	a=atan2((double)(head_local[1]-tail_local[1]),(double)(head_local[0]-tail_local[0]));
	angel=atan2((double)(y-center_local[1]),(double)(x-center_local[0]));
	angel=(angel>=0)?angel:(angel+2*3.1415926);
	a=(a>=0)?a:(a+2*3.1415926);
	if(fabs(x-head_local[0])<4&&fabs(y-head_local[1])<4) {
		IntMasterEnable();
		return 1;
	}
	if((angel-a)>=3.1415926){angel-=2*3.1415926;}
	if((a-angel)>=3.1415926){a-=2*3.1415926;}
	IntMasterEnable();
	sum+=(angel-a);
	//PID控制
	v=(int)(8*(angel-a)+sum/(0.5));
	if(a<=(angel-10*0.0175)){
			for(i=0;i<v+6;i++) turn_right();
			goto head_begin;
	}
	if(a>=(angel+10*0.0175)){
			for(i=0;i<-v+6;i++) turn_left();
			goto head_begin;
	}
	IntMasterEnable();
	return 1;
}

//朝向x，y的方向		精确对准
int head_exact(unsigned char x,unsigned char y){

	double a=0,angel=0;
	int i=0,t=0,v=0,sum=0;

head_begin:
	SysCtlDelay(SysCtlClockGet()/90);
	if(t==UART_flag) goto head_begin;
	t=UART_flag;
	IntMasterDisable();
	if(Position[25]!=0x0A) goto head_begin;
	if(Position[23]==0x00) {IntMasterEnable();return 0;}
	center_local[0]=(int)((head_local[0]+tail_local[0])/2);center_local[1]=(int)((head_local[1]+tail_local[1])/2);

	a=atan2((double)(head_local[1]-tail_local[1]),(double)(head_local[0]-tail_local[0]));
	angel=atan2((double)(y-center_local[1]),(double)(x-center_local[0]));
	angel=(angel>=0)?angel:(angel+2*3.1415926);
	a=(a>=0)?a:(a+2*3.1415926);
//	UARTprintf("%d  %d %d %d\n",(int)(100*angel/3.1415926),(int)(100*a/3.1415926),(y-head_local[1]),(x-head_local[0]));
	if(fabs(x-head_local[0])<4&&fabs(y-head_local[1])<4) {
		IntMasterEnable();
		return 1;
	}
	if((angel-a)>=3.1415926){angel-=2*3.1415926;}
	if((a-angel)>=3.1415926){a-=2*3.1415926;}
	IntMasterDisable();
	sum+=angel-a;
	//PID控制
	v=6;//(int)(5*(angel-a)+sum/(3));
	if(a<=(angel-5*0.0175)){
			for(i=0;i<v+6;i++) turn_right();
			goto head_begin;
	}
	if(a>=(angel+5*0.0175)){
			for(i=0;i<abs(v)+6;i++) turn_left();
			goto head_begin;
	}
	IntMasterEnable();
	return 1;
}



void move_to(unsigned char x,unsigned char y){
int i=0,v=0,t=0;

for(;S_flag==1;){
			if(abs(x-center_local[0])<30&&abs(y-center_local[1])<30) break;
				head_exact(x,y);
				if(Position[23]==0x00) return;
				v=8;
				t=(int)(sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1])));
			for(i=-0;i<t;i++) move_stright(v);
	}
return ;
}

void move_to_exact(unsigned char x,unsigned char y){
int i=0,v=0,t=0;
for(;S_flag==1;){
			if(abs(x-center_local[0])<5&&abs(y-center_local[1])<5) break;
			head_exact(x,y);
				t=(int)(sqrt((x-center_local[0])*(x-center_local[0])+(y-center_local[1])*(y-center_local[1])))+5;
				v=4;

				if(		( (x-tail_local[0])*(x-tail_local[0])+(y-tail_local[1])*(y-tail_local[1]) )
						>( (x-head_local[0])*(x-head_local[0])+(y-head_local[1])*(y-head_local[1]) )		 )
					v=-4;

			for(i=-0;i<t;i++) move_stright(v);
			if(Position[23]==0x00) return;
	}
return ;
}
*/
