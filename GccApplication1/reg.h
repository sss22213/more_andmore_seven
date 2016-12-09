/*
 * reg.h
 *
 * Created: 2016/11/21 下午 03:12:49
 *  Author: bohung
 */ 


#ifndef REG_H_
#define REG_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#define Seven_Init (DDRD=0xFF,DDRB=0xFF,DDRC=0x01)
#define control PORTB
#endif /* REG_H_ */