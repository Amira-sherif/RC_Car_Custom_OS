/*
 * ultrasonic.c
 *
 *  Created on: Sep 11, 2023
 *      Author: Lenovo
 */
#include "ultrasonic.h"

void ultrasonic_init(void)
{
    GPTM_ipEdgeTimeCapture_init();
    GPTM_oneShot_init();
    DIO_Init(PORTD, PD); /*Clk initialization for port D*/

    /*configure echo pin of the ultrasonic as an input to WTIMER2 (PD1)*/
    DIO_SetPinDirection(PORTD,BIT1,INPUT);
    SET_BIT(GPIO_PORTD_DEN_R,1);
    SET_BIT(GPIO_PORTD_AFSEL_R,1);
    GPIO_PORTD_PCTL_R |= 0x70;  /*choosing wide timer2 on PD1*/

    /*configure trigger pin of the ultrasonic as an output GPIO pin PD0*/
    DIO_SetPinDirection(PORTD,BIT0,OUTPUT);
    SET_BIT(GPIO_PORTD_DEN_R,0);
    DIO_WritePin(PORTD,BIT0,LOW);
}

void ultrasonicTrigger(void)
{
    DIO_WritePin(PORTD,BIT0,HIGH);
    GPTM_delay_us(10);
    //SysCtlDelay(180);
    DIO_WritePin(PORTD,BIT0,LOW);
//    SysCtlDelay(16000/3);
}
