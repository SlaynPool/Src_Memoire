#include "stm32f4_discovery.h"
/**************************************************************************************/
void RCC_Configuration(void)
{
/* --------------------------- System Clocks Configuration -----------------*/
/* USART3 clock enable */
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
/* GPIOB clock enable */
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
}
/**************************************************************************************/
void GPIO_Configuration(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/*-------------------------- GPIO Configuration ----------------------------*/
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOB, &GPIO_InitStructure);
/* Connect USART pins to AF */
GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
}
/**************************************************************************************/
void USART3_Configuration(void)
{
USART_InitTypeDef USART_InitStructure;
/* USARTx configuration ------------------------------------------------------*/
/* USARTx configured as follow:
- BaudRate = 9600 baud
- Word Length = 8 Bits
- Two Stop Bit
- Odd parity
- Hardware flow control disabled (RTS and CTS signals)
- Receive and transmit enabled
*/
USART_InitStructure.USART_BaudRate = 9600;
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
USART_InitStructure.USART_StopBits = USART_StopBits_1;
USART_InitStructure.USART_Parity = USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART3, &USART_InitStructure);
USART_Cmd(USART3, ENABLE);
}
/**************************************************************************************/
int main(void)
{
RCC_Configuration();
GPIO_Configuration();
USART3_Configuration();
while(1)
{
uint16_t Data;
while(USART_GetITStatus(USART3, USART_IT_RXNE) == RESET); // Wait for Char
Data = USART_ReceiveData(USART3); // Collect Char
while(USART_GetITStatus(USART3, USART_IT_TXE) == RESET); // Wait for Empty
USART_SendData(USART3, Data); // Echo Char
}
while(1); // Don't want to exit
}
