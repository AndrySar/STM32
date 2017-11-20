#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


/* Массив элементов для синусойды */
	const uint16_t mas[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
	3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
	599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
	unsigned char i=0;

int main(void)
{


	RCC-> APB2ENR |= RCC_APB2ENR_IOPAEN;//Тактируем Порт A
	RCC-> APB1ENR |= RCC_APB1Periph_DAC; //Тактируем ЦАП
	RCC-> APB1ENR |= RCC_APB1Periph_TIM6; //Тактируем таймер 6

	// Настройка ноги Цап
	 GPIOA->CRL |= GPIO_CRL_CNF4_1; //Вывод светодиода LED P на выход
	 GPIOA->CRL &=~GPIO_CRL_CNF4; // Двухтактный выход на PC8


	 /* Настраиваем таймер так чтоб он тикал почаще */
	 TIM6->PSC = 0;
	 TIM6->ARR = 500;
	 TIM6->DIER |= TIM_DIER_UIE; //разрешаем прерывание от таймера
	 TIM6->CR1 |= TIM_CR1_CEN; // Начать отсчёт!
	 NVIC_EnableIRQ(54); //Разрешение TIM6_DAC_IRQn прерывания ,
	 //где 54 номер прерывания в векторе прерываний


	 //Настройка DAC1
	 //Преобразован выполняются по прерыванию таймера 6
	  /* Включить DAC1 */

	 // DAC->CR |= DAC_CR_TSEL1; //Выбираем источник запуска - программный
      DAC->CR |= DAC_CR_EN1;

    while(1)
    {
    }
}

void TIM6_DAC_IRQHandler(void) {
TIM6->SR &= ~TIM_SR_UIF; //Сбрасываем флаг UIF
DAC->DHR12R1=2045; //Запихиваем в ЦАП очередной элемент массива
if (i==32) i=0; //Если вывели в ЦАП все 32 значения то начинаем заново
}
