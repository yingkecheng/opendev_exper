#include "bsp_delay.h"

static void delay_short(volatile unsigned int n);

static void delay_short(volatile unsigned int n) {
    while (n--);
}

void delay(volatile unsigned int n) {
    while (n--) {
        delay_short(0x7FF);
    }
}
