#include "motor.h"

void motorControl_init(void)
{


    DIO_Init(MOTOR_PORT_IN1,PE);
    DIO_Init(MOTOR_PORT_IN3,PB);

//    SET_BIT(SYSCTL_RCGCGPIO_R,MOTOR_PORT_IN1);
//    while(GET_BIT(SYSCTL_RCGCGPIO_R,MOTOR_PORT_IN1)  ==0  ){}

//    SET_BIT(SYSCTL_RCGCGPIO_R,MOTOR_PORT_IN3);
//    while(GET_BIT(SYSCTL_RCGCGPIO_R,MOTOR_PORT_IN3)  ==0  ){}

    SET_BIT(GPIO_PORTE_CR_R,MOTOR_PIN_IN1);
    SET_BIT(GPIO_PORTE_CR_R,MOTOR_PIN_IN2);
    SET_BIT(GPIO_PORTB_CR_R,MOTOR_PIN_IN3);
    SET_BIT(GPIO_PORTE_CR_R,MOTOR_PIN_IN4);

    DIO_SetPinDirection(MOTOR_PORT_IN1,MOTOR_PIN_IN1,OUTPUT);
    DIO_SetPinDirection(MOTOR_PORT_IN2,MOTOR_PIN_IN2,OUTPUT);
    DIO_SetPinDirection(MOTOR_PORT_IN3,MOTOR_PIN_IN3,OUTPUT);
    DIO_SetPinDirection(MOTOR_PORT_IN4,MOTOR_PIN_IN4,OUTPUT);

    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1,LOW);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2,LOW);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3,LOW);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4,LOW);
}

void motor_moveForward(void)
{

    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1, LOW);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2, HIGH);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3, HIGH);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4, LOW);
}

void motor_moveBackward(void)
{
    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1, HIGH);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2, LOW);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3, LOW);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4, HIGH);

}

void motor_moveRight(void)
{

    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1, HIGH);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2, HIGH);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3, HIGH);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4, LOW);
}

void motor_moveLeft(void)
{
    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1, LOW);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2, HIGH);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3, HIGH);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4, HIGH);

}
void motor_Brakes(void)
{

    DIO_WritePin(MOTOR_PORT_IN1,MOTOR_PIN_IN1, LOW);
    DIO_WritePin(MOTOR_PORT_IN2,MOTOR_PIN_IN2, LOW);
    DIO_WritePin(MOTOR_PORT_IN3,MOTOR_PIN_IN3, LOW);
    DIO_WritePin(MOTOR_PORT_IN4,MOTOR_PIN_IN4, LOW);
}
