#include "rcc.h"
#include "button.h"
#include "gpio.h"

void button_init(void){
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    MODER_C &= GPIOC_PIN13_MODER_MSK;
    MODER_C |= GPIOC_PIN13_MODE_INPUT;
    GPIO_C_PUPDR &= GPIOC_PIN13_PUPDR_MSK;
    GPIO_C_PUPDR |= GPIOC_PIN13_MODE_PULLUP;
}

