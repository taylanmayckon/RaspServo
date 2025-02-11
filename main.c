#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22 // Pino do servo

uint wrap = 20000; // definindo o WRAP do PWM
uint di = 125; // Divisor inteiro 
bool rotate_direction = true; // True = crescente, false=decrescente

void config_servo_pwm(uint gpio){
    // Equação para a f_pwm:
    // f_pwm = f_clk/((di+(df/16))*(wrap+1))
    // Se fizer com di=125 e wrap=20000, a frequência bate com os 50Hz solicitados

    gpio_set_function(gpio, GPIO_FUNC_PWM); // Habilitando o pino como pwm
    uint slice = pwm_gpio_to_slice_num(gpio); // Obtendo o canal (slice) do PWM 
    pwm_set_clkdiv(slice, di); // Definindo o divisor de clock do PWM
    pwm_set_wrap(slice, wrap); // Definindo o valor de wrap (contador do PWM)
    pwm_set_gpio_level(gpio, 0.12*wrap); // Iniciando com 0.12% de Duty Cycle (corresponde à 180º no servo)
    pwm_set_enabled(slice, true); // Habilitando o pwm no slice correspondente
}

void first_routine(){
    sleep_ms(5000); // Atraso de 5000s (porque já começa com o primeiro angulo ajustado)
    pwm_set_gpio_level(SERVO_PIN, 0.0735*wrap); // Ajustando o braço para 90º
    sleep_ms(5000);
    pwm_set_gpio_level(SERVO_PIN, 0.025*wrap); // Ajustando o braço para 0º
    sleep_ms(5000);
}


int main(){
    stdio_init_all();

    config_servo_pwm(SERVO_PIN);

    first_routine();

    while (true) {
        for(float dc = 0.025; dc <= 0.12; dc = dc+(0.025/100)){ // Rotina de subida do angulo (0 a 180º)
            pwm_set_gpio_level(SERVO_PIN, dc*wrap); // Ajustando o Duty Cycle para o novo angulo
            sleep_ms(10); // Atraso solicitado (10ms)
        }

        for(float dc = 0.12; dc >= 0.025; dc = dc-(0.025/100)){ // Rotina de descida do angulo (180 a 0º)
            pwm_set_gpio_level(SERVO_PIN, dc*wrap); // Ajustando o Duty Cycle para o novo angulo
            sleep_ms(10); // Atraso solicitado (10ms)
        }
    }
}
