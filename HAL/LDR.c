#include "LDR.h"

void LDR_INIT(void)
{
    ADC_INIT();
    LDR1_ADC_INIT();
    LDR2_ADC_INIT();
}

void Get_LDRReads(void)
{
    LDR1_ADC_GETDATA();
    LDR2_ADC_GETDATA();
}
