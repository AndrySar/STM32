/*
Проект ипользованиея шима таймера. Уровень напряжения на выходе
ноги PA1 задается элементами массива mass. Шим настроен в прямом
режиме.
 */
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void delay(void);

int main()
{

  RCC-> APB2ENR |= RCC_APB2ENR_IOPAEN; //Тактируем порт A
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;//Тактирование таймера TIM2

   GPIOA->CRL |= GPIO_CRL_MODE1_1;//Максимальная скорость порта  2 MHz
   GPIOA->CRL &= ~GPIO_CRL_CNF1;//Очистка бит CNF[1:0] для PA1 (поскольку после сброса мк задан режим "Input Floating")
   GPIOA->CRL |= GPIO_CRL_CNF1_1; //PA1 - выход Push-Pull в режиме альтернативной функции

  TIM2->CCER |= TIM_CCER_CC2E; //Разрешаем таймеру использовать ногу PA1 для ШИМа
  TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1); //Задаем прямой шим
  //Запуск таймера
  TIM2->CR1 |= TIM_CR1_CEN;
  //После этого пишем данные в TIM2->CCRx - и яркость светодиодов меняется

  uint32_t mass[]={0,0,6553,13107,19660,26214,32768,
                                  39321,45875,52428,58982,65535};

  uint8_t i;
  while(1)
  {
    for (i=1;i<=11;i++) {
        TIM2->CCR2=mass[i];
        delay();
    }
  }
}

void delay(void) {
  volatile uint32_t i;
    for (i=1; i != 0xF000; i++);
  }
