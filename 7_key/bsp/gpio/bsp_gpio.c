#include "bsp_gpio.h"

void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config) {
    if (config->direction == kGPIO_DigitalInput) {
        base->GDIR &= ~(1 << pin);
    } else {
        base->GDIR |= (1 << pin);
        gpio_pinwrite(base, pin, config->outputLogic);
    }
}

int gpio_pinread(GPIO_Type *base, int pin) {
    return ((base->DR >> pin) & 0x01);
}

void gpio_writepin(GPIO_Type *base, int pin, int value) {
    if (value == 0U) {
        base->DR &= ~(1U << pin);
    } else {
        base->DR |= (1U << pin);
    }
}