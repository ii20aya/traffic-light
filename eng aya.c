#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdbool.h>
#include "macro.h"
#include "DIO.h"
#include "lcd.h"
#include "led.h"
#include "timer.h"
#include "ADC.h"
#include <avr/interrupt.h>//to use bilt in functions in interrupt
#include <stdio.h>
#include <math.h>
#include <float.h>
volatile unsigned char counter1=0;
volatile unsigned char counter_green=10;
volatile unsigned char counter_yellow=5;
volatile unsigned char counter_red=7;
unsigned short temperatue;
int main(void)
{

LED_init('D',0);
LED_init('D',1);
LED_init('D',2);
LCD_inti();
ADC_init();
timer_CTC_init_interrupt();
LCD_send_command(64);
LCD_send_data(  0x00); //first step
LCD_send_data(  0x0E);
LCD_send_data(  0x0E);
LCD_send_data(  0x05);
LCD_send_data(  0x0E);
LCD_send_data(  0x14);
LCD_send_data(  0x04);
LCD_send_data(  0x0A);

LCD_send_data(  0x00); //sec step
LCD_send_data(  0x0E);
LCD_send_data(  0x0E);
LCD_send_data(  0x14);
LCD_send_data(  0x0E);
LCD_send_data(  0x05);
LCD_send_data(  0x04);
LCD_send_data(  0x0A);

LCD_send_data(  0x00); //car
LCD_send_data(  0x0E);
LCD_send_data(  0x0E);
LCD_send_data(  0x1F);
LCD_send_data(  0x15);
LCD_send_data(  0x1F);
LCD_send_data(  0x0A);
LCD_send_data(  0x0A);


int col=0;
while(1)
{
		
		temperatue=(ADC_Read()*0.25);
		
		if(temperatue<10)
		{
			LCD_move_cursore(2,13);
			LCD_send_data(0x30);
			LCD_send_data((temperatue%10)+48);
			LCD_send_data(0xDF);
			LCD_send_data(0x43);
		}
		else if( temperatue<100)
		{
			LCD_move_cursore(2,13);
			LCD_send_data((temperatue/10)+48);
			LCD_send_data((temperatue%10)+48);
			LCD_send_data(0XDF);
			LCD_send_data(0X43);
			
		}
		else
		{
			
	}
		/////////////////////////			
			
	col=2;
	counter_green=10;
	counter_yellow=5;
	counter_red=7;
	//LCD_clear_screen();
	LCD_move_cursore(1,1);
	LCD_send_string("remaining 10 sec");
	LED_ON('D',0);
	while(counter_green>0)
	{
	
		if(counter1>=50)
		{
			counter1=0;
			counter_green--;
			col++;
			LCD_move_cursore(1,11);
			LCD_send_data(' ');
			LCD_send_data((counter_green%10)+48);
			LCD_move_cursore(2,col);
			LCD_send_data(2);
			LCD_move_cursore(2,col);
			LCD_send_data(' ');

		}
			
		}
	
	
	_delay_ms(500);
	LED_ON('D',1);
	LED_OFF('D',0);
	LCD_clear_screen();
	LCD_send_string("remaining  5 sec");
	temperatue=(ADC_Read()*0.25);
	
	if(temperatue<10)
	{
		LCD_move_cursore(2,13);
		LCD_send_data(0x30);
		LCD_send_data((temperatue%10)+48);
		LCD_send_data(0xDF);
		LCD_send_data(0x43);
	}
	else if( temperatue<100)
	{
		LCD_move_cursore(2,13);
		LCD_send_data((temperatue/10)+48);
		LCD_send_data((temperatue%10)+48);
		LCD_send_data(0XDF);
		LCD_send_data(0X43);
		
	}
	else
	{
		
	}	

	while(counter_yellow>0)
	{
		col=2;
		if(counter1>=50)
		{
			counter1=0;
			counter_yellow--;
			col++;
			LCD_move_cursore(1,11);
			LCD_send_data(' ');
			LCD_send_data((counter_yellow%10)+48);
			LCD_move_cursore(2,col);
			LCD_send_string("!");
			LCD_move_cursore(2,col);
			LCD_send_data(' ');

		}
		}

	_delay_ms(500);
	LED_ON('D',2);
	LED_OFF('D',1);
	LCD_clear_screen();
	LCD_send_string("remaining  7 sec");
	temperatue=(ADC_Read()*0.25);
	
	if(temperatue<10)
	{
		LCD_move_cursore(2,13);
		LCD_send_data(0x30);
		LCD_send_data((temperatue%10)+48);
		LCD_send_data(0xDF);
		LCD_send_data(0x43);
	}
	else if( temperatue<100)
	{
		LCD_move_cursore(2,13);
		LCD_send_data((temperatue/10)+48);
		LCD_send_data((temperatue%10)+48);
		LCD_send_data(0XDF);
		LCD_send_data(0X43);
		
	}
	else
	{
		
	}

	while(counter_red>0)
	{
		col=2;
		if(counter1>=50)
		{
			counter1=0;
			counter_red--;
			col++;
			LCD_move_cursore(1,11);
			LCD_send_data(' ');
			LCD_send_data((counter_red%10)+48);
			if(counter_red%2==0){
				LCD_move_cursore(2,col);
				LCD_send_data(0);
				LCD_move_cursore(2,col);
				LCD_send_data(' ');
			}
			if(counter_red%2==1){
				LCD_move_cursore(2,col);
				LCD_send_data(1);
				LCD_move_cursore(2,col);
				LCD_send_data(' ');
			}
			
	}
	
}
_delay_ms(500);
LED_OFF('D',2);

 }
} 




ISR(TIMER0_COMP_vect) //second mode of timer0
{
	counter1++;
}


	