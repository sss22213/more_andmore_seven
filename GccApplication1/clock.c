/*
 * clock.c
 *
 * Created: 2016/11/21 下午 03:38:23
 *  Author: bohung
 */ 
#include "clock.h"
void Seven_out(unsigned char x)
{
	PORTD =((x)<<2);
	PORTC =((x>>6)&0x01);
}
void system_Init()
{
	Seven_Init;
	OCR1A = 0x3D08;
	//OCR1A = 0x0100;
	TCCR1B |= (1 << WGM12);
	// Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);
	//Set interrupt on compare match
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// set prescaler to 1024 and start the timer
	sei();
}
four_clock* new_four_clock()
{
	//Seven Table
	unsigned char Seven_table[10]=
	{
		0x3F,
		0x06,
		0x5B,
		0x4F,
		0x66,
		0x6D,
		0x7D,
		0x27,
		0x7F,
		0x67,
	};
	//init object
	four_clock* four_obj=(four_clock*)malloc(sizeof(four_clock));
	#if Debug_mode
		assert(four_obj!=NULL);
	#endif
	//Seven Table
	four_obj->Seven=(unsigned char*)malloc(10*sizeof(unsigned char));
	#if Debug_mode
		assert(four_obj->Seven!=NULL);
	#endif
	for(int i=0;i<10;i++)*((four_obj->Seven)+i)=*(Seven_table+i);
	
	//Seven_choice
	four_obj->choice=0;
	//Seven_number
	four_obj->number=(int*)malloc(4*sizeof(int));
	for(int i=0;i<4;i++)*((four_obj->number)+i)=0;
	//member function
	four_obj->Seven_Choice=Choice;
	four_obj->out_Seven=outSeven;
	four_obj->set_Seven=setSeven;
	timer=0;
	//return object
	return four_obj;
}
void Choice(four_clock* obj)
{	
	switch(obj->choice)
	{
		case 1:
			control |= 0xFC;
			control &= 0xFD;
		break; 
		case 2:
			control |= 0xFA;
			control &= 0xFB;
		break;
		case 3:
			control |= 0xF6;
			control &= 0xF7;
		break;
		case 4:
			control |= 0xEE;
			control &= 0xEF;
			break;
		default:break;
	};
}
void outSeven(four_clock* obj)
{
	//Send val to Seven
	for(int i=0;i<4;i++)
	{
		obj->choice=i+1;
		Choice(obj);
		Seven_out(obj->Seven[*(obj->number+i)]);
		_delay_ms(60);
	}
}
void setSeven(four_clock* obj,int m,int s)
{
	//
	obj->number[2]=m%10;
	obj->number[3]=m/10;
	//
	obj->number[0]=s%10;
	obj->number[1]=s/10;
	//
	obj->out_Seven(obj);
}