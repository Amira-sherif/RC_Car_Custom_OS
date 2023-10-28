/*Timers modules*/

/******************************************************************/
/*Timer Module for Input Edge time Capture mode*/
/******************************************************************/
#include "GPTM.h"

/*Timers Modules*/

uint8 g_intEdge = 0;
float total_time = 0;
uint8 distance;

void GPTM_ipEdgeTimeCapture_init(void)
{
    SET_BIT(SYSCTL_RCGCWTIMER_R,TIMER2);    /*enabling clock for WTIMER2*/
    CLEAR_BIT(WTIMER2_CTL_R,TAEN_bit);       /*disable the timer by clearing TAEN_bit in register */
    WTIMER2_CFG_R |= 0x4;                /*using 32 bit wide mode (timer A)*/

    WTIMER2_TAMR_R |= 0x07; /*write the TnCMR field to 0x1 and the TnMR
                            field to 0x3 and select a count direction by programming the TnCDIR bit.*/
    // WTIMER2_TAMR_R |= 0x17; /*write the TnCMR field to 0x1 and the TnMR  count up
    //    field to 0x3 and select a count direction by programming the TnCDIR bit.*/

    SET_BIT(WTIMER2_CTL_R,TAEVENT_bit1);
    SET_BIT(WTIMER2_CTL_R,TAEVENT_bit2);       /* event edge is set to both edges*/
    WTIMER2_TAILR_R = TICKS_FOR_MAX_DIST;
    SET_BIT(WTIMER2_IMR_R,2);                /*Enabling timer interrupt*/
    SET_BIT(NVIC_EN3_R,2);                  /*Enabling the global interrupts*/
    SET_BIT(WTIMER2_CTL_R,TAEN_bit);       /*enable the timer*/
}

void GPTM_ipEdgeTimeCaptureHandler(void)
{static uint32 rising_time;
static uint32 falling_time;
while(1){
CLEAR_BIT(WTIMER2_ICR_R,CAECINT);
while(GET_BIT(WTIMER2_RIS_R,2) == 0) ;    /* wait till captured */


if(GET_BIT(GPIO_PORTD_DATA_R,0)) /*Raising Edge detected*/
{
    rising_time = WTIMER2_TAR_R;
}
CLEAR_BIT(WTIMER2_ICR_R,CAECINT);
while(GET_BIT(WTIMER2_RIS_R,2) == 0) ;    /* wait till captured */


if(GET_BIT(GPIO_PORTD_DATA_R,0)) /*Raising Edge detected*/
{
    falling_time= WTIMER2_TAR_R;
}

    total_time = (rising_time - falling_time) / 16000.0;
    distance = (34 *total_time)/2;
}
}
//void GPTM_ipEdgeTimeCaptureHandler(void)
//{
//    CLEAR_BIT(WTIMER2_ICR_R,CAECINT);
//    static uint32 rising_time;
//    static uint32 falling_time;
//    g_intEdge++;
//    if(g_intEdge==1) /*Raising Edge detected*/
//    {
//        rising_time = WTIMER2_TAR_R;
//    }
//    else if(g_intEdge==2) /*Falling Edge detected*/
//    {
//        g_intEdge=0;
//        falling_time= WTIMER2_TAR_R;
//        total_time = (rising_time - falling_time) / 16000.0;
//        distance = (34 *total_time)/2;
//    }
//}


/******************************************************************/
/*Timer Module for one shot mode that is used for delay generation*/
/******************************************************************/

void GPTM_oneShot_init(void)
{
    SET_BIT(SYSCTL_RCGCWTIMER_R, 1);    /*Enable wide timer 1 in Run mode*/
    CLEAR_BIT(WTIMER1_CTL_R, 0);        /*Disable the timer 1  module */
    WTIMER1_CFG_R=0x04;
    SET_BIT(WTIMER1_TAMR_R, 0);         /*One shot mode*/

}

void GPTM_delay_us(uint32 time)
{
    WTIMER1_TAILR_R=time*TIME_FACTOR_MICRO_SECONDS -1;
    SET_BIT(WTIMER1_CTL_R, 0);          /*Enable the timer */
    while (!(GET_BIT(WTIMER1_RIS_R,0))){}
    SET_BIT(WTIMER1_ICR_R,0);
    CLEAR_BIT(WTIMER1_CTL_R, 0);
}


void GPTM_delay_ms(uint32 time)
{

    WTIMER1_TAILR_R=time*TIME_FACTOR_MILLI_SECONDS -1;
    SET_BIT(WTIMER1_CTL_R, 0);         /*Enable the timer */
    while (!(GET_BIT(WTIMER1_RIS_R,0))){}
    SET_BIT(WTIMER1_ICR_R,0);
    CLEAR_BIT(WTIMER1_CTL_R, 0);       /*disable the timer */
}

