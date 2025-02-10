#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição do pino do servo motor
#define PWM_SERVO_MOTOR 22 

// Função para movimentar o servo motor de 0 a 180 graus e vice-versa
void mexe_servo_motor();

#endif
