#include "bsp_delay.h"
#include "bsp_int.h"

static void delay_short(volatile unsigned int n);

void delay_init(void)
{
    GPT1->CR = 0;
    GPT1->CR = 1 << 15;
    while ((GPT1->CR >> 15) & 0x01);

    GPT1->CR = (1 << 6);
    GPT1->PR = 65;
    GPT1->OCR[0] = 0xFFFFFFFF;
    GPT1->CR |= (1 << 0);
}

void delayus(unsigned int usdelay)
{
    unsigned long oldcnt, newcnt;
    unsigned long tcntvalue = 0;

    oldcnt = GPT1->CNT;

    while (1) 
    {
        newcnt = GPT1->CNT;
        if (newcnt != oldcnt) 
        {
            if (newcnt > oldcnt) 
                tcntvalue += (newcnt - oldcnt);
            else
                tcntvalue += (0xFFFFFFFF + newcnt - oldcnt);

            oldcnt = newcnt;

            if (tcntvalue >= usdelay)
                break;
        }
    }
}

void delayms(unsigned int msdelay) 
{
    int i = 0;
    for (i = 0; i < msdelay; i++)
    {
        delayus(1000);
    }
}

static void delay_short(volatile unsigned int n)
{
    while (n--);
}

void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7FF);
    }
}
