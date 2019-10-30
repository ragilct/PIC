#include <pic.h> 
#include<htc.h>				//to enable access to eeprom
#include "uart_io.h"		//to enable another programmed UART

__CONFIG ( 0x3F32 );		//configuration for the  microcontroller

#define LEDR		RA0		//red LED (Active HIGH)
#define LEDY		RA1		//yello LED (Active HIGH)

#define rs			RC4		//RS pin of the LCD display
#define e			RC5		//E pin of the LCD display
#define lcd_data	PORTB	//LCD 8-bit data port

#define But1		RA2		//Push button 1 (Active LOW)
#define But2 		RA3		//Push button 2 (Active LOW)
#define But3		RA4		//Push button 3 (Active LOW)

#define Buzzer		RA5		//buzzer (Active HIGH)

#define ACK_SUCCESS		0x00	//Module reply success
#define ACK_FAIL		0X01	//Module reply fail
#define ACK_NOUSER		0x05	//Module reply no user
#define ACK_USER_EXIST	0x07	//Module reply user exist
#define ACK_TIMEOUT		0x08	//Module reply timeout
#define ACK_ACCESS		0x03	//Module reply access allowed


void send_config(unsigned char data);
void delay(unsigned long data);
void send_char(unsigned char data);
void lcd_goto(unsigned char data);
void lcd_clr(void);	
void send_string(const char *s)	;
void uart_send(unsigned char data);
void send_cmd(unsigned char CMD, unsigned char P1, unsigned char P2, unsigned char P3);
unsigned char uart_receive(void);
void mode(unsigned char data);
void display_status(unsigned char type, unsigned char data0, unsigned char data);
void receive_reply(void);
void receive_reply_nodisplay(void);
void setting_repeat(void);
void CheckAdmin(void);
void AddNew(unsigned char data);
void store_eeprom(unsigned char data,unsigned char location);
unsigned char get_eeprom(unsigned char location);
void view_attendance (void);
void init_attendance(void);
void clear_attendance(void);
void upload_HT(void);		//to hyperterminal
void upload_GUI(void);		//to GUI
void allign(void);
void ResetAdmin(void);

//assign global variables
bit mode_enter=0;
bit location_enter;
bit error;
bit usertype_enter=0;
bit admin;
bit day_enter=0;
bit GUIcontrol=0;
bit export_select=0;			//local variable as flag
unsigned char location=1;
unsigned char day_count=1,day_location;
unsigned char array_resp[8];
unsigned char DAY=1;
unsigned char TEMP;
unsigned char mode_count=1;

