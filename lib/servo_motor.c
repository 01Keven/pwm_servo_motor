#include "servo_motor.h"
#include <stdio.h>

void mexe_servo_motor() {
    uint ciclo_ativo = 625; // Posição inicial do servo motor (0 graus)

    printf("Movendo de 0 para 180 graus...\n");

    // Movimento de 0 a 180 graus
    while (ciclo_ativo <= 3000) {
        ciclo_ativo += 5;
        pwm_set_gpio_level(PWM_SERVO_MOTOR, ciclo_ativo);
        sleep_ms(10);
        printf("Servo atingiu 180 graus.\n");
    }


    // Movimento de 180 a 0 graus
    while (ciclo_ativo >= 625) {
        printf("Movendo de 180 para 0 graus...\n");
        ciclo_ativo -= 5;
        pwm_set_gpio_level(PWM_SERVO_MOTOR, ciclo_ativo);
        printf("Servo retornou para 0 graus.\n");
        sleep_ms(10);

    }

}
