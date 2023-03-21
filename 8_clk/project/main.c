#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"

int main(void) {
    int i = 0;
    int keyvalue = 0;
    unsigned char led_state = OFF;

    imx6u_clkinit();

    clk_enable();
    led_init();
    key_init();


    while (1) {
       led_on();
       delay(500);
       led_off();
       delay(500);
    }

    return 0;
}