void main(void)
{
	//set I/O ports
	TRISA = 0b00011100;					//configure PORTA I/O direction
	TRISB = 0b00000000;					//configure PORTB I/O direction
	TRISC = 0b10000000;					//configure PORTC I/O direction

	//setup ADC
	ADCON1 = 0b10000110;				//PORTA digital I/O

	//configure LCD display
	send_config(0b00000001);			//clear display at lcd
	send_config(0b00000010);			//lcd return to home 
	send_config(0b00000110);			//entry mode-cursor increase 1
	send_config(0b00001100);			//display on, cursor off and cursor blink off
	send_config(0b00111000);			//function set

	Buzzer=0;
	LEDY=0;

	//display startup message
	lcd_clr();							//clear lcd
	lcd_goto(0);						//set the lcd cursor to location 0
	send_string("Cytron Tech.");		//display "Cytron Tech."
	lcd_goto(20);						//set the lcd cursor to location 20
	send_string("PR 29");				//display "PR 29"
	delay(200000);						//delay for 100000
	lcd_clr();							//clear lcd


	//setup USART
	SPBRG = 0x40;						//set baud rate to 19200 for 20MHz Cystal
	BRGH = 1;							//baud rate high speed option
	TXEN = 1;							//enable transmission
	CREN = 1;							//enable reception
	SPEN = 1;							//enable serial port


	if((!But1) && (!But2))				//if both SW1 and SW2 are pressed ->entering reset admin mode
	{
		delay(100000);
		if((!But1) && (!But2))			//wait for release
		{
			ResetAdmin();				//reset admin mode
		}
	}

	//configure reader setting
	send_cmd(0x2E,0x00,0x10,0x00);		//configure Time out(0x10 means timeout after approx. 7s)
	delay(10);					
	receive_reply_nodisplay();			//get reply from UART but do not display
	send_cmd(0x2d,0x00,1,0x00);			//send command to configure not allowed repeat
	delay(10);					
	receive_reply_nodisplay();			//get reply from UART but do not display

	//initialize programmed UART
	uart_init(1);

	//initialize attendance
	init_attendance();
	
while(1)
{	
	while(usertype_enter==0)				//usertype_enter flag not set
	{
		lcd_goto(0);						//set lcd cursor to location 0
		send_string("1. Admin login  ");	//display option 1 
		lcd_goto(20);						//set lcd cursor to location 20
		send_string("2. User login   ");	//display option 2	
		if(!But1)							//User select Admin
		{
			while(!But1);//(!ButA);			//wait for release
			CheckAdmin();					//verify process
			if(error!=1)					//if no error return
			{
			admin = 1;						//mark user as admin
			usertype_enter=1;				//set usertype_enter flag and exit loop
			}
		}
		else if (!But2)						//User select user
		{
			while(!But2);					//wait for release
			admin = 0;						//mark user as normal user
			usertype_enter=1;				//set usertype_enter flag and exit loop
		}
	}	
	lcd_clr();	
	

	while(mode_enter==0 && admin ==1 && usertype_enter==1)	//loop if admin logging on,chosen user type and mode not selected
	{
		if((!But1))							//check whether SW1(INCREMENT) is pressed
		{		
			while((!But1));					//wait for release
			if (mode_count<8)				//if not reaching 8th mode
			mode_count++;					//increase mode
			else
			mode_count=1;					//reset back to 1st mode			
		}
		else if((!But2))					//check whether SW2(DECREMENT) is pressed
		{		
			while((!But2));					//wait for release
			if (mode_count>1)				//if not reaching 1st mode
			mode_count--;					//decrease mode
			else
			mode_count=8;					//reset back to 8th mode			
		}
		else if(!But3)						//check whether SW3(CONFIRM) is pressed	
		{
			while(!But3);					//wait for release	
			mode_enter=1;					//set mode_enter flag indicates user has chosen a mode
		}
			lcd_goto(0);					//set the lcd cursor to location 0
			send_string("Mode= ");			//display string
			lcd_goto(6);					//set the lcd cursor to location 6
			send_char(0x30+mode_count);		//display at location 6 (0x30 is ASCII code for 0)
			lcd_goto(7);					//set the lcd cursor to location 7
			send_string("/8");				//display string
			lcd_goto(20);					//set the lcd cursor to location 20
			if (mode_count==1) 	send_string("Set Day         ");		//display description for mode 1
			else if (mode_count==2)	send_string("Add a New Data  ");	//display description for mode 2
			else if	(mode_count==3)	send_string("Delete a Data   ");	//display description for mode 3
			else if (mode_count==4)	send_string("Delete All Data ");	//display description for mode 4
			else if (mode_count==5) send_string("Change Admin    ");	//display description for mode 5
			else if (mode_count==6) send_string("View Attendance ");	//display description for mode 6
			else if (mode_count==7) send_string("Clear Attendance");	//display description for mode 7
			else if (mode_count==8) send_string("Export          ");	//display description for mode 8
	}

	while(mode_enter==0 && admin ==0 && usertype_enter==1)	//loop if normal user logging on,chosen user type and mode not selected
	{	
		while(1)							//keep looping
		{
		lcd_goto(0);						//set the lcd cursor to location 0
		send_string("Today is Day ");		//display string
		lcd_goto(13);						//set the lcd cursor to location 13
		DAY=get_eeprom(0xff);				//assign value(from eeprom location 0xff) to variable
		send_char(0x30+DAY);				//display character
		lcd_goto(20);						//set the lcd cursor to location 20
		send_string("Press 3 to mark ");	//display string
		if(!But3)							//if SW3 is pressed
		{
			while(!But3);					//wait for release

			send_cmd(0x0c,0x00,0x00,0x00);		//send matching 1:N command
			lcd_clr();							//clear lcd screen
			lcd_goto(0);						//set the lcd cursor to location 0
			send_string("Place your thumb");	//display string
			lcd_goto(20);						//set the lcd cursor to location 20
			send_string("on the window");		//display string
			delay(100);
			receive_reply();					//get reply from UART

			if(!error)							//if reply returns no error
			{
				if(DAY==1)						//check day
				{	day_location=0x00;			//location to store day1 data
					store_eeprom(0x2f,day_location+3+array_resp[3]);	//get which user and mark at appropriate space
					delay(100);
				}
				else if(DAY==2)					//check day
				{	day_location=0x10;			//location to store day2 data
					store_eeprom(0x2f,day_location+3+array_resp[3]);	//get which user and mark at appropriate space
					delay(100);
				}
				else if(DAY==3)					//check day
				{	day_location=0x20;			//location to store day3 data
					store_eeprom(0x2f,day_location+3+array_resp[3]);	//get which user and mark at appropriate space
					delay(100);
				}
				else if(DAY==4)					//check day
				{	day_location=0x30;			//location to store day4 data
					store_eeprom(0x2f,day_location+3+array_resp[3]);	//get which user and mark at appropriate space
					delay(100);
				}
				else if(DAY==5)					//check day
				{	day_location=0x40;			//location to store day5 data
					store_eeprom(0x2f,day_location+3+array_resp[3]);	//get which user and mark at appropriate space
					delay(100);
				}

			}
		
		}
		}

	}
	lcd_clr();					//clear lcd display
	mode(mode_count);			//function call for mode selected
	delay(10);

	
}

}
//END MAIN FUNCTION//

