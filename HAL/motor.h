/*
 * motor.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Lenovo
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <Utilities/std_types.h>
#include <MCAL/DIO.h>
#include <Tiva_Registers.h>
#include <Utilities/Bitwise_Operations.h>
#include <MCAL/PWM.h>

/*input pins for motors*/
#define MOTOR_PORT_IN1 PORTE            //IN1 --> PE1
#define MOTOR_PIN_IN1 BIT1

#define MOTOR_PORT_IN2 PORTE
#define MOTOR_PIN_IN2 BIT4              //IN2 --> PE4

#define MOTOR_PORT_IN3 PORTB            //IN3 --> PB5
#define MOTOR_PIN_IN3 BIT5

#define MOTOR_PORT_IN4 PORTE    //IN4 --> PE0
#define MOTOR_PIN_IN4 BIT0

void motorControl_init(void);
void motor_moveForward(void);
void motor_moveBackward(void);
void motor_moveRight(void);
void motor_moveLeft(void);
void motor_brakes(void);

#endif /* MOTOR_H_ */
