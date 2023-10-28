//#include <HAL/LCD/LCD_interface.h>
//#include <Utilities/std_types.h>
//#include <MCAL/GPTM.h>
#include <APP/tasks.h>



int main(void)
{
    create_task(ldr_swing_car, TASK1_PERIOD);
    create_task(lcd_display, TASK2_PERIOD);
    create_task(avoid_obstacles, TASK3_PERIOD);

    scheduler_init();

    while(1){}
}
