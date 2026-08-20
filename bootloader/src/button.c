#include <stdint.h>
#include "rcc.h"
#include "button.h"
#include "gpio.h"

#define BUTTON_STATE GPIO_C_IDR_PIN13

void button_init(void){
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    MODER_C &= GPIOC_PIN13_MODER_MSK;
    MODER_C |= GPIOC_PIN13_MODE_INPUT;
    GPIO_C_PUPDR &= GPIOC_PIN13_PUPDR_MSK;
    GPIO_C_PUPDR |= GPIOC_PIN13_MODE_PULLUP;
}

uint8_t get_button_state(void){
    if(BUTTON_STATE){
        return 0;
    }
    else{
        return 1;
    }
}