//FUNCTIONS//

//function to configure LCD display
void send_config(unsigned char data)		//send lcd configuration 
{
	rs=0;									//set lcd to configuration mode
	lcd_data=data;							//lcd data port = data
	e=1;									//pulse e to confirm the data
	delay(50);
	e=0;
	delay(50);
}

//delay function
void delay(unsigned long data)			//delay function, the delay time
{										//depends on the given value
	for( ;data>0;data--);
}

//function to send character to LCD display
void send_char(unsigned char data)		//send lcd character
{
	rs=1;								//set lcd to display mode
	lcd_data=data;						//lcd data port = data
	e=1;								//pulse e to confirm the data
	delay(10);
	e=0;
	delay(10);
}

//function to set lcd cursor to desired location
void lcd_goto(unsigned char data)		//set the location of the lcd cursor
{										//if the given value is (0-15) the 
 	if(data<16)							//cursor will be at the upper line
	{									//if the given value is (20-35) the 
	 	send_config(0x80+data);			//cursor will be at the lower line
	}									//location of the lcd cursor(2X16):
	else								// -----------------------------------------------------
	{									// | |00|01|02|03|04|05|06|07|08|09|10|11|12|13|14|15| |
	 	data=data-20;					// | |20|21|22|23|24|25|26|27|28|29|30|31|32|33|34|35| |
		send_config(0xc0+data);			// -----------------------------------------------------	
	}
}

//function to clear LCD display
void lcd_clr(void)						//clear the lcd
{
 	send_config(0x01);
	delay(600);	
}

//function to send string to LCD display
void send_string(const char *s)			//send a string to display in the lcd
{          
	unsigned char i=0;
  	while (s && *s)send_char (*s++);

}

//function to transmit data by data to target device
void uart_send(unsigned char data)		//transmit data through USART
{	
	while(TXIF==0);						//only send the new data after 
	TXREG=data;							//the previous data finish sent
}

//function to send command
void send_cmd(unsigned char CMD, unsigned char P1, unsigned char P2, unsigned char P3)	//send command to fingerprint module
{
	unsigned char CHK;
	CHK = CMD^P1^P2^P3^0x00;	//calulate CHK(XOR CMD,P1,P2,P3,0)
	uart_send(0xF5);			//send first byte	(fixed)
	uart_send(CMD);				//send CMD
	uart_send(P1);				//send P1
	uart_send(P2);				//send P2
	uart_send(P3);				//send P3
	uart_send(0x00);			//send 0	(fixed)
	uart_send(CHK);				//send CHK
	uart_send(0xF5);			//send 0xF5	(fixed)
}

//function to receive data from uart buffer
unsigned char uart_receive(void)	//receive data through USART
{
	unsigned char rec_data;		
	while(RCIF==0);					//wait for data
	rec_data=RCREG;
	return rec_data;				//return received data
}

