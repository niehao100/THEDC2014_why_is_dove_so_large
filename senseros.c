/*
* senseros.c
*
*  Created on: 2014Äê11ÔÂ8ÈÕ
*      Author: niehao
*/

#include "thedc.h"

int t_s=0,i=0;
int S_flag=1;

//³¬Éù²¨
void GPIOA6INT(void){
	GPIOIntClear(INT_GPIOA, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_7);
	IntDisable(INT_GPIOA);
	for(t_s=0;t_s<10000&&(GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_5)||GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7));t_s++);


		if(((senser_flag%2)==0)&&t_s>290)	{for(i=0;i<150;i++) move_stright(-3);if((abs(abs(center_local[0]-128)-(128-_Px))<35)&&(abs(abs(center_local[1]-128)-(128-_Py))<35)) S_flag--;}
		if(((senser_flag%2)==1)&&t_s>250)	{for(i=0;i<100;i++) move_stright(4);if((abs(abs(center_local[0]-128)-(128-_Px))<35)&&(abs(abs(center_local[1]-128)-(128-_Py))<35)) S_flag--;}/*
		if((senser_flag%3)==2)	{for(i=0;i<50;i++) turn_left_back(); S_flag=1;}*/
		if(S_flag<-1000) S_flag=-10;
	//UARTprintf("%d ",t);
	IntEnable(INT_GPIOA);

}
