#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22 // Pino do servo
#define LED_PIN 12 // Pino do Led Azul

uint wrap = 20000; // definindo o WRAP do PWM
uint di = 125; // Divisor inteiro 
bool rotate_direction = true; // true = angulo crescente; false = angulo decrescente
float servo_duty_cycle = 0.025; // Valor inicial do DC do servo

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
    printf("%d", slice);
}

void first_routine(){
    sleep_ms(5000); // Atraso de 5000s (porque já começa com o primeiro angulo ajustado)
    pwm_set_gpio_level(SERVO_PIN, 0.0735*wrap); // Ajustando o braço para 90º
    pwm_set_gpio_level(LED_PIN, 0.0735*wrap); // Ajustando o led para visualizar na BitDogLab
    sleep_ms(5000);
    pwm_set_gpio_level(SERVO_PIN, 0.025*wrap); // Ajustando o braço para 0º
    pwm_set_gpio_level(LED_PIN, 0.025*wrap); // Ajustando o led para visualizar na BitDogLab
    sleep_ms(5000);
}

// Interrupção com temporizador para ajustar o pwm a cada 10ms
bool pwm_repeating_timer_callback(struct repeating_timer *t){
    // Decisão da direção de rotação
    if(servo_duty_cycle >= 0.12){ 
        rotate_direction = false; // Ajusta a rotação para decrescente
    }
    else if(servo_duty_cycle <= 0.025){
        rotate_direction = true; // Ajusta a rotação para crescente
    }

    // Incrementos/decrementos de rotação
    if(rotate_direction){
        servo_duty_cycle += (0.025/100);
        pwm_set_gpio_level(SERVO_PIN, servo_duty_cycle*wrap);
    } else{
        servo_duty_cycle -= (0.025/100);
        pwm_set_gpio_level(SERVO_PIN, servo_duty_cycle*wrap);
    }

    return true; // Retorna true para repetir a interrupção
}


int main(){
    stdio_init_all();

    config_servo_pwm(SERVO_PIN);
    config_servo_pwm(LED_PIN);

    // Chamando a rotina que muda o angulo a cada 5000s
    first_routine();

    // Configurando o repeating timer para 10ms
    struct repeating_timer timer;
    add_repeating_timer_ms(10, pwm_repeating_timer_callback, NULL, &timer);

    while (true) {
        // Superloop vazio por conta da interrupção periódica
    }
}
