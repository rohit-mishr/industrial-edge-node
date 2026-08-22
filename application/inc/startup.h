#ifndef STARTUP_H
#define STARTUP_H

#include <stdint.h>

// ==========================================
// LINKER SCRIPT SYMBOLS
// ==========================================
extern uint32_t _estack;  // Top of the stack
extern uint32_t _sidata;  // Start of initialization values in Flash (MISSING ADDITION)
extern uint32_t _sdata;   // Start of initialized data section (.data) in RAM
extern uint32_t _edata;   // End of initialized data section
extern uint32_t _sbss;    // Start of uninitialized data section (.bss)
extern uint32_t _ebss;    // End of uninitialized data section

// ==========================================
// CORE SYSTEM HANDLERS
// ==========================================
void Reset_Handler(void);

// Tell startup.c that main exists elsewhere
extern int main(void);

#endif // STARTUP_H