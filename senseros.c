/*
* senseros.c
*
*  Created on: 2014��11��8��
*      Author: niehao
*/

#include "thedc.h"

int t=1000,i=0;
int S_flag=2;

//������
void GPIOA6INT(void){
	GPIOIntClear(INT_GPIOA, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_7);
	IntDisable(INT_GPIOA);
	for(t=0;t<1000000&&(GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6)||GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_5)||GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7));t++);

	if(t>240) {
		/*if((senser_flag%3)==0)	{*/for(i=0;i<50;i++) move_stright(-4); S_flag--;//}
		/*if((senser_flag%3)==1)	{for(i=0;i<100;i++) turn_right_back();S_flag=1;}
		if((senser_flag%3)==2)	{for(i=0;i<50;i++) turn_left_back(); S_flag=1;}*/
	}

	IntEnable(INT_GPIOA);

}
