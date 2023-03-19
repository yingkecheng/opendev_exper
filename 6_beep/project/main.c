#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"

int main(void) {
    clk_enable();
    led_init();
    beep_init();


    while (1) {
        led_off();
	beep_switch(ON);
        delay(500);

        led_on();
	beep_switch(OFF);
        delay(500);
    }

    return 0;
}

