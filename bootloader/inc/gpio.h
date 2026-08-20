#ifndef GPIO
#define GPIO

#include <stdint.h>

// ==========================================
// GPIOA (General Purpose I/O Port A)
// ==========================================
#define GPIOA_BASE                      0x40020000
#define MODER_A                         *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define AFRL_A                          *(volatile uint32_t*)(GPIOA_BASE + 0x20)


#define GPIOA_PIN2_MODER_POS            4U
#define GPIOA_PIN2_MODER_MSK            (3U << GPIOA_PIN2_MODER_POS)
#define GPIOA_PIN2_MODE_ALTFUNC         (2U << GPIOA_PIN2_MODER_POS) // Set PA2 to AF Mode

#define GPIOA_PIN3_MODER_POS            6U
#define GPIOA_PIN3_MODER_MSK            (3U << GPIOA_PIN3_MODER_POS)
#define GPIOA_PIN3_MODE_ALTFUNC         (2U << GPIOA_PIN3_MODER_POS) // Set PA3 to AF Mode

// GPIOA AFRL (Alternate Function Low) Macros 
// AF7 = USART2 Routing
#define GPIOA_PIN2_AFRL_POS             8U
#define GPIOA_PIN2_AFRL_MSK             (15U << GPIOA_PIN2_AFRL_POS)
#define GPIOA_PIN2_AF7_USART2_TX        (7U << GPIOA_PIN2_AFRL_POS)  // Route PA2 to USART2_TX

#define GPIOA_PIN3_AFRL_POS             12U
#define GPIOA_PIN3_AFRL_MSK             (15U << GPIOA_PIN3_AFRL_POS)
#define GPIOA_PIN3_AF7_USART2_RX        (7U << GPIOA_PIN3_AFRL_POS)  // Route PA3 to USART2_RX

#endif