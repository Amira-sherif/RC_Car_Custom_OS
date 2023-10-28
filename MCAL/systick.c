#include"systick.h"



/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static void (*g_SysTick_Call_Back_Ptr)(void) = NULL;

void systick_init(uint16 Tick_Time)
{
    NVIC_ST_CTRL_R=0;
    NVIC_ST_RELOAD_R=15999*Tick_Time; /* Set the Reload value to the desired time to give an interrupt in milli-seconds
                                         which is the MIN_TASK_DURATION*/
    NVIC_ST_CURRENT_R=0;
    NVIC_ST_CTRL_R |= 0x07;
}

void systick_handler(void)
{

    /* Check if the SysTick_SetCallBack is already called */
       if(g_SysTick_Call_Back_Ptr != NULL)
       {
           (*g_SysTick_Call_Back_Ptr)(); /* call the function in the scheduler using call-back concept */
       }
       /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */

}

void SysTick_SetCallBack(void (*ptr_to_func)(void))
{
    g_SysTick_Call_Back_Ptr = ptr_to_func;
}

/*************************************************************************************
* Description: Function to Stop the SysTick Timer.
************************************************************************************/
void SysTick_Stop(void)
{
    NVIC_ST_CTRL_R = 0; /* Disable the SysTick Timer by Clear the ENABLE Bit */
}
