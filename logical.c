int place(int head_x,int head_y)
{
    if(head_x<=127.5&&head_y<=127.5)
    {
        if(head_x>=head_y)
        {
            if(head_x>70)
            {
                return 11;
            }
            else
            {
                return 14;
            }
        }
        else
        {
            if(head_y>70)
            {
                return 12;
            }
            else
            {
                return 13;
            }
        }
    }
    if(head_x>127.5&&head_y<=127.5)
    {
        if(head_x>=255-head_y)
        {
            if(head_y>70)
            {
                return 22;
            }
            else
            {
                return 23;
            }
        }
        else
        {
            if(255-head_x>70)
            {
                return 21;
            }
            else
            {
                return 24;
            }
        }
    }
    if(head_x>127.5&&head_y>127.5)
    {
        if(head_x>=head_y)
        {
            if(255-head_y>70)
            {
                return 32;
            }
            else
            {
                return 33;
            }
        }
        else
        {
            if(255-head_x>70)
            {
                return 31;
            }
            else
            {
                return 34;
            }
        }
    }
    if(head_x<127.5&&head_y>127.5)
    {
        if(255-head_x>=head_y)
        {
            if(255-head_y>70)
            {
                return 42;
            }
            else
            {
                return 43;
            }
        }
        else
        {
            if(head_x>70)
            {
                return 41;
            }
            else
            {
                return 44;
            }
        }
    }
}
void target1(int head_x,int head_y)//朝第一个坑走
{
    int judge;
    judge=place(head_x,head_y);
    if(judge/10==1)//在一号大区域
    {
        move_to(55,55);
    }
    if(judge/10==2)//在二号大区域
    {
        if(judge%10==1)//二号大区域里的一号小区域
        {
            head(head_x, )
            move_to(55,55);
        }
        if(judge%10==2)//二号大区域里的二号小区域
        {
            move_to(55,55);
        }
        if(judge%10==1)//二号大区域里的三号小区域
        {
            move_to(55,55);
        }
        if(judge%10==2)//二号大区域里的四号小区域
        {
            move_to(55,55);
        }
    }

}