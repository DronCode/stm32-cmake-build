#include "stm32f1xx_hal.h"	//TODO: Remove it (don't include HAL sources in user-space)
#include "HAL/Core.h"

static void MX_GPIO_Init(); //TODO: Remove it

int main()
{
    hal::Core::GetInstance().Initialize();

    MX_GPIO_Init();	//TODO: Remove it

    while (true) {
        HAL_Delay(50);	//TODO: Use HAL
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); //TODO: Use HAL
    }
}

static void MX_GPIO_Init(void)	//TODO: Remove it
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}