//modes operation
void mode(unsigned char data)	//check which mode to proceed
{	
	
	if (data==1)				//mode 1 set day mode
	{	
	
	while(!day_enter)			//loop while day_enter flag is not set
	{
		if(!But1)				//check whether SW1 is pressed
		{		
			while(!But1);		//wait for release
			if (day_count<5)	//if day not reaching 5
			day_count++;		//increase 
			else
			day_count=1;		//reset back to 1			
		}
		else if(!But2)			//check whether SW2 is pressed
		{		
			while(!But2);		//wait for release
			if (day_count>1)	//if mode not reaching 1
			day_count--;		//decrease
			else
			day_count=5;		//reset back to 5			
		}
		else if(!But3)			//check whether SW3 is pressed
		{
			lcd_clr();			//clear lcd display
			LEDY=1;				//yellow LED ON
			while(!But3);		//wait for release
			if(day_count==1) 						//day1
				{	store_eeprom(day_count,0xff);	//store at location 0xff in eeprom
	
				}
			else if (day_count==2) 					//day2
				{	store_eeprom(day_count,0xff);	//store at location 0xff in eeprom
	
				}
			else if (day_count==3) 					//day3
				{	store_eeprom(day_count,0xff);	//store at location 0xff in eeprom
			
				}
			else if (day_count==4) 					//day4
				{	store_eeprom(day_count,0xff);	//store at location 0xff in eeprom
	
				}
			else if (day_count==5) 					//day5
				{	store_eeprom(day_count,0xff);	//store at location 0xff in eeprom
	
				}
			lcd_goto(0);							//set the lcd cursor to location 0
			send_string("Day ");					//display string
			lcd_goto(4);							//set the lcd cursor to location 4
			send_char(0x30 + day_count);			//send character
			lcd_goto(20);							//set the lcd cursor to location 20
			send_string("Selected");				//send string
			delay(200000);
			LEDY=0;									//OFF yellow LED
			day_enter=1;							//indicates day selected
		}
			lcd_goto(0);							//set the lcd cursor to location 0
			send_string("Today is Day ");			//display string
			lcd_goto(13);							//set the lcd cursor to location 13
			send_char(0x30+day_count);				//display at location 13 (0x30 is ASCII code for 0)
			lcd_goto(14);							//set the lcd cursor to location 14
			send_string("/5");						//display string
			lcd_goto(20);							//set the lcd cursor to location 20
			send_string("Press 3 to set  ");		//display string
	}	
		day_enter=0;								//day select operation complete day_enter flag to zero again
	}
	else if (data==2)						//mode 2 add new data mode
	{	
		delay(10000);

		while(location_enter==0)			//loop until location_enter flag is set
		{
		lcd_goto(0);						//set the lcd cursor to location 0		
		send_string("Choose User     ");	//display string
		lcd_goto(20);						//set the lcd cursor to location 20
		send_string("User ");				//display string
		lcd_goto(25);						//set the lcd cursor to location 25
		send_char(0x30 + location);			//display character (numerical digit which started from 0x30 or zero)
		if(!But1)							//if SW1 is pressed
			{	
				while(!But1);				//waiting for release
				if (location<5)				//if location is not reaching 5
				location++;					//increment by 1
				else
				location=1;					//reset back to 1
			}
		else if(!But2)						//if SW2 is pressed
		{		
			while(!But2);					//wait for release
			if (location>1)					//if location is not reaching 1
			location--;						//decrement by 1
			else
			location=5;						//reset back to 5			
		}
		else if(!But3)						//if SW3 is pressed
			{
				while(!But3);				//waiting for release
				AddNew(location);			//function call for add new fingerprint into database at desired location
			}
		}
	}
	else if (data==3)						//mode 3 delete a data
	{
		delay(10000);

		while(location_enter==0)			//indicates location of data has been selected
		{
		lcd_goto(0);						//set the lcd cursor to location 0
		send_string("Choose User     ");	//display string
		lcd_goto(20);						//set the lcd cursor to location 20
		send_string("User ");				//display string
		lcd_goto(25);						//set the lcd cursor to location 25
		send_char(0x30 + location);			//display character (numerical digit which started from 0x30 or zero)
		if(!But1)							//if SW1 is pressed
			{	
				while(!But1);				//waiting for release
				if (location<5)				//if location not reaching 5
				location++;					//increment by 1
				else
				location=1;					//reset back to 1
			}
		else if(!But2)						//if SW2 is pressed
		{		
			while(!But2);					//wait for release
			if (location>1)					//if location not reaching 1
			location--;						//decrement by 1
			else
			location=5;						//reset back to 5			
		}
		else if(!But3)								//if SW3 is pressed
			{
				while(!But3);						//waiting for release
				send_cmd(0x04,0x00,location,0x03);	//send delete data command
				delay(10);
				receive_reply();					//get reply from UART
				location_enter=1;					//set location_enter flag to exit loop
			}
		}
	}
	else if (data==4)						//mode 4 delete all data
	{
		send_cmd(0x05,0x00,location,0x03);	//send command to delete all data
		delay(10);
		receive_reply();					//get reply from UART
		if(error!=1)						//if reply returns no error
		{

		do{
			lcd_goto(0);					//set the lcd cursor to location 0
			send_string("New Admin Needed");//display string
			delay(200000);
			lcd_goto(0);					//set the lcd cursor to location 0
			send_string("New Admin       ");//display string
			lcd_goto(20);					//set the lcd cursor to location 20
			send_string("Standby         ");//display string	
			delay(200000);		
			AddNew(0xFF);					//add new admin fingerrprint at location 0xFF
		   }while(error==1)	;
		}
	
		
	}

	else if(data==5)						//mode 5 change Admin
	{
		lcd_goto(0);						//set the lcd cursor to location 0
		send_string("Verification of ");	//display string
		lcd_goto(20);						//set the lcd cursor to location 20
		send_string("Formal Admin    ")	;	//display string
		delay(200000);						
		CheckAdmin();						//verify admin function call
		if(error==0)						//if returns no error
		{
		lcd_goto(0);						//set the lcd cursor to location 0
		send_string("Deleting...");			//display string
		delay(50000);
		send_cmd(0x04,0x00,0xFF,0x00);		//delete formal admin
		receive_reply();					//receive reply
		do{									
			lcd_goto(0);					//set the lcd cursor to location 0
			send_string("New Admin       ");//display string
			lcd_goto(20);					//set the lcd cursor to location 20
			send_string("Standby         ");//display string
			delay(200000);					
			AddNew(0xFF);					//add new admin fingerprint
		   }while(error==1)	;				//if returns error, repeat
		}
	}
	else if(data==6)				//mode 6 view attendance
	{	
		view_attendance();			//call view_attendance function
	}
	else if(data==7)					//mode 7 clear attendance
	{
		LEDY=1;							//yellow LED ON
		clear_attendance();				//call clear attebdance function
		lcd_goto(0);					//set the lcd cursor to location 0
		send_string("Attendance      ");//display string
		lcd_goto(20);					//set the lcd cursor to location 20
		send_string("Cleared         ");//display string
		delay(200000);
		LEDY=0;							//yellow LED OFF
	}
	else if(data==8)					//mode 8 Export
	{
	
		while(export_select==0)				//while option flag is not set
		{
		lcd_goto(0);					//set the lcd cursor to location 0
		send_string("1. Export to GUI");//display string
		lcd_goto(20);					//set the lcd cursor to location 20
		send_string("2. Export to HT ");//display string
		if(!But1)								//if SW1 is pressed
		{
				while(!But1);					//wait for release
				lcd_clr();						//clear lcd
				lcd_goto(0);					//set the lcd cursor to location 0
				send_string("Uploading...    ");//display string
				LEDR=1;							//Red LED ON
				delay(150000);					
				upload_GUI();					//call upload function
				lcd_goto(20);					//set the lcd cursor to location 20
				send_string("Done            ");//display string
				delay(100000);
				LEDR=0;							//red LED OFF
				export_select=1;				//set flag to exit loop
			
		}
		if(!But2)								//if SW2 is pressed
		{
				while(!But2);					//wait for release
				lcd_clr();						//clear lcd
				lcd_goto(0);					//set the lcd cursor to location 0
				send_string("Uploading...    ");//display string
				LEDR=1;							//red LED ON
				delay(150000);
				upload_HT();					//call upload function
				lcd_goto(20);					//set the lcd cursor to location 20
				send_string("Done            ");//display string
				delay(100000);
				LEDR=0;							//red LED OFF
				export_select=1;				//set flag to exit loop
			
		}
		}
		export_select=0;			//reset flag
	}				
mode_enter=0;						//reset flag
location_enter=0;					//reset flag
error=0;							//reset error
}

