/*
 * ADC_Driver.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Asmer Amen
 */


#include "Types.h"
#include "utilss.h"
#include "DIO.h"
#include "ADC_Driver.h"
//#include "DigExInterrupt.h"

#include <avr/delay.h>

void ADC_voidInit(void)
{
	/*
	 * Vref selection -> 5v
	 * REFS1 : 0, REFS0 : 1
	 * Left adjustment
	 * ADLAR : 1
	 */
	ADMUX |=(REFS1<<7) | (REFS0<<6) | (ADLAR<<5);

	/*
	 *  ADC Enable, -> 1
	 *  								 Polling | Interrupt
	 *  ADATE : Auto trigger disabled -> 	0	 |		1
	 *  ADIF: Interrupt Flag 		->		0	 |		0
	 *  ADIE: Interrupt Enable	 ->			0	 |		1
	 *  ADPS: Prescaler
	 */
	ADCSRA |= (ADEN<<7) | (ADATE<<5) | (ADIF<<4) | (ADIE<<3) |(ADPS0<<0) | (ADPS1<<1) | (ADPS2<<2);


//	SREG |=(1<<7);
}

U16 ADC_u16Read(U32 Pin)
{
	ADCH = 0;
	// Analog channel and Gain selection : 5
	ADMUX |= (0<<3) | (1<<2) | (0<<1) |(1<<0);

//	Pin = Pin&0b00000111;
//	ADMUX|= Pin;

	/*
	 *  ADC Start Conversion
	 *  ADSC -> 1
	 */
	set_bit(ADCSRA, 6);
	_delay_ms(100);

	/*
	 * 	Polling mode
	 * 	Waiting for the ADC Interrupt flag to be 1
	 */
	while(!get_bit(ADCSRA, 4));

	/* Clear interrupt flag,
	 * ADIF -> 1
	 */
	set_bit(ADCSRA,4);

	return ADCH;
}

#ifdef INTERRUPT
void ADC_voidInterrupt(void)
//U8 ADC_u8Interrupt(U32 Pin)
{
	// Analog channel and Gain selection
//	assign_nibbleLow(ADMUX,Pin);
	// Analog channel and Gain selection : Pin 5
	ADMUX |= (0<<3) | (1<<2) | (0<<1) |(1<<0);

	//Enable Global Interrupts.
//	DEI_voidInit();
	set_bit(SREG, 7);
	/*
	 *  ADC Start Conversion
	 *  ADSC -> 1
	 */
	set_bit(ADCSRA, 6);
}
#endif
