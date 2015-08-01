/*
* commu.c
*
*  Created on: 2014年11月7日
*      Author: niehao
*/

#include "thedc.h"
char flag;

//通讯模块中断
void UARTIntHandler(void)
{
	uint32_t ui32Status;
    int i=0,x=0;
    char s[10];
	ui32Status = ROM_UARTIntStatus(UART1_BASE, true);
	ROM_UARTIntClear(UART1_BASE, ui32Status);
	while(ROM_UARTCharsAvail(UART1_BASE))
	{
	    s[i]=UARTCharGet(UART1_BASE);
        i++;
	}

    if(s[2]==3) move(s[0]-64,s[1]-64);
    UARTprintf("%c",s);
	IntMasterEnable();
}

//USB通讯模块中断
void
	UART0IntHandler(void)
{
	uint32_t ui32Status;
	ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

	ROM_UARTIntClear(UART0_BASE, ui32Status);
	ROM_IntMasterDisable();
	while(ROM_UARTCharsAvail(UART0_BASE))
	{
		ROM_UARTCharPutNonBlocking(UART1_BASE,ROM_UARTCharGetNonBlocking(UART0_BASE));
	}
	ROM_IntMasterEnable();
}

void
	UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
	while(ui32Count--)
	{
		ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
	}
}

void UARTConfig(){
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
	ROM_GPIOPinConfigure(GPIO_PB1_U1TX);

	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 9600,
		(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
		UART_CONFIG_PAR_NONE));
	ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 9600,
		(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
		UART_CONFIG_PAR_NONE));

	UARTStdioConfig(0, 9600, 16000000);

	ROM_IntMasterEnable();

	IntEnable(INT_UART0);
	IntEnable(INT_UART1);
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
	UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

	UARTSend((uint8_t *)"\033  Enter text: ", 16);
}

