#include <stdint.h>
#include "config.h"
#include "main.h"
#include "usart.h"


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