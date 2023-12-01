/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Amira Atef
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "common_macros.h" /* For GET_BIT Macro */
#include "adc.h"

#if (INTERRUPT)
#include <avr/interrupt.h> /* For ADC ISR */

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 01 to choose AVCC = 5v as reference voltage
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialisation
	 */
	ADMUX = (ADMUX & 0x3F) | (Config_Ptr->ref_volt);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 111 to choose ADC_Clock = F_CPU/128 = 16Mhz/128 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN);
	#if (INTERRUPT)
		ADCSRA |= (1<<ADIE);
	#endif
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr-> prescaler);
}

#if (INTERRUPT)
void ADC_readChannel(uint8 channel_num)
{
	/* Input channel number must be from 0 --> 7 */
	/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0)| (channel_num & 0x07);
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
}

#else
uint16 ADC_readChannel(uint8 channel_num)
{
	/* Input channel number must be from 0 --> 7 */
	/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = (ADMUX & 0xE0)| (channel_num & 0x07);
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
#endif