//function to display the status of reply
void display_status(unsigned char type, unsigned char data0, unsigned char data)	//show the status of the reply
{
	lcd_clr();			//clear lcd display
	switch(data)
	{
		case ACK_SUCCESS:		LEDY=1;								//turn ON yellow LED
								if((type != 1) && (type != 2))
								{	lcd_goto(20);					//set the lcd cursor to location 0
									send_string("Successful      ");//display status	
								}
								else if (type ==1)					//During adding process 1
								{
									lcd_goto(0);					//set the lcd cursor to location 0
									send_string("Scanning...     ");//display string
									lcd_goto(20);					//set the lcd cursor to location 20
									send_string("Verification 1/2");//display string
								}
								else if (type ==2)					//During add process 2
								{
									lcd_goto(0);					//set the lcd cursor to location 0
									send_string("Scanning...     ");//display string
									lcd_goto(20);					//set the lcd cursor to location 20
									send_string("Verification 2/2");//display string								
								}	
								delay(200000);
								LEDY=0;						//turn OFF yellow LED
								error=0;					//no error
								lcd_clr();					//clear lcd 
								break;

		case ACK_FAIL:			LEDR=1;						//turn ON red LED
								Buzzer=1;					//ON buzzer
								lcd_goto(20);				//set the lcd cursor to location 20
								send_string("Failed");		//display status
								delay(200000);
								Buzzer=0;					//OFF buzzer
								LEDR=0;						//turn OFF red LED
								error=1;					//indicates error
								lcd_clr();					//clear lcd display
								break;

		case ACK_TIMEOUT:		LEDR=1;						//turn ON red LED
								Buzzer=1;					//On buzzer
								lcd_goto(20);				//set the lcd cursor to location 20
								send_string("Timeout");		//display status
								delay(200000);	
								Buzzer=0;					//OFF buzzer
								LEDR=0;						//turn OFF red LED
								error=1;					//indicates error
								lcd_clr();					//clear lcd display
								break;

		case ACK_USER_EXIST:	LEDR=1;						//turn ON red LED
								Buzzer=1;					//ON buzzer
								lcd_goto(20);				//set the lcd cursor to location 20
								send_string("User Exist");	//display status
								delay(200000);		
								Buzzer=0;					//OFF buzzer
								LEDR=0;						//turn OFF red LED
								error=1;					//indicates error
								lcd_clr();					//clear lcd display
								break;

		case ACK_NOUSER:		LEDR=1;						//turn ON red LED
								Buzzer=1;					//ON buzzer
								lcd_goto(20);				//set the lcd cursor to location 20
								send_string("Access Denied");//display status
								delay(200000);
								Buzzer=0;					//OFF buzzer
								LEDR=0;						//turn OFF red LED
								error=1;					//indicates error
								lcd_clr();					//clear lcd display
								break;
		
		case ACK_ACCESS:		LEDY=1;						//turn ON yellow LED
								if(data0!=0xFF)				//if not admin (admin stored at location 0xFF)
								{
								lcd_goto(0);				//set the lcd cursor to location 0
								send_string("Hello User ");	//display string
								lcd_goto(11);				//set the lcd cursor to location 11
								send_char(0x30 + data0);	//display character (numerical digit which started from 0x30 or zero)
								lcd_goto(20);				//set the lcd cursor to location 20
								send_string("Welcome");		//display string
								error=0;					//no error
								}
								else
								{
								lcd_goto(0);				//set the lcd cursor to location 0
								send_string("Hello Admin");	//display string
								}
								delay(200000);
								LEDY=0;						//turn OFF yellow LED
								lcd_clr();					//clear lcd display
								break;
				

		default:				LEDR=1;					//turn ON red LED
								LEDY=1;					//turn ON yellow LED
								Buzzer=1;				//turn ON buzzer
								lcd_goto(20);			//set lcd cursor to location 20
								send_string("Error");	//display string
								delay(200000);
								Buzzer=0;				//turn OFF buzzer
								LEDR=0;					//turn OFF red LED
								LEDY=0;					//turn OFF yellow LED
								error=1;				//indicates error
								lcd_clr();				//clear lcd display
								break;

	}
}

