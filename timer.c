/*
* timer.c
*
*  Created on: 2014年11月7日
*      Author: niehao
*/
#include "thedc.h"
uint32_t g_ui32Flags;
char senser_flag=0;
void TimerConfig(){
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	TimerEnable(TIMER0_BASE, TIMER_A);

	ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet()/64);

	ROM_IntEnable(INT_TIMER0A);

	ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

}


//超声波专用中断啊啊啊啊
void
	Timer0IntHandler(void)
{
	//
	// Clear the timer interrupt.
	//
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	//
	// Toggle the flag for the first timer.
	//
	HWREGBITW(&g_ui32Flags, 0) ^= 1;

	//
	// Use the flags to Toggle the LED for this timer
	//
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, g_ui32Flags << 1);
	//
	// Update the interrupt status on the display.
	//
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x2);

	//GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0x20);
	//SysCtlDelay(SysCtlClockGet()/5000);//0.01s
	//GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);

switch (senser_flag%2){
	case 0:
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,0x8);
		SysCtlDelay(SysCtlClockGet()/5000);//0.01s
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,0);
		break;
	case 1:
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x10);
		SysCtlDelay(SysCtlClockGet()/5000);//0.01s
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
		break;
	/*case 2:
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0x20);
		SysCtlDelay(SysCtlClockGet()/5000);//0.01s
		GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);
		break;
*/	}
	GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0);
	if((senser_flag++)>9998) senser_flag=0;

	//UARTprintf("next");
	//  UARTCharPutNonBlocking(UART0_BASE,ROM_UARTCharGetNonBlocking(UART1_BASE));
}



