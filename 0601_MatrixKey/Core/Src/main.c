#include "main.h"

uint16_t i, KeyVal = 0;
uint8_t PreLine[3] = {1, 2, 3};

void Error_Handler(void);

int main(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  HAL_Init();

  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  // PE4 PE5 PE6
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET);

  // PE0~PE3
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // PF0~PF7 LED??
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                      |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  GPIOF->ODR = 0xFF;

  while (1)
  {
    KeyVal = 0;
    for(i = 0; i < 3; i++)
    {
      GPIOE->ODR |= (1 << 4) | (1 << 5) | (1 << 6);
      GPIOE->ODR &= ~(1 << (i + 4));
      HAL_Delay(1);

      if((GPIOE->IDR & 0x0F) != 0x0F)
      {
        HAL_Delay(16);
        if((GPIOE->IDR & 0x0F) != 0x0F)
        {
          switch(i)
          {
            case 0: //K1~K4
              switch(GPIOE->IDR & 0x0F)
              {
                case 0x0E: KeyVal = 1; break;
                case 0x0D: KeyVal = 2; break;
                case 0x0B: KeyVal = 3; break;
                case 0x07: KeyVal = 4; break;
              }
              break;
            case 1: // K5~K8
              switch(GPIOE->IDR & 0x0F)
              {
                case 0x0E: KeyVal = 5; break;
                case 0x0D: KeyVal = 6; break;
                case 0x0B: KeyVal = 7; break;
                case 0x07: KeyVal = 8; break;
              }
              break;
            case 2: // K9~K12
              switch(GPIOE->IDR & 0x0F)
              {
                case 0x0E: KeyVal = 9; break;
                case 0x0D: KeyVal = 10; break;
                case 0x0B: KeyVal = 11; break;
                case 0x07: KeyVal = 12; break;
              }
              break;
          }
          while((GPIOE->IDR & 0x0F) != 0x0F);
          HAL_Delay(16);

          // 8421 BCD
          switch(KeyVal)
          {
            case 1:  GPIOF->ODR = 0xFE; break;
            case 2:  GPIOF->ODR = 0xFD; break;
            case 3:  GPIOF->ODR = 0xFC; break;
            case 4:  GPIOF->ODR = 0xFB; break;
            case 5:  GPIOF->ODR = 0xFA; break;
            case 6:  GPIOF->ODR = 0xF9; break;
            case 7:  GPIOF->ODR = 0xF8; break;
            case 8:  GPIOF->ODR = 0xF7; break;
            case 9:  GPIOF->ODR = 0xF6; break;
            case 10: GPIOF->ODR = 0xEF; break;
            case 11: GPIOF->ODR = 0xEE; break;
            case 12: GPIOF->ODR = 0xED; break;
            default: GPIOF->ODR = 0xFF; break;
          }
          HAL_Delay(2000);   
          GPIOF->ODR = 0xFF; 
        }
      }
    }
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}