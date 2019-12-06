/*
 * ADC_Driver.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Asmer Amen
 */

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

/*
 *	Define to Enable Interrupt mode,
 *	undefine to Enable Polling mode.
 */

	#define INTERRUPT

#ifdef INTERRUPT
		/* Including Interrupt configurations */
//	#include "DigExInterrupt.h"
#endif

/* Mapping equation value */
#define RESOLUTION 255 // 8 Bits
#define V_REF 5  // Voltage Reference : 5V

	//	Registers
#define SREG  *((U8*) 0x5F)		//Status Register
#define ADMUX *((U8*)0x27)		//ADC Multiplexer Selection Register
#define ADCSRA *((U8*)0x26)		//ADC Status Register A
#define ADCH *((U8*)0x25)		//ADC ADC Data Register Upper byte
#define SFIOR *((U8*)0x50)		//Special FunctionIO Register
/*********************************************************************************/

/*
 * 				ADMUX Bits Configuration
 */

	//Vref Selection : ARef = 5v
#define REFS1 0	//Bit7
#define REFS0 0	//Bit6
	/* Left Adjustment
	 * Enable : 1
	 */
#define ADLAR 1	//Bit5
	/*
	 * Analog Channel and Gain selection
	 * Sets the channel to be used,
	 * Mode: single, differential.
	 * Gain.
	 *
	 * MUX bits : Mux4 -> Mux0
	 */

/*********************************************************************************/

/*
 * 				ADCSRA Bits Configuration
 * 	ADEN is set to 1, when ADC is being initialized.
 *
 * 	ADSC is set to 1, when conversion is about to be executed.
 *
 * 	ADATE is set to 0, while using polling mode.
 * 					1, while using interrupt mode.
 *
 * 	ADIE is set to 0, while using polling mode.
 * 				   1, while using interrupt mode.
 *
 * 	ADS2, ADPS1, ADPS0, Prescaler Select Bits
 * 	0		0		0 --> 2
 * 	0		0		1 --> 2
 * 	0		1		0 --> 4
 * 	0		1		1 --> 8
 * 	1		0		0 --> 16
 * 	1		0		1 --> 32
 * 	1		1		0 --> 64
 * 	1		1		1 --> 128
 *
 */

#define ADEN  1		//Bit7 ADC Enable
#define ADSC  0		//Bit6 ADC Start Conv.

#ifndef INTERRUPT
#define ADATE 0		//Bit5 ADC Auto Trigger Enable
#define ADIF  0		//Bit4 ADC Interrupt Flag
#define ADIE  0		//Bit3 ADC Interrupt Enable

#else
#define ADATE 1		//Bit5 ADC Auto Trigger Enable
#define ADIF  0		//Bit4 ADC Interrupt Flag
#define ADIE  1		//Bit3 ADC Interrupt Enable
#endif

//ADC Prescaler select Bits : set to 7 (128)
#define ADPS0 1 	//Bit0
#define ADPS1 1		//Bit1
#define ADPS2 1		//Bit2

#ifdef INTERRUPT
/* 	SFIOR: Special FunctionIO Register */
	/*
	 * ADC Auto trigger Source
	 * ADTS2, ADTS1, ADTS0
	 * 0 		0 		0 --> Free running mode.
	 * 0		0		1 --> Analog Comparator.
	 * 0 		1 		0 --> External Interrupt Request 0
	 * 0 		1 		1 --> Timer/Counter0 Compare Match
	 * 1	 	0 		0 --> Timer/Counter0 Overflow
	 * 1 		0 		1 --> Timer/Counter Compare Match B
	 * 1	 	1 		0 --> Timer/Counter1 Overflow
	 * 1 		1	 	1 --> Timer/Counter1 Capture Event
	 *
	 */
#define ADTS2 0		//Bit7
#define ADTS1 0		//Bit6
#define ADTS0 0		//Bit5
#endif

/*********************************************************************************/


					/* Prototypes */
	void ADC_voidInit(void);
	U16 ADC_u16Read(U32);
//	U8 ADC_u8Interrupt(void);
	void ADC_voidInterrupt(void);

#endif /* ADC_DRIVER_H_ */
