#include "hal.h"
void MCAL_init(void)
{
    GPTM_ipEdgeTimeCapture_init();
    GPTM_oneShot_init();
    PWM_Init();
    //ADC init
}
