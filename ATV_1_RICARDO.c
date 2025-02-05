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
    // Desliga todos os LEDs antes de acender o próximo
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_GREEN, 0);
    gpio_put(LED_PIN_BLUE, 0);

    // Acende o LED correspondente ao estado atual
    switch (estado_led)
    {
    case 0:
        printf("VERMELHO ACESO \n");
        gpio_put(LED_PIN_RED, 1);
        break;
    case 1:
        printf("VERDE ACESO \n");
        gpio_put(LED_PIN_GREEN, 1);
        break;
    case 2:
        printf("AZUL ACESO \n");
        gpio_put(LED_PIN_BLUE, 1);
        break;
    }

    // Atualiza o estado do LED ciclicamente
    estado_led = (estado_led + 1) % 3;

    return true; // Continua o timer
}

// Função principal
int main()
{
    // Inicialização serial
    stdio_init_all();

    // Inicialização dos pinos dos LEDs
    int led_pins[] = {LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE};
    for (int i = 0; i < 3; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], true);
    }

    // Estrutura para o timer
    struct repeating_timer timer;

    // Configuração para iniciar o timer
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito com mensagem periódica
    while (true)
    {
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
    }

    return 0;
}
