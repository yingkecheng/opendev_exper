#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"
#include "bsp_uart.h"

int main(void) {
	unsigned char a = 0;
	unsigned char state = OFF;
	
	int_init();
	imx6u_clkinit();
	delay_init();
    clk_enable();
	led_init();
	key_init();
	beep_init();
	uart_init();

	while (1) {
		puts("請你輸入字符：");
		a = getc();
		putc(a);
		puts("\r\n");

		puts("您输入的字符为:");
		putc(a);
		puts("\r\n\r\n");

		state = !state;
		led_switch(LED0, state);
	}
	return 0;
}

