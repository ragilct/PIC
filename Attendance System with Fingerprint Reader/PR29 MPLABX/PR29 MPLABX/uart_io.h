
//	include
//==========================================================================
#include <pic.h>


//	define system crystal frequency
//==========================================================================
#define _XTAL_FREQ 20000000		//frequency of the crystal


//UART configuration
//==========================================================================

#define UART_2_tx			RC0			//define which pin is used for build TX of UART1
#define UART_2_tx_tris		TRISC0
#define UART_2_rx			RC1 		//define which pin is used for build RX of UART1
#define UART_2_rx_tris		TRISC1
#define UART_2_baudrate		19200		//define the baudrate of this UART channel1



//	function prototype
//==========================================================================
//the function of initialize UART
void uart_init(unsigned char channel);
//the function of write 
void uart_write(unsigned char channel,unsigned char data);
//the function of read
unsigned char uart_read(unsigned char channel);

