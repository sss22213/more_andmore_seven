/*
 * clock.h
 *
 * Created: 2016/11/21 下午 03:38:09
 *  Author: bohung
 */ 
#ifndef CLOCK_H_
#define CLOCK_H_
#define Debug_mode 0
#include "reg.h"
#include <stdlib.h>
#include <assert.h>
#include <util/delay.h>
//define clock
typedef struct _four_clock four_clock;
//define member function 
typedef void (*ptr_Chioce)(four_clock*);
typedef void (*ptr_outSeven)(four_clock*);
typedef void (*ptr_setSeven)(four_clock*,int,int);
//define object
typedef struct _four_clock four_clock;

typedef struct _four_clock
{
	unsigned char *Seven;
	int choice;
	int *number;
	ptr_outSeven out_Seven;
	ptr_Chioce Seven_Choice;
	ptr_setSeven set_Seven;
}four_clock;

four_clock* new_four_clock(void);

//member function
void Seven_out(unsigned char x);
void Choice(four_clock*);
void outSeven(four_clock*);
void setSeven(four_clock*,int,int);
void system_Init(void);
//timer
unsigned long timer;

#endif /* CLOCK_H_ */