//function to get reply from UART
void receive_reply(void)						
{

	unsigned char i;
	for(i=0;i<8;i++)											//store the reply in the array
	array_resp[i]=uart_receive();								//assign values to array
	display_status(array_resp[1],array_resp[3],array_resp[4]);	//retrieve the informations
	delay(1000);

}

//function to get reply from UART but not display the status
void receive_reply_nodisplay(void)
{
	unsigned char i;
	for(i=0;i<8;i++)								//store the reply in the array
	array_resp[i]=uart_receive();					//assign values to array
}

//function to verify admin
void CheckAdmin(void)
{
	send_cmd(0x0b,0x00,0xFF,0x00);		//send command for 1:1 Matching
	lcd_goto(0);						//set the lcd cursor to location 0
	send_string("Place your thumb");	//display string
	lcd_goto(20);						//set the lcd cursor to location 20
	send_string("on the window");		//display string
	delay(100);
	receive_reply();					//get reply from UART
}

//add new fingerprint into database
void AddNew(unsigned char data)
{
	send_cmd(0x01,0x00,data,0x03);		//send adding new fingerprint command
	lcd_goto(0);						//set the lcd cursor to location 0
	send_string("Place your thumb");	//display string
	lcd_goto(20);						//set the lcd cursor to location 20
	send_string("on the window");		//display string
	delay(5000);		
	receive_reply();					//get reply from UART
	location_enter=1;					//indicates location of data has been selected
	if(!error)							//if no error
	{
	lcd_clr();							//clear lcd display
	lcd_goto(0);
	send_string("Scanning...     ");
	lcd_goto(20);
	send_string("Verification 1/2");
	send_cmd(0x02,0x00,data,0x03);		//send verifying fingerprint #1 command
	receive_reply();					//get reply from UART
		if(!error)						//if no error
		{
		lcd_clr();						//clear lcd display
		lcd_goto(0);
		send_string("Scanning...     ");
		lcd_goto(20);
		send_string("Verification 2/2");			
		send_cmd(0x03,0x00,data,0x03);	//send verifying fingerprint #2 command
		receive_reply();				//get reply from UART
		}

	}

}

//store data into specified location in EEPROM
void store_eeprom(unsigned char data,unsigned char location)
{
	EEPROM_WRITE(location,data);		//write data 
	while(WR)							//wait until it finish
	continue;
}

//access EEPROM to retrieve data
unsigned char get_eeprom(unsigned char location)
{
	unsigned char value;
	value= EEPROM_READ(location);		//read eeprom and assign the data to variable 
	return value;						//return data
}

