/*
 * tasks.h
 *
 *  Created on: Sep 11, 2023
 *      Author: Lenovo
 */

#ifndef APP_TASKS_H_
#define APP_TASKS_H_

#define COLLISION_DISTANCE 10

#include <OS/os.h>

void ldr_swing_car(void);
void avoid_obstacles(void);
void lcd_display(void);

#endif /* APP_TASKS_H_ */
