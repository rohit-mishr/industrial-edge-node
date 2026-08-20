#ifndef LED
#define LED

#include "gpio.h"

#define LED_STATE GPIO_A_ODR_PIN5

__attribute__((always_inline)) static inline void led_on(void){
    GPIO_A_ODR |= GPIO_A_ODR_PIN5_SET;
}

__attribute__((always_inline)) static inline void led_off(void){
    GPIO_A_ODR &= GPIO_A_ODR_PIN5_RESET;
}

__attribute__((always_inline)) static inline void led_toggle(void){
    GPIO_A_ODR ^= GPIO_A_ODR_PIN5_SET;
}

__attribute__((always_inline)) static inline uint8_t get_led_state(void){
    return (uint8_t)LED_STATE;
}

void led_init(void);

#endif