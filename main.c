
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
}



int main(void)


{
	int i=0,x=0,y=0,time=0,k=0;
	char score=0;
	Init(); //初始化针脚什么的
	begin:
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

	while(1){
		SysCtlDelay(SysCtlClockGet()/50);

		if(Position[23]==0x01) break;
	}
	move_to(200,122);
	move_to_exact(200,122);
//比赛逻辑
/*

first:
S_flag=1;
move_to(54,100);
head((char)((head_local[0]+tail_local[0])/2),0);
S_flag=1;
for(i=0;i<200;i++) move_stright(3);

if(Position[23]==0x00) goto begin;
if(S_flag==1){
		for(i=0;i<150;i++) move_stright(-3);
		move_to(54,56);
		time=Position[22];
		score=Position[5];
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

			for(;;){
				for(i=0;i<500;i++);
				if(Position[23]==0x00) goto begin;
				if(Position[22]<(time-7)) break;
				if(Position[5]!=score)   break;
			}
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);

}
	S_flag=1;
	for(i=0;i<100;i++)
	move_stright(-4);
	if(Position[23]==0x00) goto begin;


second:
for(i=0;i<75;i++) turn_left();
S_flag=1;
move_to(54,160);
head((char)((head_local[0]+tail_local[0])/2),255);
S_flag=1;
for(i=0;i<200;i++) move_stright(3);

if(Position[23]==0x00) goto begin;
if(S_flag==1){
	for(i=0;i<150;i++) move_stright(-3);
	move_to(54,196);
	time=Position[22];
	score=Position[5];
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

		for(;S_flag==1;){
			for(i=0;i<500;i++);
			if(Position[23]==0x00) goto begin;
			if(Position[22]<(time-7)) break;
			if(Position[5]!=score){

			break;
				}
			}
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);

	}
	S_flag=1;
	for(i=0;i<60;i++)
	move_stright(-4);
	if(Position[23]==0x00) goto begin;




third:
for(i=0;i<45;i++) turn_left();
head(255,50);
		//
			for(i=0;i<400;i++) move_stright(6);
		//
S_flag=1;
move_to(204,160);
for(i=0;i<40;i++)	turn_right();
head((char)((head_local[0]+tail_local[0])/2),255);
S_flag=1;
for(i=0;i<200;i++) move_stright(3);

if(Position[23]==0x00) goto begin;
if(S_flag==1){
	for(i=0;i<150;i++) move_stright(-4);
	move_to(201,196);
	score=Position[5];
	time=Position[22];
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

	for(;S_flag==1;){
		for(i=0;i<500;i++);
		if(Position[23]==0x00) goto begin;
		if(Position[22]<(time-7)) break;
		if(Position[5]!=score) 		break;
		}
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);

	}
	S_flag=1;
	for(i=0;i<100;i++)
	move_stright(-4);
	if(Position[23]==0x00) goto begin;

fourth:
for(i=0;i<80;i++) turn_right();
head(195,56);
for(i=0;i<100;i++) move_stright(4);
if(Position[23]==0x00) goto begin;
S_flag=1;
move_to(195,100);
head((char)((head_local[0]+tail_local[0])/2),0);
S_flag=1;
for(i=0;i<200;i++) move_stright(3);

if(Position[23]==0x00) goto begin;
if(S_flag==1){
	for(i=0;i<150;i++) move_stright(-3);
	move_to(201,57);
	time=Position[22];
	score=Position[5];
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

		for(;S_flag==1;){
			for(i=0;i<500;i++);
			if(Position[23]==0x00) goto begin;
			if(Position[22]<(time-7)) break;
			if(Position[5]!=score)			break;

			}
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);

}
	S_flag=1;
	for(i=0;i<100;i++)
	move_stright(-5);
	if(Position[23]==0x00) goto begin;
	for(i=0;i<50;i++) turn_left();
				head(0,112);
				head(0,112);
				//
	for(i=0;i<350;i++) move_stright(6);
				//
	move_to(62,110);


goto first;
*/
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
	return 0;

}