//function to display attendance
void view_attendance (void)
{
	lcd_clr();						//clear lcd
	lcd_goto(0);     				//set the lcd cursor to location 0
	send_string("User 1 2 3 4 5 ");	//display string
	lcd_goto(20);					//set the lcd cursor to location 20
	unsigned char x;
	for(x=0; x<4; x++)		//day1 0x00
	{	TEMP=get_eeprom(x);	//get "D","A","Y","1"
		send_char(TEMP);	//display characters
	}
	for(x=4; x<9; x++)		//loop 5 times for 5 days
	{	send_char(0x20);	//display " "
		TEMP=get_eeprom(x);	//retrieve marking
		send_char(TEMP);	//display marking
	}
	delay(300000);			
	lcd_goto(20);			//set the lcd cursor to location 20
	for(x=16; x<20; x++)	//day2 0x10
	{	TEMP=get_eeprom(x);	//get "D","A","Y","2"
		send_char(TEMP);	//display characters
	}
	for(x=20; x<25; x++)	//loop 5 times for 5 days
	{	send_char(0x20);	//display " "
		TEMP=get_eeprom(x);	//retrieve marking
		send_char(TEMP);	//display marking
	}
	delay(300000);
	lcd_goto(20);			//set the lcd cursor to location 20
	for(x=32; x<36; x++)	//day3 0x20
	{	TEMP=get_eeprom(x);	//get "D","A","Y","3"
		send_char(TEMP);	//display characters
	}
	for(x=36; x<41; x++)	//loop 5 times for 5 days
	{	send_char(0x20);	//display " "
		TEMP=get_eeprom(x);	//retrieve marking
		send_char(TEMP);	//display marking
	}			
	delay(300000);
	lcd_goto(20);			//set the lcd cursor to location 20
	for(x=48; x<52; x++)	//day4 0x30
	{	TEMP=get_eeprom(x);	//get "D","A","Y","4"
		send_char(TEMP);	//display characters
	}
	for(x=52; x<57; x++)	//loop 5 times for 5 days
	{	send_char(0x20);	//display " "
		TEMP=get_eeprom(x);	//retrieve marking
		send_char(TEMP);	//display marking
	}			
	delay(300000);
	lcd_goto(20);			//set the lcd cursor to location 20
	for(x=64; x<68; x++)	//day5 0x40
	{	TEMP=get_eeprom(x);	//get "D","A","Y","5"
		send_char(TEMP);	//display characters
	}
	for(x=68; x<73; x++)	//loop 5 times for 5 days
	{	send_char(0x20);	//display " "
		TEMP=get_eeprom(x);	//retrieve marking
		send_char(TEMP);	//display marking
	}	
	delay(300000);		

}		

//Initialize attendance list
void init_attendance(void)
{
					day_location=0x00;					//location for day1
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('1',day_location+3);	//store character

					day_location=0x10;					//location for day2
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('2',day_location+3);	//store character

					day_location=0x20;					//location for day3
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('3',day_location+3);	//store character

					day_location=0x30;					//location for day4
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('4',day_location+3);	//store character

					day_location=0x40;					//location for day5
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('5',day_location+3);	//store character

}
//clear attendance marking and reset to default
void clear_attendance(void)
{
					day_location=0x00;					//location for day1
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('1',day_location+3);	//store character
					store_eeprom(0xff,day_location+4);	//reset marking
					store_eeprom(0xff,day_location+5);	//reset marking
					store_eeprom(0xff,day_location+6);	//reset marking
					store_eeprom(0xff,day_location+7);	//reset marking
					store_eeprom(0xff,day_location+8);	//reset marking
					day_location=0x10;					//location for day2
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('2',day_location+3);	//store character
					store_eeprom(0xff,day_location+4);	//reset marking
					store_eeprom(0xff,day_location+5);	//reset marking
					store_eeprom(0xff,day_location+6);	//reset marking
					store_eeprom(0xff,day_location+7);	//reset marking
					store_eeprom(0xff,day_location+8);	//reset marking
					day_location=0x20;
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('3',day_location+3);	//store character
					store_eeprom(0xff,day_location+4);	//reset marking
					store_eeprom(0xff,day_location+5);	//reset marking
					store_eeprom(0xff,day_location+6);	//reset marking
					store_eeprom(0xff,day_location+7);	//reset marking
					store_eeprom(0xff,day_location+8);	//reset marking
					day_location=0x30;
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('4',day_location+3);	//store character
					store_eeprom(0xff,day_location+4);	//reset marking
					store_eeprom(0xff,day_location+5);	//reset marking
					store_eeprom(0xff,day_location+6);	//reset marking
					store_eeprom(0xff,day_location+7);	//reset marking
					store_eeprom(0xff,day_location+8);	//reset marking
					day_location=0x40;
					store_eeprom('D',day_location);		//store character
					store_eeprom('A',day_location+1);	//store character
					store_eeprom('Y',day_location+2);	//store character
					store_eeprom('5',day_location+3);	//store character
					store_eeprom(0xff,day_location+4);	//reset marking
					store_eeprom(0xff,day_location+5);	//reset marking
					store_eeprom(0xff,day_location+6);	//reset marking
					store_eeprom(0xff,day_location+7);	//reset marking
					store_eeprom(0xff,day_location+8);	//reset marking
}

