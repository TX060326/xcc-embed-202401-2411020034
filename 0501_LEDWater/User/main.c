#include "stm32f407xx.h"

void Delay_ms(uint32_t ms)
{
    uint32_t i,j;
    for(i=0; i<ms; i++)
        for(j=0; j<20000; j++);
}

void LED_Init(void)
{
    RCC->AHB1ENR |= (1 << 5);
    GPIOF->MODER &= ~0x0000FFFF;
    GPIOF->MODER |=  0x00005555;
    GPIOF->ODR |= 0x00FF;   // ????1,??
}

int main(void)
{
    uint8_t pos = 0;
    uint8_t dir = 0;
    LED_Init();
    while(1)
    {
        GPIOF->ODR = ~(1 << pos); // ??pos??0,??;???1??
        Delay_ms(150);

        if(dir == 0)
        {
            pos++;
            if(pos >= 7)
            {
                dir = 1;
            }
        }
        else
        {
            pos--;
            if(pos <= 0)
            {
                dir = 0;
            }
        }
    }
}