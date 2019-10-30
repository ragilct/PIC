//==========================================================================
//	Author				:	Ragil.C.T
//	Project				:	Smoke Detector V1.1
//	Project description	:	Use a smoke detector to detect smoke and send 
//							its status to microcontoller to do output, blink
//							led and sound buzzer
//**This sample source code should be compiled with HI-TECH C Compiler for PIC10/12/16
//  MCUs operate in Lite Mode
//==========================================================================

//==========================================================================
//	include all necessary header file
//==========================================================================
#include <pic.h> 					//include PIC library

//==========================================================================
//	device configuration
//==========================================================================
__CONFIG ( 0x3F32 );				//configuration for the  microcontroller PIC16F877A and PIC16F876A
									//correct setting for this PIC, 0x refers to Hexadecimal whereas 3F32 means:
                            		//• Set the oscillator as high speed (HS – 4MHz to 20MHz crystal)
                            		//•	Off the Watchdog Timer
                            		//•	On Power On Timer
                            		//•	Off Brown Out Detect
                            		//•	Disable Low Voltage Program
                            		//•	Off data EEPROM Read Protect
                            		//•	Off Flash Program Write Protection
                            		//•	Off Code Protect
									//the setting of the configuration can reffered to PIC datasheet under
									//special features of the CPU

//==========================================================================
//	define label for IO
//==========================================================================
#define	buzzer		RC0				//active high, connected to RC0
#define	button1		RB0				//active low, connected to RB0
#define	button2		RB1				//active low, connected to RB1
#define	button3		RB2				//active low, connected to RB2
#define	led1		RC1				//active high, connected to RC1			
#define	led2		RC2				//active high, connected to RC2
#define	led3		RC3				//active high, connected to RC3
#define	alarm		RA0				//active high, connected to RA1, is input to PIC

//==========================================================================
//	function prototype
//==========================================================================
void delay(unsigned long data);		//delay function prototype

//==========================================================================
//	main function
//==========================================================================
void main(void)
{
	//declare and initialize variable
	unsigned char mode=0;			//declare a variable
	
	//set I/O input output
	TRISB = 0b11111111;				//set PORTB I/O direction
	TRISC = 0b00000000;				//set PORTC I/O direction
	TRISA = 0b11111111;				//set PORTA I/O direction
	
	//set ADC pin to digital I/O
	ADCON1 = 0b00000110;
						
	//initial condition
	buzzer=0;						//off buzzer
	mode=0;							//set to mode 0
	led1=0;							//off led 1
	led2=0;							//off led 2
	led3=0;							//off led 3
	
	//infinite loop
	while(1)
	{
		if(button1==0)				//if button 1 pressed, mode 1 activated
		{
			mode=1;					//set current mode to mode 1
			led1=1;					//on led 1
			led2=0;					//off led 2
			led3=0;					//off led 3
		}
		else if(button2==0)			//if button 2 pressed, mode 2 activated
		{
			mode=2;					//set current mode to mode 2
			led1=0;					//off led 1
			led2=1;					//on led 2
			led3=0;					//off led 2
		}
		else if(button3==0)			//if button 3 pressed, mode 3 activated
		{
			mode=3;					//set current mode to mode 3
			led1=0;					//off led 1
			led2=0;					//off led 2
			led3=1;					//on led 3
		}
		
		if(alarm)					//if alarm on (smoke detector send alarm to PIC)
		{
			if(mode==1)				//mode 1, blink 3 led
			{
				while(1)			//infinite loop
				{
					led1=1;			//on led 1
					led2=1;			//on led 2
					led3=1;			//on led 3
					delay(50000);	//delay for about 370ms
					led1=0;			//off led 1
					led2=0;			//off led 2
					led3=0;			//off led 3
					delay(50000);	//delay for about 370ms
				}
			}
			else if(mode==2)		//mode 2, sound buzzer without led
			{
				while(1)			//infinite loop
				{
					buzzer=1;		//on buzzer
					delay(50000);	//delay
					buzzer=0;		//off buzzer
					delay(50000);	//delay
				}
			}
			else if(mode==3)		//mode 3, sound buzzer and blink led
			{
				while(1)			//infinite loop	
				{
					led1=1;			//on led 1
					led2=1;			//on led 2
					led3=1;			//on led 3
					buzzer=1;		//on buzzer
					delay(50000);	//delay for about 370ms
					led1=0;			//off led 1
					led2=0;			//off led 2
					led3=0;			//off led 3
					buzzer=0;		//off buzzer
					delay(50000);	//delay for about 370ms
				}
			}
		}
	}	
}

//==========================================================================
//	functions
//==========================================================================

void delay(unsigned long data)		//delay function
{
	for( ;data>0;data-=1);			//the delay lenght depend
}									//on the value feed to the function
