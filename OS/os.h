/*
 * os.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Lenovo
 */

#ifndef OS_OS_H_
#define OS_OS_H_

#include <Utilities/std_types.h>
#include <HAL/ultrasonic.h>
#include <HAL/motor.h>
#include <HAL/LCD/LCD_interface.h>
#include <HAL/hal.h>
#include <HAL/temp_sensor.h>

#define TASK1_PERIOD 10
#define TASK2_PERIOD 20
#define TASK3_PERIOD 30

typedef struct{
    void (*task_ptr)(void); /* function pointer to task which will be used to point to each task*/
    uint32 task_period; /*task period will be used to indicate the task duration*/
}TaskControlBlock;

#define NUM_OF_TASKS 3

void scheduler_init(void);
void OS_tickTime(void);
void create_task (void (*task)(void), uint32 task_period_ms);



#endif /* OS_OS_H_ */
