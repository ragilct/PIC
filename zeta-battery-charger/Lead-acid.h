/*****************************************************************************
*                           Lead-acid.h
*
* Description: Lead-acid specific parameters
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
* Ragil.C.T           Oct 2012 	1.00	Release

******************************************************************************/

//Lead-acid battery specific parameters

#define PRESET1
//define PRESET2


//	1.75V per cell cutoff voltage
// 	2.10V per cell charged OCV voltage
//	2.25V per cell floating voltage
//	2.40V per cell charging voltage

#ifdef PRESET1
	#define LA_3CELL
	#define CAPACITY 				4000
	#define CHARGING_VOLTAGE		1474	//7.20V
	#define	FLOATING_VOLTAGE		1382	//6.75V
	#define TOPPING_VOLTAGE			1290	//6.30V
	#define	CUTOFF_VOLTAGE			1075	//5.25V

	#define	ILIM_PRECHARGE			173		//50mA, C/10
	#define	ILIM					347		//800mA, C/5
	#define IFLOAT					35		//80mA, C/50 (2%) minimum charging current				

#endif

#define		BATTERY_STANDBY_MODE
	

#define	PRECHARGE_TIME		600

#define FLOAT_TIME			43200

#define	FLOAT_RELAX_TIME	(FLOAT_TIME - 10)

#define IFLAT_COUNT		600

