#include <stdint.h>
#include "main.h"
#include "config.h"
#include "usart.h"
#include "button.h"
#include "flash.h"
#include "led.h"


void delay(volatile uint32_t count) {
    while(count--) {}
}

int main(void) {
    // 1. TODO: Initialize Clocks and UART
    bootloader_uart_init();
    button_init();
    led_init();

    // check for button press
    uint32_t i = 0;
    while (get_button_state() && i < 500000) { 
        i++; 
    }
    
    // 3. Evaluate the result
    if (i < 500000) {
        // Button was NOT held long enough (or not pressed at all)
        while(1) {
            char *s = "Not in bootloader mode\r\n";
            int j = 0;
            while (s[j] != '\0') {
                usart_send_char(s[j++]); // (Assuming your TX function is named uart_tx)
            }
            delay(1000000); // Wait a bit before printing again
        }
    }
    
    // 4. Bootloader Mode (Button was held)
    led_on();
    while(1) {
        char *s = "In bootloader mode\r\n";
        int j = 0;
        while (s[j] != '\0') {
            usart_send_char(s[j++]);
        }
        delay(1000000); // Wait a bit before printing again
    }
    
    
    
    // 2. TODO: Check if the user is requesting a firmware update
    
    // 3. TODO: De-initialize clocks and UART before jumping

    // jump_to_application();
    
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