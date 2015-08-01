
#include "thedc.h"

void Init(void){

	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
		SYSCTL_XTAL_16MHZ);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//
	// Enable the GPIO pins for the LED (PF2).
	//
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	IntEnable(INT_GPIOA);
	UARTConfig();
	PWMConfig();
	IntRegister(0,UARTIntHandler);
	//IntRegister(1,GPIOA6INT);
	//IntRegister(0,Timer0IntHandler);
}



int main(void)
{

	Init(); //初始化针脚什么的
	move(1,1);
/*	int i=0,x=0,y=0,time=0,k=0;
	char score=0;

begin:
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

	while(1){
		SysCtlDelay(SysCtlClockGet()/50);

		if(Position[23]==0x01) break;
	}

	move_to(200,122);
	//head_exact(200,122);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x04);*/
	while(1);
}




