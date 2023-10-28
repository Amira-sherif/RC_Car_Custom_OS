/*This is the code for the three main tasks of the system which are:
1- Task to swing the car based on the LDR.s [void ldr_swing_car(void)]
2- Task to display on the LCD. [void lcd_display(void)]
3- Task to avoid obstacles based on the readings of the ultrasonic sensor. [void avoid_obstacles(void)]*/

/*TASK 1*/
#include "tasks.h"

/*global variable to hold the current time to be printed on the LCD*/
uint32 g_current_time = 0;

void ldr_swing_car(void)
{
    if(switch0_flag) /*start the car*/
    {
        /*LDR CODE HERE*/
        /*reset systick*/

    }
//    if(switch4_flag || g_current_time == 60) /*stop the car*/
//    {
//        motor_brakes();
//          SysTick_Stop();
//    }
}


/*TASK 2: Task to display tempreture reading and current time on the LCD. */
void lcd_display(void)
{

    LcdSendString("Temp: ");
    LCDSendInt(TEMP);
    LcdGoTo(ROW2,COL1);

    g_current_time = NVIC_ST_CURRENT_R/16000000;
    LcdSendString("Time:");
    LCDSendInt(g_current_time);
}


/*TASK 3: uses ultrasonic sensor to detect and avoid obstacles*/
void avoid_obstacles(void)
{
    ultrasonicTrigger();
    if(distance<= COLLISION_DISTANCE)
    {
        motor_moveBackward();
        GPTM_delay_ms(3000); /*3 seconds delay*/
        motor_moveRight();
        GPTM_delay_ms(3000); /*configured based on the time taken to reach 90 degrees*/
    }
    else
    {
//        moveForward();
    }
}

