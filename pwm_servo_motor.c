#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lib/servo_motor.h"

int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O

    printf("Inicializando PWM no pino %d...\n", PWM_SERVO_MOTOR);

    gpio_set_function(PWM_SERVO_MOTOR, GPIO_FUNC_PWM); // Configura GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PWM_SERVO_MOTOR); // Obtém o canal PWM da GPIO

    // Configuração do PWM para 50Hz (20ms de período) com clock de 125MHz, divisor de 100 e wrap de 25000
    pwm_set_clkdiv(slice, 100);
    pwm_set_wrap(slice, 25000);
    pwm_set_enabled(slice, true);

    printf("Posicionando servo em 180 graus...\n");
    // Definição de posições iniciais do servo motor
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 3000); // 180 graus
    sleep_ms(5000);

    printf("Posicionando servo em 90 graus...\n");
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 1838); // 90 graus
    sleep_ms(5000);

    printf("Posicionando servo em 0 graus...\n");
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 625); // 0 graus
    sleep_ms(5000);

    // Loop principal
    while (true) {
        mexe_servo_motor();
    }
}
