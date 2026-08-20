#ifndef USART
#define USART
#include <stdint.h>

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

void bootloader_uart_init(void);
void usart_send_char(uint8_t data);
uint8_t usart_receive_char(void);

#endif