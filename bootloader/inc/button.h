#ifndef BUTTON
#define BUTTON
#include <stdint.h>
#include "gpio.h"

#define BUTTON_STATE GPIO_C_IDR_PIN13

__attribute__((always_inline)) static inline uint8_t get_button_state(void){
    return (uint8_t)(!(BUTTON_STATE));
}

void button_init(void);

#endif