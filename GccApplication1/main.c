/*
 * GccApplication1.c
 *
 * Created: 2016/11/21 下午 03:11:57
 * Author : bohung
 */ 

#include "clock.h"
#include "reg.h"

void modify(four_clock * obj)
{
	obj->set_Seven(obj,0,0);
	int m=0;
	int s=0;
	int m_flag=0;
	int s_flag=0;
	while(PINC!=0x04)
	{
		obj->set_Seven(obj,m,s);
		//
		if(PINC==0x08 && m_flag>5)
		{
			m++;
			m_flag=0;
		}
		else if(PINC==0x08)m_flag++;
		
		if(PINC==0x10 && s_flag>5)
		{
			s++;
			s_flag=0;
		}
		else if(PINC==0x10)s_flag++;
		s=s>59?0:s;
		m=m>11?0:m;
	}
	timer=m*60+s;
}
int main(void)
{
	four_clock *myclock=new_four_clock();
	system_Init();
	int m=0,s=0;
    while (1) 
    {
		m=timer/60;
		s=timer%60;
		myclock->set_Seven(myclock,m,s);
		if(PINC==0x02)
		{
			modify(myclock);
		}
    }
}
ISR(TIMER1_COMPA_vect)
{
	timer=((timer>720)?0:timer);
	timer++;
}

