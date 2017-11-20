#include "stm32f10x.h"
#define F_CPU 72000000UL



void USART1_IRQHandler(void)
{
	if (USART1->SR & USART_SR_RXNE)
	{
	USART1->DR = (USART1->DR)+1;
	}
}

void USART2_IRQHandler(void)
{
	if (USART2->SR & USART_SR_RXNE)
	{
	USART2->DR = (USART2->DR)+10;
	}
}

void USART3_IRQHandler(void)
{
	if (USART3->SR & USART_SR_RXNE)
	{
	USART3->DR = (USART3->DR)+100;
	}
}



int main(void)
{
SystemInit();

// PORT INIT
RCC->APB2ENR  |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN |	// GPIOA Clock ON. Alter function clock ON
		 RCC_APB2ENR_IOPBEN;				// GPIOB Clock ON


// USART1 Settings
// SET TX1
GPIOA->CRH	&= ~GPIO_CRH_CNF9;		// Clear CNF bit 9
GPIOA->CRH	|= GPIO_CRH_CNF9_1;		// Set CNF bit 9 to 10 - AFIO Push-Pull
GPIOA->CRH	|= GPIO_CRH_MODE9_0;		// Set MODE bit 9 to Mode 01 = 10MHz

// SET RX1
GPIOA->CRH	&= ~GPIO_CRH_CNF10;		// Clear CNF bit 9
GPIOA->CRH	|= GPIO_CRH_CNF10_0;		// Set CNF bit 9 to 01 HiZ
GPIOA->CRH	&= ~GPIO_CRH_MODE10;		// Set MODE bit 9 to Mode 01 = 10MHz

// SET USART1 REG
RCC->APB2ENR	|= RCC_APB2ENR_USART1EN;				// USART1 Clock ON
USART1->BRR 	= 0xEA6;						// Baudrate for 19200 on 72Mhz
USART1->CR1 	|= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE |		// USART1 ON, TX ON, RX ON
		     USART_CR1_RXNEIE;					// RXNE Int ON


// USART2 Settings
// SET TX2
GPIOA->CRL	&= ~GPIO_CRL_CNF2;	// Clear CNF bit 2
GPIOA->CRL	|= GPIO_CRL_CNF2_1;	// Set CNF bit 2 to 10 - AFIO Push-Pull
GPIOA->CRL	|= GPIO_CRL_MODE2_0;	// Set MODE bit 2 to Mode 01 = 10MHz

// SET RX2
GPIOA->CRL		&= ~GPIO_CRL_CNF3;	// Clear CNF bit 3
GPIOA->CRL		|= GPIO_CRL_CNF3_0;	// Set CNF bit 3 to 01 HiZ
GPIOA->CRL		&= ~GPIO_CRL_MODE3;	// Set MODE bit 3 to Mode 01 = 10MHz


// SET USART2 REG
RCC->APB1ENR	|= RCC_APB1ENR_USART2EN;				// USART2 Clock ON
USART2->BRR 	= 0x753;						// Baudrate for 19200 on 36Mhz
USART2->CR1 	|= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE |		// USART2 ON, TX ON, RX ON
		 USART_CR1_RXNEIE;


// USART3 Settings
// SET TX3
GPIOB->CRH	&= ~GPIO_CRH_CNF10;		// Clear CNF bit 9
GPIOB->CRH	|= GPIO_CRH_CNF10_1;		// Set CNF bit 9 to 10 - AFIO Push-Pull
GPIOB->CRH	|= GPIO_CRH_MODE10_0;		// Set MODE bit 9 to Mode 01 = 10MHz

// SET RX3
GPIOB->CRH	&= ~GPIO_CRH_CNF11;		// Clear CNF bit 9
GPIOB->CRH	|= GPIO_CRH_CNF11_0;		// Set CNF bit 9 to 01 HiZ
GPIOB->CRH	&= ~GPIO_CRH_MODE11;		// Set MODE bit 9 to Mode 01 = 10MHz


// SET USART3 REG
RCC->APB1ENR	|= RCC_APB1ENR_USART3EN;				// USART3 Clock ON
USART3->BRR 	= 0x753;						// Baudrate for 19200 on 36Mhz
USART3->CR1 	|= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE |		// USART3 ON, TX ON, RX ON
		    USART_CR1_RXNEIE;

//UART INT ON
NVIC_EnableIRQ (USART1_IRQn);
NVIC_EnableIRQ (USART2_IRQn);
NVIC_EnableIRQ (USART3_IRQn);

__enable_irq ();

 while(1)
	{
	}
}
