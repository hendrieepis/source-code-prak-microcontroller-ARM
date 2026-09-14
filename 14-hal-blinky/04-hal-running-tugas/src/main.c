#include "stm32f4xx_hal.h"

static const uint16_t leds[4] = {
    GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15
};

int main(void)
{
    HAL_Init();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef gpio = {0};
    gpio.Pin   = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &gpio);

    for (;;)
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            HAL_GPIO_WritePin(GPIOD,
                GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15,
                GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOD, leds[i], GPIO_PIN_SET);
            HAL_Delay(250);
        }
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
