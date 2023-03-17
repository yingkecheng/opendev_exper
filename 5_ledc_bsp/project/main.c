#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"

int main(void) {
    clk_enable();
    led_init();

    while (1) {
        led_off();
        delay(500);

        led_on();
        delay(500);
    }

    return 0;
}