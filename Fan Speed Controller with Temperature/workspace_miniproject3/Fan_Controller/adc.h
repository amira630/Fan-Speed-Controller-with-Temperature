/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver
 *
 * Author: Amira Atef
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
#define INTERRUPT            LOGIC_LOW


/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	AREF=0x00, AVCC=0x40, INTERNAL=0xC0
} ADC_ReferenceVolatge;

typedef enum
{
	F_CPU_2_0,F_CPU_2_1, F_CPU_4,F_CPU_8,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

#if (INTERRUPT)
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;

#endif
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialising the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#if (INTERRUPT)
void ADC_readChannel(uint8 channel_num);
#else
uint16 ADC_readChannel(uint8 channel_num);
#endif


#endif /* ADC_H_ */
