#include <stdio.h>
#include "pico/stdlib.h"
#include "ws2818b.pio.h"
#include "hardware/pio.h"
#include "digitos.h"
#include "write_matrix.h"
#include "pico/bootrom.h"

#define LED_MATRIZ 7
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_BOOTSEL 22


void rgb_clean_except(int exception_led){
    for (int i=11; i<13; i++){
        if (i != exception_led)
            gpio_put(i, 0);
    }
}

uint count_numbers = 0;
uint32_t last_time;
void gpio_irq_handler(uint gpio, uint32_t event_mask) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time > 200000){
        if (gpio == BUTTON_A) {
            rgb_clean_except(LED_GREEN);
            gpio_put(LED_GREEN, !gpio_get(LED_GREEN));
            printf("O LED_GREEN foi alterado\n!");
        }
        if (gpio == BUTTON_B) {
            rgb_clean_except(LED_BLUE);
            gpio_put(LED_BLUE, !gpio_get(LED_BLUE));
            printf("O LED_BLUE foi alterado\n!");


        }
        last_time = current_time;
    }

}
int main()
{
    stdio_init_all();

    npInit(LED_MATRIZ);
    npClear();
    npWrite();


    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_init(BUTTON_BOOTSEL);
    gpio_set_dir(BUTTON_BOOTSEL, GPIO_IN);
    gpio_pull_up(BUTTON_BOOTSEL);

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {

        if (!gpio_get(BUTTON_BOOTSEL)) {
            rom_reset_usb_boot(0, 0);
        }
        //desenha_numeros(count_numbers);
        sleep_ms(200);
    }
}
