#ifndef CONFIG
#define CONFIG

#include <stdint.h>
// ==========================================
// SYSTEM & APPLICATION MACROS
// ==========================================
// We will assume the main application firmware is flashed starting at Sector 5
#define MAIN_APP_START_ADDRESS          0x08020000U
#define MAIN_APP_RESET_HANDLER_ADDRESS  (MAIN_APP_START_ADDRESS + 4U)
#define SCB_VTOR_ADDRESS                0xE000ED08

#endif