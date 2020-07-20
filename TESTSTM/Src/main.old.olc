#include <stm32f4xx_hal.h>
#include <stm32_hal_legacy.h>
 
#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
 
static UART_HandleTypeDef s_UARTHandle = UART_HandleTypeDef();
 
int main(void)
{
    HAL_Init();
 
    __USART2_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStructure;
 
    GPIO_InitStructure.Pin = GPIO_PIN_2;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Alternate = GPIO_AF7_USART2;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    s_UARTHandle.Instance        = USART2;
    s_UARTHandle.Init.BaudRate   = 115200;
    s_UARTHandle.Init.WordLength = UART_WORDLENGTH_8B;
    s_UARTHandle.Init.StopBits   = UART_STOPBITS_1;
    s_UARTHandle.Init.Parity     = UART_PARITY_NONE;
    s_UARTHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    s_UARTHandle.Init.Mode       = UART_MODE_TX_RX;
    
    if (HAL_UART_Init(&s_UARTHandle) != HAL_OK)
        asm("bkpt 255");
    
    for (;;)
    {
        uint8_t buffer[4];
        HAL_UART_Receive(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
        HAL_UART_Transmit(&s_UARTHandle, buffer, sizeof(buffer), HAL_MAX_DELAY);
    }
}
