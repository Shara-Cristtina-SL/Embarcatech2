#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "ws2812b_animation.h"

#define JOYSTICK_VRX 27
#define JOYSTICK_VRY 26

#define JOYSTICK_MAX_VALUE 99
#define JOYSTICK_MIN_VALUE 0

void draw_arrow_up() {
    ws2812b_fill(2, 2, GRB_PINK);
    ws2812b_fill(7, 7, GRB_PINK);
    ws2812b_fill(12, 12, GRB_PINK);
    ws2812b_fill(17, 17, GRB_PINK);
    ws2812b_fill(22, 22, GRB_PINK);

    ws2812b_fill(16, 16, GRB_PINK);
    ws2812b_fill(18, 18, GRB_PINK);
    ws2812b_fill(10, 10, GRB_PINK);
    ws2812b_fill(14, 14, GRB_PINK);
}

void draw_arrow_down() {
    ws2812b_fill(2, 2, GRB_PINK);
    ws2812b_fill(7, 7, GRB_PINK);
    ws2812b_fill(12, 12, GRB_PINK);
    ws2812b_fill(17, 17, GRB_PINK);
    ws2812b_fill(22, 22, GRB_PINK);

    ws2812b_fill(10, 10, GRB_PINK);
    ws2812b_fill(14, 14, GRB_PINK);
    ws2812b_fill(6, 6, GRB_PINK);
    ws2812b_fill(8, 8, GRB_PINK);
}

void draw_arrow_left() {
    ws2812b_fill(10, 10, GRB_PINK);
    ws2812b_fill(11, 11, GRB_PINK);
    ws2812b_fill(12, 12, GRB_PINK);
    ws2812b_fill(13, 13, GRB_PINK);
    ws2812b_fill(14, 14, GRB_PINK);

    ws2812b_fill(16, 16, GRB_PINK);
    ws2812b_fill(22, 22, GRB_PINK);
    ws2812b_fill(6, 6, GRB_PINK);
    ws2812b_fill(2, 2, GRB_PINK);
}

void draw_arrow_right() {
    ws2812b_fill(10, 10, GRB_PINK);
    ws2812b_fill(11, 11, GRB_PINK);
    ws2812b_fill(12, 12, GRB_PINK);
    ws2812b_fill(13, 13, GRB_PINK);
    ws2812b_fill(14, 14, GRB_PINK);

    ws2812b_fill(8, 8, GRB_PINK);
    ws2812b_fill(2, 2, GRB_PINK);
    ws2812b_fill(18, 18, GRB_PINK);
    ws2812b_fill(22, 22, GRB_PINK);
}

uint8_t read_joystick_x() {
    adc_select_input(1);

    return adc_read() * 100 / 4095;
}

uint8_t read_joystick_y() {
    adc_select_input(0);

    return adc_read() * 100 / 4095;
}

void check_joystick(){
    uint8_t vrx = read_joystick_x();
    uint8_t vry = read_joystick_y();

    ws2812b_fill_all(GRB_BLACK);

    if (vrx <= JOYSTICK_MIN_VALUE) {
        draw_arrow_left();
    } else if (vrx >= JOYSTICK_MAX_VALUE) {
        draw_arrow_right();
    } else if (vry <= JOYSTICK_MIN_VALUE) {
        draw_arrow_down();
    } else if (vry >= JOYSTICK_MAX_VALUE) {
        draw_arrow_up();
    } else {
        ws2812b_fill_all(GRB_BLACK);
    }
    ws2812b_render();
}

void init_pins(){
    adc_init();

    adc_gpio_init(JOYSTICK_VRX);
    adc_gpio_init(JOYSTICK_VRY);

    ws2812b_init(pio0, 7, 25);
    ws2812b_set_global_dimming(5);//Ajusta intensidade da matriz de 1 a 7 (quanto menor val mais forte brilho)
}

int main()
{
    stdio_init_all();
    init_pins();

    while (1) {
        check_joystick();
        sleep_ms(100);
    }
    return 0;
}