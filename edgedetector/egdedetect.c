#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <util/delay.h>
#include "uart.h"
#include "uart.c"
#include <avr/interrupt.h>



int readADC(int channel){
	
	int x;
	long val=0;
	
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

	
	//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running 4
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
	
	
	 //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   ADCSRA|=(1<<ADIF);	
	
	return ADCH;
}



#define forward PORTD=0xb4;
#define reverse PORTD=0x78;
#define stop    PORTD=0x00;
void main()
{
   
DDRC=0x0f;
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	uart_puts("initialized");//uart_putc('f');
	
	
	int a,s,d,f,g,h;
	
	char str[10],str1[10],str2[2],str3[2],str4[2],str5[2];
	sbi(DDRA,0);
	cbi(PORTA,0);
	sbi(DDRD,4);
	sbi(DDRD,5);
	sbi(DDRD,2);
	sbi(DDRD,3);
	sbi(DDRD,6);
	sbi(DDRD,7);
	sbi(PORTD,4);
	sbi(PORTD,5);
	//DDRD=0XFF;
	
while(1)
	
	{

		PORTC=0x0f;
		a= readADC(1);
		s= readADC(2);
		d= readADC(3);
		f= readADC(4);
		g= readADC(5);
		h= readADC(6);

		itoa(a,str,10);
		uart_puts(str);
		uart_puts("\t");
		itoa(s,str1,10);
		uart_puts(str1);

		uart_puts("\n\r");


		itoa(d,str2,10);
		uart_puts(str2);
		uart_puts("\t");
		itoa(f,str3,10);
		uart_puts(str3);

		uart_puts("\n\r");


		itoa(g,str4,10);
		uart_puts(str4);
		uart_puts("\t");
		itoa(h,str5,10);
		uart_puts(str5);

		uart_puts("\n\r");
		uart_puts("\n\r");

//_delay_ms(1000);
if((d<=6) && (f<=6) &&(s>=6)&&(g>=6)&&(h>=6)){   //forard
		sbi(PORTD,2);
		cbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);
				uart_puts("fo");

	
	}

if((d<=6) && (f<=6) &&(s>=6)&&(g<=6)&&(h<=6)){   //forard
		sbi(PORTD,2);
		cbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);		uart_puts("fo");

	
	}		

if((d<=6) && (f>=6)&&(s>=6)&&(g>=6)&&(h>=6)){    //right
		sbi(PORTD,2);
		cbi(PORTD,3);
		cbi(PORTD,7);
		sbi(PORTD,6);		uart_puts("ro");


	}	
	if((d<=6) && (f<=6)&&(s<=6)&&(g>=6)&&(h>=6)){    //right
		sbi(PORTD,2);
		cbi(PORTD,3);
		cbi(PORTD,7);
		sbi(PORTD,6);		uart_puts("ro");


	}	
if((d>=6) && (f<=6)&&(s>=6)&&(g>=6)&&(h>=6)){     //left
		
		cbi(PORTD,2);
		sbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);		uart_puts("lo");




	}	

if((d<=6) && (f<=6)&&(s<=6)&&(g<=6)&&(h<=6)){     //left
		
		cbi(PORTD,2);
		sbi(PORTD,3);
		sbi(PORTD,7);
		cbi(PORTD,6);		uart_puts("lo");
		_delay_ms(500);




	}	



}
}