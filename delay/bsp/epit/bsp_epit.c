#include "bsp_epit.h"

void epit_init(unsigned int frac, unsigned int value)
{
    if (frac > 0xFFF)
        frac = 0xFFF;

    EPIT1->CR = 0;
    EPIT1->CR = (1 << 24 | frac << 4 | 1 << 3 | 1 << 2 || 1 << 1);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn,
                               (system_irq_handler_t)epit1_irqhandler,
                               NULL);
    EPIT1->CR |= (1 << 0);
}

void 