# **Controle de Servo Motor com Raspberry Pi Pico W**
## **Visão Geral**
Este projeto controla um **servo motor** usando **PWM (Pulse Width Modulation)** no microcontrolador **Raspberry Pi Pico**.
## **Video Apresentação**

https://drive.google.com/file/d/12O62ZDkDq_WU_7WzxygeqzjNbCqq_G_v/view?usp=sharing
---

## **Componentes Utilizados**
- **Raspberry Pi Pico W**
- **Servo motor**

---

## **Como Funciona?**
- O **PWM (Modulação por Largura de Pulso)** é utilizado para controlar a posição do servo motor.  
- O código inicia o servo em diferentes posições fixas (**0°, 90°, 180°**) e depois entra em um loop contínuo.  
- No loop, o servo move suavemente de **0° a 180°** e depois retorna a **0°**.

---

## **Estrutura do Código**
O código foi dividido em três arquivos principais:

📂 `servo_motor.h` → **Arquivo de cabeçalho (declarações)**  
📂 `servo_motor.c` → **Implementação da movimentação do servo**  
📂 `main.c` → **Código principal (configuração e loop principal)**  

---

## **Explicação dos Arquivos**
### **- Arquivo: `servo_motor.h`**
**Objetivo:** Contém a definição do pino do servo motor e a declaração da função responsável pela movimentação.  
**Código:**  
```c
#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_SERVO_MOTOR 22 // Definição do pino do servo motor

// Função para movimentar o servo motor de 0 a 180 graus e vice-versa
void mexe_servo_motor);

#endif
```
**Explicação:**  
✔ `#ifndef SERVO_MOTOR_H` e `#define SERVO_MOTOR_H` → Evita que o arquivo seja incluído mais de uma vez.  
✔ `#include "pico/stdlib.h"` e `#include "hardware/pwm.h"` → Bibliotecas necessárias para o funcionamento do PWM.  
✔ `#define PWM_SERVO_MOTOR 22` → Define o pino GPIO utilizado para o servo.  
✔ Declara a função `mexe_servo_motor()`, que será definida no arquivo `.c`.  

---

### **- Arquivo: `servo_motor.c`**
**Objetivo:** Implementa a lógica de movimentação do servo motor.  
**Código:**  
```c
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
    }

    printf("Servo atingiu 180 graus.\n");
    sleep_ms(1000);

    printf("Movendo de 180 para 0 graus...\n");

    // Movimento de 180 a 0 graus
    while (ciclo_ativo >= 625) {
        ciclo_ativo -= 5;
        pwm_set_gpio_level(PWM_SERVO_MOTOR, ciclo_ativo);
        sleep_ms(10);
    }

    printf("Servo retornou para 0 graus.\n");
    sleep_ms(1000);
}
```
**Explicação:**  
✔ `ciclo_ativo = 625` → Define a posição inicial do servo (correspondente a **0°**).  
✔ Laço `while (ciclo_ativo <= 3000)` → Aumenta gradativamente o PWM até atingir **180°**.  
✔ Laço `while (ciclo_ativo >= 625)` → Reduz gradativamente o PWM até retornar a **0°**.  
✔ `printf()` → Mensagens no console para depuração e acompanhamento das ações.  
✔ `sleep_ms(10)` → Atraso para suavizar o movimento do servo.  

---

### **- Arquivo: `main.c`**
**Objetivo:** Configura o PWM e inicia o loop de movimentação do servo.  
**Código:**  
```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo_motor.h"

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
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 3000); // 180 graus
    sleep_ms(5000);

    printf("Posicionando servo em 90 graus...\n");
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 1838); // 90 graus
    sleep_ms(5000);

    printf("Posicionando servo em 0 graus...\n");
    pwm_set_gpio_level(PWM_SERVO_MOTOR, 625); // 0 graus
    sleep_ms(5000);

    printf("Iniciando movimentação contínua...\n");

    // Loop principal
    while (true) {
        mexe_servo_motor();
    }
}
```
**Explicação:**  
✔ `stdio_init_all();` → Inicializa a comunicação serial para exibir mensagens no terminal.  
✔ `gpio_set_function(PWM_SERVO_MOTOR, GPIO_FUNC_PWM);` → Configura o pino do servo como saída PWM.  
✔ Configuração do PWM com frequência de **50Hz (20ms)**.  
✔ Define o servo em **180°, 90° e 0°**, antes de iniciar o loop.  
✔ `while (true)` → Chama continuamente a função `mexe_servo_motor_de_0_a_180_e_reverso()` para manter o movimento.  

---

## **Compilação e Execução**

### **➡ Usando CMake (`CMakeLists.txt`)**
Foi adicionado ao **CMake**:
```cmake
add_executable(meu_programa
    pwm_servo_motor.c
    lib/servo_motor.c
)
```

### **Clonar Repositório**
```
git remote add origin https://github.com/01Keven/pwm_servo_motor.git
```
Clone o projeto para conseguir rodar ele localmente.
