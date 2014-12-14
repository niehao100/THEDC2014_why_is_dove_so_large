#include "thedc.h"


int check[4]={1,1,1,1};
void beat_enemy(int px,int py){
	int i=0;
	int x=Position[enemy_flag*5+1],
		y=Position[enemy_flag*5+2];
	if((abs(x-px)>15)||(abs(y-py)>15)) return;
	if(((center_local[0]-Position[enemy_flag*5+1])*(center_local[0]-Position[enemy_flag*5+1])
			+(center_local[1]-Position[enemy_flag*5+2])*(center_local[1]-Position[enemy_flag*5+2]))
			<400) {
		if(	 ((head_local[0]-tail_local[0])*(x-center_local[0])+(head_local[1]-tail_local[1])*(y-center_local[1]))<0	 )
		{
				for(i=0;i<50;i++) move_stright(4);
				head((unsigned char)(2*center_local[0]-x),(unsigned char)(2*center_local[1]-y));
				for(i=0;i<100;i++) move_stright(-8);
		}
		else	{
			for(i=0;i<50;i++) move_stright(-4);
				head(x,y);
				for(i=0;i<100;i++) move_stright(8);
				}
		if((abs(px-center_local[0])<5)&&(abs(py-center_local[1])<5)) return;

	}
}

void get_score(int x,int y){
	int t_c=0,i=0;
	move_to_exact(x,y);
	if(S_flag>0){
			score=Position[5+5*Position[0]];
			t_c=Position[22];
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);
			for(;;){
				if(score_change!=score) {for(i=0;i<4;i++) check[i]=1;break;}
				if(!((abs(x-center_local[0])<5)&&(abs(y-center_local[1])<5))) {S_flag=1;move_to_exact(x,y);}
				for(i=0;i<50;i++);
				if(Position[23]==0x00) exit(0);
				if((Position[22]-time)<4) {for(i=0;i<4;i++) check[i]=1;break;}
				beat_enemy(x,y);
				}
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);

			}
}




int Place(unsigned char x,unsigned char y)
{
    if(x<=128&&y<=128)
    {
        if(x>=y){
            if(x>70)
                return 11;
            return 14;
        }
        if(y>70)
            return 12;
        return 13;
    }
    if(x>128&&y<=128){
        if(x>=255-y){
            if(y>70)
                return 22;
            return 23;
        }
        if(255-x>70)
             return 21;
        return 24;
    }
    if(x>128&&y>128)
    {
        if(x>=y) {
            if(255-y>70)
            	return 32;
            return 33;
        }
        if(255-x>70)
            return 31;
        return 34;
    }
    if(x<128&&y>128)
    {
        if(255-x>=y)
        {
            if(255-y>70)
            	return 42;
            return 43;
        }

        if(x>70)
        	return 41;
        return 44;
    }
    return 0;
}

void target1(int judge)
{

	if(((int)(judge/10))==1)
    {
        if(judge%10==1)
        {
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
            return;
        }
        if(judge%10==2)
        {
        	move_to(_Px,96);
        	//move_to_exact(_Px,96);
            get_score(_Px,_Py);
        	return;
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);//竖直移动到II区
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);//水平移动到I区
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
    }
    if(((int)(judge/10))==2)
    {
        if(judge%10==1)
        {
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(140,center_local[1]);
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
    }
    if(((int)(judge/10))==3)
    {
        if(judge%10==1)
        {
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            head(_Px,_Py);
            get_score(_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            //move_to_exact(_Px,96);
            move_to(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            //move_to_exact(96,_Py);
            move_to(96,_Py);
            get_score(_Px,_Py);
        }
    }
    if(((int)(judge/10))==4)
    {
        if(judge%10==1)
        {
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            move_to(_Px,96);
            //move_to_exact(_Px,96);
            get_score(_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);
            move_to(96,_Py);
            //move_to_exact(96,_Py);
            get_score(_Px,_Py);
        }
    }
}

void target2(int judge)
{
    if(((int)(judge/10))==1)
    {
        if(judge%10==1)
        {
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);//竖直移动到II区
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            head(255-_Px,_Py);
            get_score(255-_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);//水平移动到I区
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
    }
    if(((int)(judge/10))==2)
    {
        if(judge%10==1)
        {
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
    }
    if(((int)(judge/10))==3)
    {
        if(judge%10==1)
        {
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
    }
    if(((int)(judge/10))==4)
    {
        if(judge%10==1)
        {
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(255-_Px,96);
            //move_to_exact(255-_Px,96);
            get_score(255-_Px,_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(150,_Py);
            //move_to_exact(150,_Py);
            get_score(255-_Px,_Py);
        }
    }
}


void target3(int judge)
{
    if(((int)(judge/10))==1)
    {
        if(judge%10==1)
        {
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);//竖直移动到II区
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);//水平移动到I区
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==2)
    {
        if(judge%10==1)
        {
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==3)
    {
        if(judge%10==1)
        {
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==4)
    {
        if(judge%10==1)
        {
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(255-_Px,150);
            //move_to_exact(255-_Px,150);
            get_score(255-_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(150,255-_Py);
            //move_to_exact(150,255-_Py);
            get_score(255-_Px,255-_Py);
        }
    }
}

void target4(int judge)
{
    if(((int)(judge/10))==1)
    {
        if(judge%10==1)
        {
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);//竖直移动到II区
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);//水平移动到I区
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==2)
    {
        if(judge%10==1)
        {
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],110);
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==3)
    {
        if(judge%10==1)
        {
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(110,center_local[1]);
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
    }
    if(((int)(judge/10))==4)
    {
        if(judge%10==1)
        {
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
        if(judge%10==2)
        {
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==3)
        {
            move_to(center_local[0],150);
            move_to(_Px,165);
            //move_to_exact(_Px,165);
            get_score(_Px,255-_Py);
        }
        if(judge%10==4)
        {
            move_to(150,center_local[1]);
            move_to(110,255-_Py);
            //move_to_exact(110,255-_Py);
            get_score(_Px,255-_Py);
        }
    }
}

