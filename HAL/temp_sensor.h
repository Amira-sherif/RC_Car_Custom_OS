/*
 * temp_sensor.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Lenovo
 */

#ifndef HAL_TEMP_SENSOR_H_
#define HAL_TEMP_SENSOR_H_

#include <MCAL/ADC.h>

void Temp_sensorInit(void);
void Temp_sensorRead(void);



#endif /* HAL_TEMP_SENSOR_H_ */
