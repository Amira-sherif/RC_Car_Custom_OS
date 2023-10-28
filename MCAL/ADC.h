/*
 * ADC.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_ADC_H_
#define MCAL_ADC_H_

#define ADC_H_
#include <Utilities/std_types.h>
#include <Tiva_Registers.h>
#include <Utilities/Bitwise_Operations.h>
#include <MCAL/DIO.h>

extern uint32 ldr1_buffer;
extern uint32 ldr2_buffer;
extern uint32 ts_buffer;
extern volatile uint32 TEMP;


void configurePLL(void);
void ADC_INIT(void);
void LDR1_ADC_INIT(void);
void LDR1_ADC_GETDATA(void);
void LDR2_ADC_INIT(void);
void LDR2_ADC_GETDATA(void);

void TS_ADC_INIT(void);
void TS_ADC_GETDATA(void);


#endif /* MCAL_ADC_H_ */
