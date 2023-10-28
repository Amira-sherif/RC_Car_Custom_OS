#include "os.h"

/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm(" CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm(" CPSID I")

#define MIN_TASK_DURATION   10  /////////////////////////////

static uint8 task_counter = 0;

uint8 g_currentTime_ms = 0;
uint8 g_systick_newTick_flag = 0;


TaskControlBlock tasks[NUM_OF_TASKS];   /*array of structs that holds the tasks and their periods*/

void scheduler_init(void)
{
    Enable_Interrupts();

/*setup and initializing the hardware*/
    MCAL_init();

    LcdInit();
    motorControl_init();
    ultrasonic_init();
    //LDR INIT
    //TEMP SENSOR INIT

    /*
     * Set the Call Back function to call OS_tickTime function
     * this function will be called every SysTick Interrupt (every MIN_TASK_DURATION)
     */
    SysTick_SetCallBack(OS_tickTime);

    /* Start SysTickTimer to generate interrupt every MIN_TASK_DURATION */
    systick_init(MIN_TASK_DURATION);
    tasks_scheduler();

}

/*this function will increment the function counter on each systick interrupt
 * with the value of the minimum task duration */
void OS_tickTime(void)
{
    g_currentTime_ms += MIN_TASK_DURATION;
    g_systick_newTick_flag = 1; /*this flag is set each systick interrupt*/
}

void create_task (void (*task)(void), uint32 task_period_ms)
{
    if(task_counter < NUM_OF_TASKS){
        tasks[task_counter].task_ptr = task;
        tasks[task_counter].task_period = task_period_ms;
        task_counter++;
    }
    else{
        /*for MISRA*/
    }
}

void tasks_scheduler(void)
{
    while(1)
    {
        if(g_systick_newTick_flag)
        {
            switch(g_currentTime_ms)
            {
            case TASK1_PERIOD :
            g_systick_newTick_flag = 0;
            tasks[0].task_ptr();
            break;
            case TASK2_PERIOD :
            g_systick_newTick_flag = 0;
            break;
            case TASK3_PERIOD :
            g_systick_newTick_flag = 0;
            break;
            }
        }

    }

}