//function to upload attendance to Hyper Terminal
void upload_HT(void)
{
	unsigned char address;				
	unsigned char count;
	unsigned char array_title[40]= {"+-+-+- Attendance List -+-+- Cytron PR29"};	//display string

	for(count=0;count<40;count++)			//loop for 40 times
	uart_write(2,array_title[count]);		//write to programmed uart
	for(count=0;count<20;count++)			//loop for 20 times
	{	uart_write(2,'+');					//write '+'
		uart_write(2,'-');					//write '-'
	}
	for(count=0;count<80;count++)			//loop for 80 times
	uart_write(2,' ');						//write to programmed uart
	uart_write(2,'U');						//write to programmed uart
	uart_write(2,'s');						//write to programmed uart
	uart_write(2,'e');						//write to programmed uart
	uart_write(2,'r');						//write to programmed uart
	for(count=1;count<6;count++)			//loop for 5 times
	{
		uart_write(2,' ');					//write ' '
		uart_write(2,0x30+count);			//write user id 1 to 5
	}
	allign();								//function making allignment

	address=0x00;							//set address for day1
	count=address;							//assign value in address to count
	for(address;count<=address+3;count++)	//DAY1 0x00->0x03
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","1"
		uart_write(2,TEMP);					//write to programmmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		uart_write(2,' ');					//write to programmed uart
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
	allign();								//function making allignment

	address=0x10;							//set address for day2
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY2 0x10->0x13
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","2"
		uart_write(2,TEMP);					//write to programmmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		uart_write(2,' ');					//write to programmed uart
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
	allign();								//function making allignment

	address=0x20;							//set address for day3
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY3 0x20->0x23
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","3"
		uart_write(2,TEMP);					//write to programmmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		uart_write(2,' ');					//write to programmed uart
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
	allign();								//function making allignment
                                                     
	address=0x30;							//set address for day4
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY4 0x30->0x33
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","4"
		uart_write(2,TEMP);					//write to programmmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		uart_write(2,' ');					//write to programmed uart
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
	allign();								//function making allignment

	address=0x40;							//set address for day5
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY5 0x40->0x43
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","5"
		uart_write(2,TEMP);					//write to programmmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		uart_write(2,0xff);					//write to programmed uart
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
	allign();								//function making allignment
	for(count=0;count<80;count++)			//loop 80 times 
	uart_write(2,' ');						//to blank a line
	for(count=0;count<40;count++)			//loop 40 times
	{	uart_write(2,'+');					//write to programmed uart
		uart_write(2,'-');					//write to programmed uart

	}
}

//function to upload attendance to GUI
void upload_GUI(void)
{
	unsigned char address;
	unsigned char count;

	address=0x00;							//day1 location
	count=address;							//assign value in address to count
	for(address;count<=address+3;count++)	//DAY1 0x00->0x03
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","1"
		uart_write(2,TEMP);					//write to programmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}

	address=0x10;							//day2 location
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY2 0x10->0x13
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","2"
		uart_write(2,TEMP);					//write to programmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}

	address=0x20;							//day3 location
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY3 0x20->0x23
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","3"
		uart_write(2,TEMP);					//write to programmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking				
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}
                                                     
	address=0x30;							//day4 location
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY4 0x30->0x33
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","4"
		uart_write(2,TEMP);					//write to programmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}

	address=0x40;							//day5 location
	count=address;							//assign value in address to count
	for(count;count<=address+3;count++)		//DAY5 0x40->0x43
	{
		TEMP=get_eeprom(count);				//get "D","A","Y","5"
		uart_write(2,TEMP);					//write to programmed uart
	}
	address=count;							//assign value in count to address
	for(count;count<=address+4;count++)		//loop 5 times to get marking
	{
		TEMP=get_eeprom(count);				//get marking
		if(TEMP==0xff)	TEMP=0x30;			//if 0xff (no marking) replace with 0x30( zero )
		uart_write(2,TEMP);					//write to programmed uart
	}

}

//function to allign the text in Hyper Terminal
void allign(void)
{
	unsigned char Allign;
	for(Allign=0;Allign<66;Allign++)		//loop
	uart_write(2,' ');						//write ' ' to programmed uart
}

//function to reset and re-assign admin
void ResetAdmin(void)
{
	lcd_goto(0);							//set the lcd cursor to location 0
	send_string("Resetting Admin...");		//display string
	delay(200000);
	send_cmd(0x04,0x00,0xFF,0x00);			//command to delete formal admin
	receive_reply();						//get reply from uart
	lcd_goto(0);							//set the lcd cursor to location 0
	send_string("New Admin Needed");		//display string
	delay(200000);
	do{
		lcd_goto(0);						//set the lcd cursor to location 0
		send_string("New Admin       ");	//display string
		lcd_goto(20);						//set the lcd cursor to location 20
		send_string("Standby");				//display string
		delay(200000);
		AddNew(0xff);						//add new admin
	  }	while(error==1)	;					//repeat if new admin not added successfully
}
