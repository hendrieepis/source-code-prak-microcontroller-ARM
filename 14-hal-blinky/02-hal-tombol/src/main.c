#include "stm32f4xx_hal.h"

static void led_init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin   = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Pull  = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &gpio);
}

static void button_init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {0};
    gpio.Pin  = GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);
}

int main(void)
{
    uint32_t last = 0;

    HAL_Init();
    led_init();
    button_init();

    for (;;)
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
            if ((HAL_GetTick() - last) > 50U)   /* debounce 50 ms */
            {
                last = HAL_GetTick();
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
            }
        }
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
