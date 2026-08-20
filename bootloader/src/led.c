#include "led.h"
#include "gpio.h"
#include "rcc.h"

void led_init(void){
     // Enable the clock for GPIOA (AHB1 Bus)
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    MODER_A &= GPIOA_PIN5_MODER_MSK;
    MODER_A |= GPIOA_PIN5_MODE_OUTPUT;
    GPIO_A_PUPDR &= GPIOA_PIN5_PUPDR_MSK;
    GPIO_A_PUPDR |= GPIOA_PIN5_MODE_PULLDOWN;
    led_off();
}