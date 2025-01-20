#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definições das portas GPIO dos LEDs
#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13

// Definição da porta GPIO do BUZZER
#define BUZZER_PIN 21

// Definições da UART
// Por padrão, o stdout UART é uart0, então usaremos o segundo UART
#define UART_ID uart1
#define BAUD_RATE 115200

// Usar pinos 4 e 5 para UART1
// Os pinos podem ser alterados, veja a tabela de seleção de função GPIO no datasheet para informações sobre as atribuições GPIO
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// Função para definir a frequência do buzzer


void set_buzzer_frequency(uint pin, uint frequency) {
     // Obter o slice do PWM associado ao pino
     uint slice_num = pwm_gpio_to_slice_num(pin);

     // Configurar o pino como saída de PWM
     gpio_set_function(pin, GPIO_FUNC_PWM);
     
     // Configurar o PWM com a frequência desejada
     pwm_config config = pwm_get_default_config();
     pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Calcula o divisor do clock
     pwm_init(slice_num, &config, true);
     pwm_set_gpio_level(pin, 0); // Inicializa com duty cycle 0 (sem som)
}

// Função para tocar o buzzer por uma duração específica

void play_buzzer(uint pin, uint frequency, uint duration_ms) {
    set_buzzer_frequency(pin, frequency); // Configura a frequência do buzzer
    pwm_set_gpio_level(pin, 2048); // Define o nível do PWM (50% duty cycle)
    sleep_ms(duration_ms); // Espera pela duração especificada
    pwm_set_gpio_level(pin, 0); // Desliga o buzzer
}

// Redefinição de algumas variáveis globais
#define UART_ID uart1 
#define BAUD_RATE 115200 
#define UART_TX_PIN 4 
#define UART_RX_PIN 5

#define green_pin 11
#define blue_pin 12
#define red_pin 13
#define botaoA_pin 5
#define botaoB_pin 6

// Função para inicializar a UART e os GPIOs

void inicia () {
    stdio_init_all(); // Inicializa todas as saídas padrão
    uart_init(UART_ID, BAUD_RATE); // Inicializa a UART com a taxa de baud
    sleep_ms(3000); // Espera 3 segundos

    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configura o pino TX para UART
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configura o pino RX para UART

    gpio_init(blue_pin); // Inicializa o pino do LED azul
    gpio_set_dir(blue_pin, GPIO_OUT); // Configura o pino do LED azul como saída

    gpio_init(green_pin); // Inicializa o pino do LED verde
    gpio_set_dir(green_pin, GPIO_OUT); // Configura o pino do LED verde como saída

    gpio_init(red_pin); // Inicializa o pino do LED vermelho
    gpio_set_dir(red_pin, GPIO_OUT); // Configura o pino do LED vermelho como saída

    gpio_init(botaoB_pin); // Inicializa o pino do botão B
    gpio_init(botaoA_pin); // Inicializa o pino do botão A
}



int main() {
    inicia(); // Chama a função de inicialização

    gpio_set_dir(botaoA_pin, GPIO_IN); // Configura o pino do botão A como entrada
    gpio_pull_up(botaoA_pin); // Ativa o pull-up interno para o botão A
    gpio_init(botaoB_pin); 
    gpio_set_dir(botaoB_pin, GPIO_IN); // Configura o pino do botão B como entrada
    gpio_pull_up(botaoB_pin); // Ativa o pull-up interno para o botão B

    while (true) {
        // Imprime o menu
        printf("\nMenu:\n"); 
        printf("A - Ligar LED Vermelho\n"); 
        printf("B - Ligar LED Azul\n"); 
        printf("C - Ligar LED Verde\n"); 
        printf("D - Ligar LED Branco\n"); 
        printf("# - Ativar Buzzer\n"); 
        printf("Digite sua escolha: ");
        
        // Lê a escolha do usuário
        char ESCOLHA;
        scanf(" %c", &ESCOLHA);  // Espaço antes de %c para ignorar espaços em branco
        
        // Executa ações com base na escolha do usuário
        if (ESCOLHA == 'A') {
            gpio_put(blue_pin, 0);
            gpio_put(green_pin, 0);
            gpio_put(red_pin, 1); // Liga o LED vermelho
            printf("LED RED ON\n");
        } else if (ESCOLHA == 'C') {
            gpio_put(green_pin, 1); // Liga o LED verde
            gpio_put(blue_pin, 0);
            gpio_put(red_pin, 0);
            printf("LED GREEN ON\n");
        } else if (ESCOLHA == 'B') {
            gpio_put(blue_pin, 1); // Liga o LED azul
            gpio_put(green_pin, 0);
            gpio_put(red_pin, 0);
            printf("LED BLUE ON\n");
        } else if (ESCOLHA == 'D') {
            gpio_put(blue_pin, 1); // Liga todos os LEDs (branco)
            gpio_put(green_pin, 1);
            gpio_put(red_pin, 1);
            printf("LED WHITE ON\n");
        } else if (ESCOLHA == '#') {
            gpio_put(GREEN_LED_PIN, 0);
            gpio_put(BLUE_LED_PIN, 0);
            gpio_put(RED_LED_PIN, 0); // Desliga todos os LEDs
            play_buzzer(BUZZER_PIN, 3350, 2000); // Ativa o buzzer
            printf("BUZZER ON\n");
            break; // Encerra o loop
        } else {
            gpio_put(blue_pin, 0);
            gpio_put(green_pin, 0);
            gpio_put(red_pin, 0); // Desliga todos os LEDs
            printf("Entrada inválida!\n");
        }
    }

    return 0;
}

