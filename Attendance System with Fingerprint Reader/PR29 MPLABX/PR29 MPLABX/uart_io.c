

//	include
//==========================================================================
#include "uart_io.h"


//	unused uart channel handler
//==========================================================================
unsigned char dummy_byte=0;

#ifndef UART_2_tx
	#define UART_2_tx dummy_byte	
#endif
#ifndef UART_2_tx_tris
	#define UART_2_tx_tris dummy_byte	
#endif
#ifndef UART_2_rx
	#define UART_2_rx dummy_byte	
#endif
#ifndef UART_2_rx_tris
	#define UART_2_rx_tris dummy_byte	
#endif
#ifndef UART_2_baudrate
	#define UART_2_baudrate 19200
#endif



//	baudrate cycle definition
//==========================================================================
#define UART_2_baudrate_cycle	(_XTAL_FREQ/4)/UART_2_baudrate



//	functions
//==========================================================================
void uart_init(unsigned char channel)
{
	switch(channel)
	{
		case 2:
			UART_2_tx=1;		//set tx pin to '1'
			UART_2_tx_tris=0;	//set tx pin as output
			UART_2_rx=1;		//set rx pin to '1'
			UART_2_rx_tris=1;	//set rx pin as input
			break;				
	}		
}

void uart_write(unsigned char channel,unsigned char data)
{
	unsigned char i;
	
	switch(channel)
	{
		case 2:
			UART_2_tx=0;
			_delay(UART_2_baudrate_cycle-15);
			for(i=1;i>0;i=i<<1)
			{
				if((data&i)==0)
				{
					UART_2_tx=0;
					_delay(UART_2_baudrate_cycle-21);	
				}
				else
				{
					UART_2_tx=1;
					_delay(UART_2_baudrate_cycle-20);	
				}		
			}
			_delay(8);
			UART_2_tx=1;
			_delay(UART_2_baudrate_cycle-3);	
			break;
	}		
}	
	
	
unsigned char uart_read(unsigned char channel)
{
	unsigned char i;
	unsigned char result=0;
	unsigned char dummy_mask=0x00;
	
	switch(channel)
	{
		case 2:
			while(UART_2_rx);					//wait for start bit
			_delay(UART_2_baudrate_cycle-10);	//delay for 1 and half bit
			_delay(UART_2_baudrate_cycle/2);
			for(i=1;i>0;i=i<<1)					
			{
				if(UART_2_rx==1)
				{
					result|=i;
				}
				else 
				{
					result|=result;
				}
				_delay(UART_2_baudrate_cycle-20);
			}
			_delay(UART_2_baudrate_cycle/2);		
			break;			
	}	
	return result;
}	
