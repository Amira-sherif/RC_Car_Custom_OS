/*
 * ultrasonic.h
 *
 *  Created on: Sep 11, 2023
 *      Author: Lenovo
 */

#ifndef HAL_ULTRASONIC_H_
#define HAL_ULTRASONIC_H_

#include <MCAL/DIO.h>
#include <MCAL/GPTM.h>

extern uint8 distance;

void ultrasonic_init(void);
void ultrasonicTrigger(void);


#endif /* HAL_ULTRASONIC_H_ */
