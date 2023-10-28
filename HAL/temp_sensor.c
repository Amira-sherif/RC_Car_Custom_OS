/*
 * temp_sensor.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Lenovo
 */


#include <HAL/temp_sensor.h>

void Temp_sensorInit(void)
{
    ADC_INIT();
    TS_ADC_INIT();
}

void Temp_sensorRead(void)
{
    TS_ADC_GETDATA();
}
