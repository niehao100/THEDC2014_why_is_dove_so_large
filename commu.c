/*
* commu.c
*
*  Created on: 2014年11月7日
*      Author: niehao
*/

#include "thedc.h"
struct Queue {
	unsigned char q[50];
	int i;
}queue;
//平台发给选手
char flag;
unsigned char Position[26];
int UART_flag=0;

//通讯模块中断
void UARTIntHandler(void)
{
	uint32_t ui32Status;
	int j=0,k=0;
	ui32Status = ROM_UARTIntStatus(UART1_BASE, true);
	ROM_UARTIntClear(UART1_BASE, ui32Status);
	while(ROM_UARTCharsAvail(UART1_BASE))
	{
		queue.i++;if(queue.i==50) queue.i=0;
		queue.q[queue.i]=UARTCharGet(UART1_BASE);
	}

	if(queue.q[queue.i]==0x0A){
		IntMasterDisable();
		if(queue.i>26) {
			if(queue.q[queue.i-1]==0x0D&&queue.q[queue.i-26]==0x0A&&queue.q[queue.i-27]==0x0D){
				for(k=0,j=queue.i-25;k<26;k++){
					Position[k]=queue.q[j];

					j++;
				}

				head_local[0]=Position[1+5*Position[0]];
				head_local[1]=Position[2+5*Position[0]];
				tail_local[0]=Position[3+5*Position[0]];
				tail_local[1]=Position[4+5*Position[0]];
				center_local[0]=(int)((head_local[0]+tail_local[0])/2);center_local[1]=(int)((head_local[1]+tail_local[1])/2);
				UART_flag++;	if(UART_flag==10000) UART_flag=0;
			}
		}
		else {
				if((queue.q[(queue.i==0)?49:(queue.i-1)]==0x0D)&&(queue.q[queue.i+24]==0x0A)){
					IntMasterDisable();
					for(k=0,j=(((queue.i-25)>=0)?(queue.i-25):(queue.i+25));k<26;k++){
						Position[k]=queue.q[j];
						j++;if(j==50) j=0;
					}
					head_local[0]=Position[1+5*Position[0]];
					head_local[1]=Position[2+5*Position[0]];
					tail_local[0]=Position[3+5*Position[0]];
					tail_local[1]=Position[4+5*Position[0]];
					center_local[0]=(int)((head_local[0]+tail_local[0])/2);center_local[1]=(int)((head_local[1]+tail_local[1])/2);

					UART_flag++;	if(UART_flag==10000) UART_flag=0;
				}
						//回朔
			 }

		// UARTprintf("%c",flag);
		//for(j=0;j<26;j++)

	}
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
		ROM_UARTCharPutNonBlocking(UART0_BASE,ROM_UARTCharGetNonBlocking(UART0_BASE));
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
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	ROM_GPIOPinConfigure(GPIO_PB0_U1RX);

	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

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

