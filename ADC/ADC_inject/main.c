#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay(uint32_t i);

int main(void)
{

	     RCC-> APB2ENR |= RCC_APB2ENR_IOPCEN; // Тактируем порт C

		  GPIOC->CRH |= GPIO_CRH_MODE9_1; // Вывод светодиода LED3 PC9 на выход.
		  GPIOC->CRH &=~GPIO_CRH_CNF9; // Двухтактный выход на PC9.

		  GPIOC->CRH |= GPIO_CRH_MODE8_1; //Вывод светодиода LED PC8 на выход
		  GPIOC->CRH &=~GPIO_CRH_CNF8; // Двухтактный выход на PC8
		  // Настройки светодиодов следующие : 2 МГц , Альтернативная функция  output Push-pull

		  RCC-> APB2ENR |= RCC_APB2ENR_IOPAEN; //Тактируем порт A
		  //Мы будем использовать ногу порта A PA1, данная ножка по умолчания настроена на вход,
		  //что нам и надо, т.к на эту ножку мы будем подавать измеряемое напряжения.

		  RCC-> APB2ENR |= RCC_APB2ENR_ADC1EN;// Тактируем АЦП
		  ADC1->CR2 |= ADC_CR2_CAL; //Включение калибровки

		  while (!(ADC1->CR2 & ADC_CR2_CAL)); //Ожидаем окончания калибровки

		  ADC1->SMPR2 |= (ADC_SMPR2_SMP1_2 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_0); //Задаем
		 // длительность выборки

		  ADC1->CR2 |= ADC_CR2_JEXTSEL; //Преобразование инжектированной группы
		  //запустится установкой бита JSWSTART

		  ADC1->CR2 |= ADC_CR2_JEXTTRIG; //Разрешаем внешний запуск инжектированной группы
		  ADC1->CR2 |= ADC_CR2_CONT; //Разрешаем непрерывные преобразования

		  ADC1->CR1 |= ADC_CR1_JAUTO; //Разрешить преобразование инжектированной группы
		  //после регулярной. Не понятно зачем, но без этого не работает

		  ADC1->JSQR |= (1<<15); //Задаем номер канала (выбран ADC1)
		  ADC1->CR2 |= ADC_CR2_ADON;//Теперь включаем АЦП
		  ADC1->CR2 |= ADC_CR2_JSWSTART; //Запуск преобразований

		  while (!(ADC1->SR & ADC_SR_JEOC)); //ждем пока первое преобразование завершится

		  //Теперь можно читать результат из JDR1
		  uint32_t aza; //Использовал переменную для отладки. Можно и без неё
		  while(1)
		  {
		  aza=ADC1->JDR1;
		  delay(aza); //Делаем задержку, длительность которой зависит от величины aza
		  GPIOC->BSRR = GPIO_BSRR_BR8; //Гасим светодиод PC8
		  GPIOC->BSRR = GPIO_BSRR_BS9; // Зажигаем светодиод PC9
		  aza=ADC1->JDR1;
		  delay(aza); //Делаем задержку, длительность которой зависит от величины aza
		  GPIOC->BSRR = GPIO_BSRR_BR9; //Гасим светодиод PC9
		  GPIOC->BSRR = GPIO_BSRR_BS8; // Зажигаем светодиод PC8
		  }
}

void delay(uint32_t j)
{
	uint32_t i;
	for(i=0;i < j * 1000; ++i);
}

