#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22 // Pino do servo

uint slice; // Definindo a variávle slice no escopo global
uint wrap = 20000; // definindo o WRAP do PWM
uint di = 125; // Divisor inteiro 

void config_servo_pwm(){
    // Equação para a f_pwm:
    // f_pwm = f_clk/((di+(df/16))*(wrap+1))
    // Se fizer com di=125 e wrap=20000, a frequência bate com os 50Hz solicitados

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Habilitando o pino como pwm
    slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtendo o canal (slice) do PWM 
    pwm_set_clkdiv(slice, di); // Definindo o divisor de clock do PWM
    pwm_set_wrap(slice, wrap); // Definindo o valor de wrap (contador do PWM)
    pwm_set_gpio_level(SERVO_PIN, 0.12*20000); // Iniciando com 0% de Duty Cycle
    pwm_set_enabled(slice, true); // Habilitando o pwm no slice correspondente
}


int main(){
    stdio_init_all();

    config_servo_pwm();

    while (true) {
        sleep_ms(1000);
    }
}
