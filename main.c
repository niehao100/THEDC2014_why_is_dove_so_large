
#include "thedc.h"

void Init(void){

	FPUEnable();
	FPULazyStackingEnable();
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
		SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


	//
	// Enable the GPIO pins for the LED (PF2).
	//
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2|GPIO_PIN_3);
	//传感器
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
	// GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

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
	IntRegister(4,UART0IntHandler);
	IntRegister(0,Timer0IntHandler);
    IntRegister(2,GPIOA6INT);
}



int main(void)
{

	void (*target[4])(int judge)={&target1,&target2,&target3,&target4};
	int i=0,x=0,y=0,time=0,k=0;
	char score=0,_place=0,p=0;
	Init(); //初始化针脚什么的

	//for(i=0;i<100;i++) move_stright(7);

	begin:
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
	while(1){
		SysCtlDelay(SysCtlClockGet()/90);

		if(Position[23]==0x01) break;
	}
	SysCtlDelay(SysCtlClockGet()/90);

	S_flag=2;

//比赛逻辑
	for(;;){
		if(Position[23]==0) exit(0);
		if((check[0]==0)&&(check[1]==0)&&(check[2]==0)&&(check[3]==0))
		for(i=0;i<4;i++)	check[i]=1;
		_place=Place();
		p=(int)(_place/10)-1;
		S_flag=2;
		if(check[p])	{target[p](_place);check[p]=0;}
		else{
			if(check[(p==0)?3:(p-1)]){ target[(p==0)?3:(p-1)](_place);check[(p==0)?3:(p-1)]=0;continue;}
			if(check[(p==3)?0:(p+1)]){ target[(p==3)?0:(p+1)](_place);check[(p==3)?0:(p+1)]=0;continue;}
			if(check[(p>1)?(p-2):(p+2)]){	target[(p>1)?(p-2):(p+2)](_place); check[(p>1)?(p-2):(p+2)]=0;continue;}
		}
	}

	goto begin;

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
	return 0;

}






