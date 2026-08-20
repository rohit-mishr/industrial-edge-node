#ifndef RCC
#define RCC

#include <stdint.h>
// ==========================================
// RCC (Reset and Clock Control)
// ==========================================
#define RCC_BASE                        0x40023800
#define RCC_AHB1ENR                     *(volatile uint32_t*)(RCC_BASE + 0x30)
#define RCC_APB1ENR                     *(volatile uint32_t*)(RCC_BASE + 0x40)

// RCC Bitmasks
#define RCC_AHB1ENR_GPIOAEN             (1U << 0)   // Enable GPIOA clock
#define RCC_APB1ENR_USART2EN            (1U << 17)  // Enable USART2 clock

#endif