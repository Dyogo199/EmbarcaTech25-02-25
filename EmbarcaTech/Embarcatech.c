#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

// Definindo os pinos
#define MQ135_PIN 26        // GPIO26 (ADC0) para o MQ135
#define DHT_PIN 15          // GPIO15 para o DHT22
#define AC_DIMMER_PIN 18    // GPIO18 para controle do AC Dimmer via PWM

// Definindo os ganhos do PID
#define Kp 2.0
#define Ki 5.0
#define Kd 1.0

// Variáveis para o controle PID
double inputTemperature = 0.0, outputPWM = 0.0, setPointTemperature = 30.0; // Temperatura alvo: 30°C
double last_input = 0.0, integral = 0.0;

// Função para configurar o ADC do MQ135
void init_adc() {
    adc_init();
    adc_gpio_init(MQ135_PIN);  // Inicializa o pino GPIO26 para ADC
    adc_select_input(0);       // Seleciona o canal ADC0 (pino GPIO26)
}

// Função para ler o valor do MQ135
uint16_t read_mq135() {
    uint16_t raw_value = adc_read();  // Lê o valor analógico
    return raw_value;
}

// Função para configurar o PWM para o AC Dimmer
void init_pwm() {
    gpio_set_function(AC_DIMMER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(AC_DIMMER_PIN);
    pwm_set_clkdiv(slice_num, 8.00);  // Ajuste de frequência do PWM
    pwm_set_wrap(slice_num, 255);    // Ajuste do ciclo de trabalho do PWM
    pwm_set_enabled(slice_num, true);
}

// Função para ajustar o PWM com base no valor do duty cycle
void set_pwm_duty(uint8_t duty) {
    uint slice_num = pwm_gpio_to_slice_num(AC_DIMMER_PIN);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty);  // Define o valor do duty cycle
}

// Função de controle de temperatura com PID
void control_temperature() {
    // Erro (setpoint - entrada)
    double error = setPointTemperature - inputTemperature;

    // Calculando a integral
    integral += error;

    // Derivada (mudança do erro)
    double derivative = inputTemperature - last_input;

    // Calculando a saída do PID
    outputPWM = (Kp * error) + (Ki * integral) - (Kd * derivative);

    // Atualizando o valor da entrada anterior
    last_input = inputTemperature;

    // Ajustando o PWM baseado na saída do PID
    set_pwm_duty((uint8_t)outputPWM);
}

// Função para ler o sensor DHT22
int read_dht22(float *temperature, float *humidity) {
    // Variáveis de controle para o protocolo de 1 fio
    uint8_t data[5] = {0};
    uint32_t timeout;

    // Inicializa o pino de dados
    gpio_init(DHT_PIN);
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0); // Envia um pulso baixo de 18ms
    sleep_ms(18);
    gpio_set_dir(DHT_PIN, GPIO_IN);
    sleep_us(40);

    // Espera a resposta do DHT
    timeout = time_us_32();
    while (gpio_get(DHT_PIN) == 1) {
        if ((time_us_32() - timeout) > 1000) return 0; // Timeout
    }
    
    timeout = time_us_32();
    while (gpio_get(DHT_PIN) == 0) {
        if ((time_us_32() - timeout) > 1000) return 0; // Timeout
    }

    timeout = time_us_32();
    while (gpio_get(DHT_PIN) == 1) {
        if ((time_us_32() - timeout) > 1000) return 0; // Timeout
    }

    // Lê os dados do sensor
    for (int i = 0; i < 5; i++) {
        for (int j = 7; j >= 0; j--) {
            timeout = time_us_32();
            while (gpio_get(DHT_PIN) == 0) {
                if ((time_us_32() - timeout) > 1000) return 0; // Timeout
            }

            timeout = time_us_32();
            while (gpio_get(DHT_PIN) == 1) {
                if ((time_us_32() - timeout) > 1000) return 0; // Timeout
            }

            if (time_us_32() - timeout > 40) {
                data[i] |= (1 << j); // Se a duração for maior que 40ms, é 1
            }
        }
    }

    // Verifica a soma de verificação
    if (data[0] + data[1] + data[2] + data[3] != data[4]) return 0;

    // Calcula a temperatura e umidade
    *humidity = (float)((data[0] << 8) + data[1]) / 10.0;
    *temperature = (float)((data[2] << 8) + data[3]) / 10.0;

    return 1; // Sucesso
}

int main() {
    stdio_init_all();  // Inicializa a biblioteca padrão (serial)
    init_adc();        // Configura o ADC para o MQ135
    init_pwm();        // Configura o PWM para o AC Dimmer

    while (1) {
        // Leitura do sensor MQ135
        uint16_t mq135_value = read_mq135();
        printf("Valor do MQ135: %u\n", mq135_value);  // Exibe o valor do MQ135 no monitor serial

        // Leitura do DHT22 e controle da temperatura
        float temperature = 0.0, humidity = 0.0;
        if (read_dht22(&temperature, &humidity)) {
            inputTemperature = temperature;  // Atualiza a temperatura para o PID
            printf("Temperatura: %.2f°C, Umidade: %.2f%%\n", temperature, humidity);

            // Controla a temperatura com o PID
            control_temperature();
        } else {
            printf("Falha na leitura do DHT22.\n");
        }

        sleep_ms(2000);  // Atraso de 2 segundos antes de ler novamente
    }

    return 0;
}
