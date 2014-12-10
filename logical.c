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
}




void target1(int head_x,int head_y)//朝第一个坑走
{


}