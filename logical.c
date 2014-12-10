#include "thedc.h"
/*
int check[4]={1,1,1,1};
void (*target[4])(int judge)={&target1,&target2,&target3,&target4};

void get_score(int x,int y){
	int score=0,time=0;
	move_to_exact(x,y);
	if(S_flag){
			score=Position[5+5*Position[0]];
			time=Position[22];
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
			for(;S_flag==1;){
				for(i=0;i<500;i++);
				if(Position[23]==0x00) goto begin;
				if(Position[22]<(time-7)) break;
				if(Position[5+5*Position[0]]!=score) 	break;
				}
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
			for(i=0;i<4;i++) check[i]=1;
				check[int(place/10)]=0;
				continue;
			}
			else{
					check[int(place/10)]=0;S_flag=1;
				}
}




int place(int head_x,int head_y)
{
    if(head_x<=127.5&&head_y<=127.5)
    {
        if(head_x>=head_y){
            if(head_x>70)
                return 11;
            return 14;
        }
        if(head_y>70)
            return 12;
        return 13;
    }
    if(head_x>127.5&&head_y<=127.5){
        if(head_x>=255-head_y){
            if(head_y>70)
                return 22;
            return 23;
        }
        if(255-head_x>70)
             return 21;
        return 24;
    }
    if(head_x>127.5&&head_y>127.5)
    {
        if(head_x>=head_y) {
            if(255-head_y>70)
            	return 32;
            return 33;
        }
        if(255-head_x>70)
            return 31;
        return 34;
    }
    if(head_x<127.5&&head_y>127.5)
    {
        if(255-head_x>=head_y)
        {
            if(255-head_y>70)
            	return 42;
            return 43;
        }

        if(head_x>70)
        	return 41;
        return 44;
    }
}

void target1(int judge)//鏈濈涓�釜鍧戣蛋
{
    if(judge/10==1)//鍦ㄤ竴鍙峰ぇ鍖哄煙
    {
        move_to(55,55);
    }
    if(judge/10==2)//鍦ㄤ簩鍙峰ぇ鍖哄煙
    {
        if(judge%10==1)//浜屽彿澶у尯鍩熼噷鐨勪竴鍙峰皬鍖哄煙
        {
            move_to(55,55);
        }
        if(judge%10==2)//浜屽彿澶у尯鍩熼噷鐨勪簩鍙峰皬鍖哄煙
        {
            move_to(55,55);
        }
        if(judge%10==1)//浜屽彿澶у尯鍩熼噷鐨勪笁鍙峰皬鍖哄煙
        {
            move_to(55,55);
        }
        if(judge%10==2)//浜屽彿澶у尯鍩熼噷鐨勫洓鍙峰皬鍖哄煙
        {
            move_to(55,55);
        }
    }

}
*/
