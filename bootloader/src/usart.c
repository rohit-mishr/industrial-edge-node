#include <stdint.h>
#include "gpio.h"
#include "rcc.h"
#include "usart.h"


void bootloader_uart_init(void) {
    // ==========================================
    // STEP 1: ENABLE CLOCKS
    // ==========================================
    
    // Enable the clock for GPIOA (AHB1 Bus)
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    // Enable the clock for USART2 (APB1 Bus)
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;
    
    // ==========================================
    // STEP 2: CONFIGURE GPIO 
    // ==========================================
    MODER_A &= (GPIOA_PIN2_MODER_MSK & GPIOA_PIN3_MODER_MSK);
    AFRL_A &=  (GPIOA_PIN2_AFRL_MSK & GPIOA_PIN3_AFRL_MSK);
    
    MODER_A |= (GPIOA_PIN2_MODE_ALTFUNC | GPIOA_PIN3_MODE_ALTFUNC);
    AFRL_A |= (GPIOA_PIN2_AF7_USART2_TX | GPIOA_PIN3_AF7_USART2_RX);
    
    // ==========================================
    // STEP 3: CONFIGURE USART2
    // ==========================================
    // Setting baudrate 
    USART_BRR = USART_BRR_115200;

    // Setting the enable bits
    USART_CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}

void usart_send_char(uint8_t data) {
    // 1. Wait for TXE to be 1
    // 2. Write 'data' to USART_DR
    while(!TXE);
    USART_DR = data;
}

uint8_t usart_receive_char(void) {
    // 1. Wait for RXNE to be 1
    // 2. Return the masked value in USART_DR
    while(!RXNE);
    return (uint8_t)(USART_DR & USART_DR_DATA_MSK);
}
