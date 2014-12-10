
#include "thedc.h"


void Init(void){

	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
		SYSCTL_XTAL_16MHZ);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


	//
	// Enable the GPIO pins for the LED (PF2).
	//
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3);
	//传感器
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
	// ROM_GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_6,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_HIGH_LEVEL);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_6);

	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_5,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_HIGH_LEVEL);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_5);

	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_HIGH_LEVEL);
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
	GPIOIntEnable(GPIO_PORTA_BASE, GPIO_INT_PIN_7);

	IntEnable(INT_GPIOA);



	UARTConfig();
	TimerConfig();

	IntRegister(1,UARTIntHandler);
	IntRegister(0,Timer0IntHandler);
	IntRegister(2,GPIOA6INT);
}



int main(void)


{
	int i=0;
	char place=0,p=0;

	Init(); //初始化针脚什么的
	begin:
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);


	while(1){
		SysCtlDelay(SysCtlClockGet()/90);

		if(Position[23]==0x01) break;
	}
	move_to(200,122);
	move_to_exact(200,122);
	move_to(50,122);
	move_to_exact(50,122);


//比赛逻辑
	for(;Position[23]==0x01;){
		if((check[0]==0)&&(check[1]==0)&&(check[2]==0)&&(check[3]==0))
		for(i=0;i<4;i++)	check[i]=1;
		place=Place();
		p=(int)(place/10)-1;
		if(check[p])	target[p](place);
		else{
			if(check[(p==0)?3:(p-1)]){ target[(p==0)?3:(p-1)](place);continue;}
			if(check[(p==3)?0:(p+1)]){ target[(p==3)?0:(p+1)](place);continue;}
			if(check[(p>1)?(p-2):(p+2)])	{target[(p>1)?(p-2):(p+2)](place); continue;}
		}
	}

	goto begin;

}






