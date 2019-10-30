//=============================================================================================
//
//	Author				:Cytron Technologies		
//	Project				:DIY Project
//	Project description	:PR6-Bluetooth Remote Control
//  Date				:21 May 2009
//
//=============================================================================================


//=============================================================================================
// Include file
//=============================================================================================
#include <pic.h>


//=============================================================================================
// Configuration
//=============================================================================================
__CONFIG(0x3F32);


//=============================================================================================
//Define
//=============================================================================================
#define seg PORTD				// define 7 segment as PORTD 


//==============================================================================================
// Function Prototype
// User can write all the necessary function here
//==============================================================================================
	
unsigned char a;

void init(void)					// subroutine to initialize  			
{	
	SPBRG=0x0A;					// set baud rate as 115200 baud
	BRGH=1;	
	TXEN=1;
	CREN=1;
	SPEN=1;
	TRISD = 0b00000000;			
	seg   = 0b00000000;			
}

void display(unsigned char c)		// subrountine to display the text on the screen	
{
	while (TXIF == 0);
	TXREG = c;	
}

unsigned char receive(void)			// subrountine to receive text from PC
{
	while (RCIF == 0);
	a = RCREG;
	return a;
}


//================================================================================================
//	Main Function
//	This is the main function where program start to execute 
//================================================================================================
void main(void)
{
	init();

	while(1)				// Wait for 'ok' to be entered by user
	{
		a = receive();								
		if (a == 'o') 						
			{
				a = receive();
				if (a == 'k') break;
			}
	}


		display('C');			// Text will display on Hyperterminal after 'ok' is entered
		display('y');
		display('t');
		display('r');
		display('o');
		display('n');
		display(0x0a);			//Go to new line	
		display(0x0d);			
		display('P');
		display('r');
		display('e');
		display('s');
		display('s');
		display(0x20);			// Space
		display('a');
		display('n');
		display('y');
		display(0x20);			// Space
		display('n');
		display('u');
		display('m');		
		display('b');
		display('e');
		display('r');

		seg = 1;	

		// wait for number and display it on 7 segment
        // The number display on 7 segment is depends on what number entered in Hyperterminal.
		while(1)	
		{
			a = receive(); 
			if (a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9'||a=='0')
			{
				seg = a-0x30;
			}
		}
}


