#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"



void clk_enable(void) {
    CCM->CCGR0 = 0xFFFFFFFF;
    CCM->CCGR1 = 0xFFFFFFFF;
    CCM->CCGR2 = 0xFFFFFFFF;
    CCM->CCGR3 = 0xFFFFFFFF;
    CCM->CCGR4 = 0xFFFFFFFF;
    CCM->CCGR5 = 0xFFFFFFFF;
    CCM->CCGR6 = 0xFFFFFFFF;
}

void led_init(void) {
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);

    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);

    GPIO1->GDIR |= (1 << 3);
    GPIO1->DR &= ~(1 << 3);
}

void led_on(void) {
    GPIO1->DR &= ~(1 << 3);
}

void led_off(void) {
    GPIO1->DR |= (1 << 3);
}

void delay_short(volatile unsigned int n) {
    while (n--);
}

void delay(volatile unsigned int n) {
    while (n--) {
        delay_short(0x7FF);
    }
}

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