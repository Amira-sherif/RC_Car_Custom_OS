/*
 * ADC.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Lenovo
 */


#include "ADC.h"

uint32 ldr1_buffer;
uint32 ldr2_buffer;
uint32 ts_buffer;
volatile uint32 TEMP=0;


void configurePLL(void)
{
    // Configure the PLL to generate the desired system clock frequency
    // Example: Set PLL to generate a 50 MHz system clock
    // This assumes a 16 MHz external crystal or oscillator as the input
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2; // Bypass PLL and divider during config
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // Clear XTAL field
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ; // Set XTAL to 16 MHz
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M; // Clear OSCSRC2 field
    SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO; // Use main oscillator as the PLL source
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;   // Activate PLL by clearing PWRDN2 bit
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;    // Use 400 MHz PLL output
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (4<<22);// Clear SYSDIV2 field   // Set SYSDIV2 to divide by 5 (80 MHz)

    while((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0); // Wait for PLL lock
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;  // Enable PLL by clearing BYPASS2
}
void ADC_INIT(void)
{
    configurePLL();
    /* Enable Clock to ADC0*/
    SET_BIT(SYSCTL_RCGCADC_R,0);
}

void LDR1_ADC_INIT(void)
{
    /************** GPIO configuration*****************************/
    /* Enable Clock to GPIOE*/
    DIO_Init(PORTE, PE);

    /* initialize PE2 for AIN1 input  */
    SET_BIT(GPIO_PORTE_AFSEL_R,BIT2);
    CLEAR_BIT(GPIO_PORTE_DEN_R,BIT2);
    SET_BIT(GPIO_PORTE_AMSEL_R,BIT2);

    /************** ADC configuration*****************************/
    /* initialize sample sequencer0 */

    CLEAR_BIT(ADC0_ACTSS_R,BIT0);       /* disable SS0 during configuration */

    ADC0_EMUX_R &= ~0X000F;              /* software trigger conversion */

    ADC0_SSMUX0_R|=0X1;                 /* get input from channel 1 */

    SET_BIT(ADC0_SSCTL0_R,1);           /* 1st sample is the end of the sequence*/
    SET_BIT(ADC0_SSCTL0_R,2);           /* 1st Sample Interrupt Enable*/

    CLEAR_BIT(ADC0_IM_R,0);              /* polling */

    SET_BIT(ADC0_ACTSS_R,0);            /* enable SS0 during configuration */
}

void LDR1_ADC_GETDATA(void)
{
    SET_BIT(ADC0_PSSI_R,0);                               /* start a conversion sequence 0 */
    while (GET_BIT(ADC0_RIS_R ,0) == 0);                  /* wait for conversion complete */
    ldr1_buffer = ADC0_SSFIFO0_R;                         /* read conversion result */
    SET_BIT(ADC0_ISC_R,BIT0);                             /* clear completion flag */
}

void LDR2_ADC_INIT(void)
{
    /************** GPIO configuration*****************************/
    /* Enable Clock to GPIOE*/
    DIO_Init(PORTE, PE);

    /* initialize PE1 for AIN2 input  */
    SET_BIT(GPIO_PORTE_AFSEL_R,BIT1);
    CLEAR_BIT(GPIO_PORTE_DEN_R,BIT1);
    SET_BIT(GPIO_PORTE_AMSEL_R,BIT1);

    /************** ADC configuration*****************************/
    /* initialize sample sequencer0 */

    CLEAR_BIT(ADC0_ACTSS_R,BIT1);       /* disable SS1 during configuration */

    ADC0_EMUX_R &= ~0x00F0;              /* software trigger conversion */

    ADC0_SSMUX1_R =0x2;                 /* get input from channel 2 */

    ADC0_SSCTL1_R|=0x06;                /* 1st sample is the end of the sequence AND 1st Sample Interrupt Enable */


    CLEAR_BIT(ADC0_IM_R,1);              /* polling */

    SET_BIT(ADC0_ACTSS_R,BIT1);            /* enable SS1 during configuration */
}

void LDR2_ADC_GETDATA(void)
{
    SET_BIT(ADC0_PSSI_R,1);                               /* start a conversion sequence 1 */
    while (GET_BIT(ADC0_RIS_R ,1) == 0);                  /* wait for conversion complete */
    ldr2_buffer = ADC0_SSFIFO1_R;                         /* read conversion result */
    SET_BIT(ADC0_ISC_R,BIT1);                             /* clear completion flag */
}


void TS_ADC_INIT(void)
{
    /************** ADC configuration*****************************/

    /* initialize sample sequencer3 */
    ADC0_SAC_R|=ADC_SAC_AVG_64X;        /*over sampling*/
 //   sequencer_set(ADC0,SEQ3,AIN1,Enable);
    CLEAR_BIT(ADC0_ACTSS_R,3);          /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;             /* software trigger conversion */

    SET_BIT(ADC0_SSCTL3_R,1);           /* take one sample at a time, set flag at 1st sample */
    SET_BIT(ADC0_SSCTL3_R,2);           /* set flag at 1st sample */
    SET_BIT(ADC0_SSCTL3_R,3);           /* set flag at 1st Sample Temp Sensor Select*/
    SET_BIT(ADC0_ACTSS_R,3);            /* enable SS3 during configuration */

}

void TS_ADC_GETDATA(void)
{
    SET_BIT(ADC0_PSSI_R,3);                               /* start a conversion sequence 3 */
    while ((ADC0_RIS_R & 0x8) == 0);                      /* wait for conversion complete */
    ts_buffer = ADC0_SSFIFO3_R;                           /* read conversion result */
    TEMP = 147.5 - ((75 * (3.3) * ts_buffer) / 4096);     /*  temperature  */
    ADC0_ISC_R = 0x8;                                     /* clear completion flag */

}
