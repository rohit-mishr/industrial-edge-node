#ifndef GPIO
#define GPIO

#include <stdint.h>

#define MODER_X_OFFSET 0x00
#define AFRL_X_OFFSET 0x20
#define GPIOx_PUPDR_OFFSET 0x0C
#define GPIOx_IDR_OFFSET 0x10
#define GPIOx_ODR_offset 0x14

// ==========================================
// GPIOA (General Purpose I/O Port A)
// ==========================================
#define GPIOA_BASE                      0x40020000

#define MODER_A                         *(volatile uint32_t*)(GPIOA_BASE + MODER_X_OFFSET)
#define AFRL_A                          *(volatile uint32_t*)(GPIOA_BASE + AFRL_X_OFFSET)
#define GPIO_A_PUPDR                    *(volatile uint32_t*)(GPIOA_BASE + GPIOx_PUPDR_OFFSET)
#define GPIO_A_ODR                      *(volatile uint32_t*)(GPIOA_BASE + GPIOx_ODR_offset)


#define GPIOA_PIN2_MODER_POS            4U
#define GPIOA_PIN2_MODER_MSK            ~(3U << GPIOA_PIN2_MODER_POS)
#define GPIOA_PIN2_MODE_ALTFUNC         (2U << GPIOA_PIN2_MODER_POS) // Set PA2 to AF Mode

#define GPIOA_PIN3_MODER_POS            6U
#define GPIOA_PIN3_MODER_MSK            ~(3U << GPIOA_PIN3_MODER_POS)
#define GPIOA_PIN3_MODE_ALTFUNC         (2U << GPIOA_PIN3_MODER_POS) // Set PA3 to AF Mode

#define GPIOA_PIN5_MODER_POS             10U
#define GPIOA_PIN5_PUPDR_POS             10U
#define GPIOA_PIN5_MODER_MSK            ~(3U << GPIOA_PIN5_MODER_POS)
#define GPIOA_PIN5_MODE_OUTPUT          (1U << GPIOA_PIN5_MODER_POS) // Set PA5 to output Mode
#define GPIOA_PIN5_MODE_PULLDOWN        (2U << GPIOA_PIN5_PUPDR_POS) 
#define GPIOA_PIN5_PUPDR_MSK            ~(3U << GPIOA_PIN5_PUPDR_POS)
#define GPIO_A_ODR_PIN5_POS             5
#define GPIO_A_ODR_PIN5_SET             (1U << GPIO_A_ODR_PIN5_POS)
#define GPIO_A_ODR_PIN5_RESET           ~(1U << GPIO_A_ODR_PIN5_POS)

// GPIOA AFRL (Alternate Function Low) Macros 
// AF7 = USART2 Routing
#define GPIOA_PIN2_AFRL_POS             8U
#define GPIOA_PIN2_AFRL_MSK             ~(15U << GPIOA_PIN2_AFRL_POS)
#define GPIOA_PIN2_AF7_USART2_TX        (7U << GPIOA_PIN2_AFRL_POS)  // Route PA2 to USART2_TX

#define GPIOA_PIN3_AFRL_POS             12U
#define GPIOA_PIN3_AFRL_MSK             ~(15U << GPIOA_PIN3_AFRL_POS)
#define GPIOA_PIN3_AF7_USART2_RX        (7U << GPIOA_PIN3_AFRL_POS)  // Route PA3 to USART2_RX

// ==========================================
// GPIOC (General Purpose I/O Port C)
// ==========================================
#define GPIOC_BASE                      0x40020800
#define MODER_C                         *(volatile uint32_t*)(GPIOC_BASE + MODER_X_OFFSET)
#define GPIO_C_PUPDR                    *(volatile uint32_t*)(GPIOC_BASE + GPIOx_PUPDR_OFFSET)
#define GPIO_C_IDR                      *(volatile uint32_t*)(GPIOC_BASE + GPIOx_IDR_OFFSET)

#define GPIOC_PIN13_MODER_POS            26U
#define GPIOC_PIN13_MODER_MSK            ~(3U << GPIOC_PIN13_MODER_POS)
#define GPIOC_PIN13_PUPDR_POS            26U
#define GPIOC_PIN13_PUPDR_MSK            ~(3U << GPIOC_PIN13_PUPDR_POS)
#define GPIO_C_IDR_PIN13_POS             13
#define GPIO_C_IDR_PIN13                 ((GPIO_C_IDR >> GPIO_C_IDR_PIN13_POS)&(1U << 0))
#define GPIOC_PIN13_MODE_INPUT           (0U << GPIOC_PIN13_MODER_POS)
#define GPIOC_PIN13_MODE_PULLUP          (1U << GPIOC_PIN13_PUPDR_POS)

#endif