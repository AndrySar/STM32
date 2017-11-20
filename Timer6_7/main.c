#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "core_cm3.h"
#include "misc.h"

//void TIM7_IRQHandler(void);
void TIM6_DAC_IRQHandler(void);

uint8_t i;

int main(void)
{
//  IRQn_Type TIM6_IRQn;
	RCC-> APB2ENR |= RCC_APB2ENR_IOPCEN;

	  GPIOC->CRH |= GPIO_CRH_MODE9_1; // Вывод светодиода LED3 PC9 на выход.
	  GPIOC->CRH &=~GPIO_CRH_CNF9; // Двухтактный выход на PC9.

	//  NVIC_SetPriority( , 1); // Устанавливаем приоритет прерывания TIM6
	  NVIC_EnableIRQ(54); //Разрешаем обработку прерывания TIM6

	  RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV8; //Делитель на шине AHB , делитель на 8

	  //TIM6 init
	  RCC->APB1ENR |=  RCC_APB1Periph_TIM6;// Тактируем шину
	  TIM6->PSC= 0xFFFF; // Устанавливаем предделитель таймера в наше случае 65535
	  TIM6->ARR = 0x000F; //Перезагружаемое значение или проще задержка обработки прерывания
	  TIM6->DIER |= TIM_DIER_UIE; //Разрешаем генерацию прерывания
	  TIM6->CR1 |= TIM_CR1_CEN; //Запускаем счетчик таймера


    while(1)
    {
    }
}

void TIM6_DAC_IRQHandler(void)
{
	TIM6->SR &= ~TIM_SR_UIF; //Сбрасываем флаг перрывания UIF
	  if (i == 0) GPIOC->BSRR |= GPIO_BSRR_BS9;
	  else GPIOC->BSRR |= GPIO_BSRR_BR9;
	  i = ~i;
}

void TIM7_IRQHandler(void)
 {
  TIM7->SR &= ~TIM_SR_UIF; //Сбрасываем флаг перрывания UIF
  if (i == 0) GPIOC->BSRR |= GPIO_BSRR_BS9;
  else GPIOC->BSRR |= GPIO_BSRR_BR9;
  i = ~i;
 }

