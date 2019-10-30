/*****************************************************************************
*                           Hardware.c
*
* Description: Hardware related functions
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
* CODE OWNERSHIP AND DISCLAIMER OF LIABILITY
*
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in
* all derivatives hereto.  You may use this code, and any derivatives created
* by any person or entity by or on your behalf, exclusively with Microchips
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT
* LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND
* FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH
* MICROCHIPS PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
* APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE,
* WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
* STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE,
* FOR ANY INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE
* BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY
* TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
* Author            Date		Ver		Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Ragil.C.T            Oct 2012 	1.00	Release

******************************************************************************/

#include "BatteryCharger.h"

unsigned char temp;
unsigned char lbut, led_state;

unsigned char but_cnt, led_cnt;

unsigned int ad_res;
unsigned int iout;
unsigned int vout;

unsigned int vref;
unsigned int iref; 
unsigned int warmup;
unsigned char cc_cv;

unsigned int second;

int increment;

char cmode;

int	pp,pi;

void Initialize_Hardware()
{	
	increment = NCO_MIN;

	CLRWDT();

	T0IF = 0;

	AD_SET_CHAN(31);	
	
	ad_res = 0xFFFF;

	cmode = 0;
	warmup = WARMUP_TIME;

	cc_cv = CURRENT_MODE;
	but_cnt = BUTTON_COUNT;
	second = SECOND_COUNT_START;

	battery_state = IDLE;

	iref = 0;
	vref = 0;

	lbut = 1;

	STOP_CONVERTER();
}

void Init_Registers()
{
	//		   	  76543210
	OSCCON = 	0b01111000;

	OPTION_REG = 	0b01000011;	///> set prescaler to 1/16

	//		  	  76543210
	PORTA = 	0b00000000;
	TRISA = 	0b11001110;
	ANSELA = 	0b11000110;
	//		  	  76543210
	PORTC =		0b00010000;	
	TRISC = 	0b11001100;
	ANSELC =	0b11001100;

	WPUA = 		0b00001000;
	APFCON = 	0b00000001;

	//		  	  76543210
	FVRCON = 	0b10001111;

	//		  	  76543210
	ADCON0 = 	ADCON0_INIT;
	ADCON1 = 	ADCON1_INIT;

	T2CON = 	0x04;

	//		  	  76543210
	NCO1CON = 	0b11000001;
	NCO1CLK = 	NCO_32P;		// 2us ON time

	NCO1INCH = 	0x00;
	NCO1INCL =	0x00;
}

void Shutdown_Peripherals()
{
	//		  	  76543210
	ANSELA = 	0b11111111;
	PORTA = 	0b00000000;
	TRISA = 	0b11111111;
	WPUA = 		0b11111111;

	FVRCON = 0x00;

	ADCON0 = 0x00;

	T2CON = 0x00;

	OPTION_REG = 0xFF;
}

void Delay_ms(unsigned int msec)
{
	while(msec)
	{
		while(!T0IF);
		T0IF = 0;
		msec--;
	}
}

void pid(unsigned int feedback, unsigned int setpoint)
{
int 	er;
int		ipid;
	
	er = setpoint - feedback;

	if(er > ERR_MAX) er = ERR_MAX;
	if(er < ERR_MIN) er = ERR_MIN;

	if(!warmup)
	{
		if(cmode) pp = er; else
		pp = er;

		pi += er;
		if(pi > ERR_MAX) pi = ERR_MAX;
		if(pi < ERR_MIN) pi = ERR_MIN;

		ipid = pp;
		ipid += (pi / 256);

		if(ipid > ERR_MAX) ipid = ERR_MAX;
		if(ipid < ERR_MIN) ipid = ERR_MIN;

		increment += ipid;
	} else
	{	
		warmup--;
		if(er > 0) increment++; else increment--;
		pi = 0;
	}
		
	set_NCO();
}

void set_NCO()
{
		if(increment < NCO_MIN) increment = NCO_MIN;
		if(increment > NCO_MAX) increment = NCO_MAX;
	
		NCO1INCH = increment >> 8;
		NCO1INCL = increment & 0xFF;
}

void read_ADC()
{
	AD_SET_CHAN(IOUT_SENSE_CHAN);
	_delay(10);
	ad_res = 0;

	for(temp = 0; temp < AD_SAMPLES; temp++)
	{
		AD_CONVERT();	
		ad_res += ADRESL;
		ad_res += (ADRESH << 8);
	}
	iout = ad_res;

	AD_SET_CHAN(VOUT_CHAN);
	_delay(10);
	ad_res = 0;

	for(temp = 0; temp < AD_SAMPLES; temp++)
	{
		AD_CONVERT();	
		ad_res += ADRESL;
		ad_res += (ADRESH << 8);
	}
	vout = ad_res;

	AD_SET_CHAN(VIN_CHAN);
	_delay(10);
	ad_res = 0;
	
}

void cc_cv_mode()
{
	if(vout > vref) 
	{
		if(cc_cv) cc_cv--; else
		{
			if(cmode) pi = 0;
			cmode = 0;
		}
	}
	if(iout > iref) 
	{
			if(!cmode) pi = 0;
			cmode = 1;
			cc_cv = CURRENT_MODE;
	}
}

void led_blink(void)
{
	if(led_state == LED_ON) LED = 1; else
	if(led_state == LED_OFF) LED = 0; else
	if(led_cnt) led_cnt--; else
	{
		led_cnt = led_state;
		LED ^= 1;
	}
}



