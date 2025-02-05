// Inclusão de bibliotecas padrão para funcionamento do código
#include "stdio.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"

// Definição dos pinos dos LEDs RGB
#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12

// Variável para controle do estado dos LEDs
int estado_led = 0;

// Função de callback para o timer
bool repeating_timer_callback(struct repeating_timer *t)
{
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_GREEN, 0);
    gpio_put(LED_PIN_BLUE, 0);

    // Verifica o estado do LED e acende o LED correspondente
    if (estado_led == 0)
    { // VERMELHO caso estado_led = 0
        printf("VERMELHO ACESO \n");
        gpio_put(LED_PIN_RED, 1);
    }
    else if (estado_led == 1)
    { // VERDE caso estado_led = 1
        printf("VERDE ACESO \n");
        gpio_put(LED_PIN_GREEN, 1);
    }
    else if (estado_led == 2)
    { // AZUL caso estado_led = 2
        printf("AZUL ACESO \n");
        gpio_put(LED_PIN_BLUE, 1);
    }

    // Atualiza o estado do LED
    estado_led = (estado_led + 1) % 3;

    // Retorna true para continuar o timer
    return true;
}

// Função principal
int main()
{
    // Inicialização serial
    stdio_init_all();

    // Inicialização dos pinos dos LEDs
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, true);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, true);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, true);

    // Estrutura para o timer
    struct repeating_timer timer;

    // Configuração para iniciar o timer
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito
    while (true)
    {
        // Aguarda 1 segundo e imprime uma mensagem
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
    }

    return 0;
}