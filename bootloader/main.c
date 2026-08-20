#include <stdint.h>

// ==========================================
// SYSTEM & APPLICATION MACROS
// ==========================================
// We will assume the main application firmware is flashed starting at Sector 2
#define MAIN_APP_START_ADDRESS          0x08008000
#define MAIN_APP_RESET_HANDLER_ADDRESS  (MAIN_APP_START_ADDRESS + 4U)
#define SCB_VTOR_ADDRESS                0xE000ED08

// ==========================================
// RCC (Reset and Clock Control)
// ==========================================
#define RCC_BASE                        0x40023800
#define RCC_AHB1ENR                     *(volatile uint32_t*)(RCC_BASE + 0x30)
#define RCC_APB1ENR                     *(volatile uint32_t*)(RCC_BASE + 0x40)

// RCC Bitmasks
#define RCC_AHB1ENR_GPIOAEN             (1U << 0)   // Enable GPIOA clock
#define RCC_APB1ENR_USART2EN            (1U << 17)  // Enable USART2 clock

// ==========================================
// GPIOA (General Purpose I/O Port A)
// ==========================================
#define GPIOA_BASE                      0x40020000
#define MODER_A                         *(volatile uint32_t*)(GPIOA_BASE + 0x00)
#define AFRL_A                          *(volatile uint32_t*)(GPIOA_BASE + 0x20)

// GPIOA MODER (Mode Register) Macros 
// Mode 2 = Alternate Function (AF)
#define GPIOA_PIN2_MODER_POS            4U
#define GPIOA_PIN2_MODER_MSK            (3UL << GPIOA_PIN2_MODER_POS)
#define GPIOA_PIN2_MODE_ALTFUNC         (2UL << GPIOA_PIN2_MODER_POS) // Set PA2 to AF Mode

#define GPIOA_PIN3_MODER_POS            6U
#define GPIOA_PIN3_MODER_MSK            (3UL << GPIOA_PIN3_MODER_POS)
#define GPIOA_PIN3_MODE_ALTFUNC         (2UL << GPIOA_PIN3_MODER_POS) // Set PA3 to AF Mode

// GPIOA AFRL (Alternate Function Low) Macros 
// AF7 = USART2 Routing
#define GPIOA_PIN2_AFRL_POS             8U
#define GPIOA_PIN2_AFRL_MSK             (15UL << GPIOA_PIN2_AFRL_POS)
#define GPIOA_PIN2_AF7_USART2_TX        (7UL << GPIOA_PIN2_AFRL_POS)  // Route PA2 to USART2_TX

#define GPIOA_PIN3_AFRL_POS             12U
#define GPIOA_PIN3_AFRL_MSK             (15UL << GPIOA_PIN3_AFRL_POS)
#define GPIOA_PIN3_AF7_USART2_RX        (7UL << GPIOA_PIN3_AFRL_POS)  // Route PA3 to USART2_RX

// ==========================================
// USART2
// ==========================================
#define USART2_BASE                     0x40004400
#define USART_SR                        *(volatile uint32_t*)(USART2_BASE + 0x00) 
#define USART_DR                        *(volatile uint32_t*)(USART2_BASE + 0x04)
#define USART_BRR                       *(volatile uint32_t*)(USART2_BASE + 0x08)
#define USART_CR1                       *(volatile uint32_t*)(USART2_BASE + 0x0C)

// USART Status Extraction Macros
#define TXE                             ((USART_SR >> 7) & (1U << 0))
#define RXNE                            ((USART_SR >> 5) & (1U << 0))

// USART Settings & Bitmasks
#define USART_BRR_115200                0x008BU     // Assuming 16 MHz clock and 115200 Baud Rate
#define USART_DR_DATA_MSK               0xFFU       // 8-bit data mask for DR register

#define USART_CR1_UE                    (1U << 13)  // USART Enable
#define USART_CR1_TE                    (1U << 3)   // Transmitter Enable
#define USART_CR1_RE                    (1U << 2)   // Receiver Enable


// ==========================================
// FUNCTIONS
// ==========================================

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
    MODER_A &= ~(GPIOA_PIN2_MODER_MSK | GPIOA_PIN3_MODER_MSK);
    AFRL_A &= ~(GPIOA_PIN2_AFRL_MSK | GPIOA_PIN3_AFRL_MSK);
    
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

void jump_to_application(void) {
    // Step A: Read the main application's Stack Pointer
    uint32_t app_msp_value = *(volatile uint32_t*)MAIN_APP_START_ADDRESS;
    
    // Step B: Read the main application's Reset Handler
    uint32_t app_jump_address = *(volatile uint32_t*)MAIN_APP_RESET_HANDLER_ADDRESS;
    
    // Step C: Cast to a C function pointer
    void (*app_reset_handler)(void) = (void (*)(void))app_jump_address;
    
    // Step D: Set the VTOR to the main app's address
    *(volatile uint32_t*)SCB_VTOR_ADDRESS = MAIN_APP_START_ADDRESS;
    
    // Step E: Physically set the ARM CPU's Main Stack Pointer (MSP)
    __asm volatile("msr msp, %0" : : "r" (app_msp_value));

    // Step F: Jump! 
    app_reset_handler();
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

int main(void) {
    // 1. TODO: Initialize Clocks and UART
    // bootloader_uart_init();
    
    // 2. TODO: Check if the user is requesting a firmware update
    
    // 3. TODO: De-initialize clocks and UART before jumping
    
    // 4. Jump to the main application
    // Temporary Hardware Test Loop
    jump_to_application();
    
    // The CPU has left the bootloader. It will never reach this while loop.
    while (1) {
    }
    
    return 0;
}