/*
 * systick.h
 *
 *  Created on: Sep 11, 2023
 *      Author: Lenovo
 */

#ifndef MCAL_SYSTICK_H_
#define MCAL_SYSTICK_H_

#include "Tiva_Registers.h"
#include <Utilities/std_types.h>
#include <Utilities/Bitwise_Operations.h>

extern volatile uint8 current_time;

void systick_init(uint16 Tick_Time);
void SysTick_SetCallBack(void (*ptr_to_func)(void));
void SysTick_Stop(void);

#endif /* MCAL_SYSTICK_H_ */
