#ifndef FLASH_DRIVER_H
#define FLASH_DRIVER_H

#include <stdint.h>

/* ========================================================================== */
/*                      1. BASE ADDRESSES & OFFSETS                           */
/* ========================================================================== */
#define FLASH_INTERFACE_BASE_ADDR 0x40023C00U

#define FLASH_ACR_OFFSET  0x00
#define FLASH_KEYR_OFFSET 0x04
#define FLASH_SR_OFFSET   0x0C
#define FLASH_CR_OFFSET   0x10

/* ========================================================================== */
/*                      2. REGISTER DEFINITIONS                               */
/* ========================================================================== */
#define FLASH_ACR  *((volatile uint32_t*)(FLASH_INTERFACE_BASE_ADDR + FLASH_ACR_OFFSET))
#define FLASH_KEYR *((volatile uint32_t*)(FLASH_INTERFACE_BASE_ADDR + FLASH_KEYR_OFFSET))
#define FLASH_SR   *((volatile uint32_t*)(FLASH_INTERFACE_BASE_ADDR + FLASH_SR_OFFSET))
#define FLASH_CR   *((volatile uint32_t*)(FLASH_INTERFACE_BASE_ADDR + FLASH_CR_OFFSET))

/* ========================================================================== */
/*                      3. FLASH UNLOCK KEYS                                  */
/* ========================================================================== */
#define FLASH_KEY1 0x45670123U
#define FLASH_KEY2 0xCDEF89ABU

/* ========================================================================== */
/*                      4. REGISTER BIT MASKS & POSITIONS                     */
/* ========================================================================== */

/* --- FLASH_ACR (Access Control Register) --- */
#define FLASH_ACR_PRFTEN_POS  8
#define FLASH_ACR_ICEN_POS    9
#define FLASH_ACR_DCEN_POS    10
#define FLASH_ACR_ICRST_POS   11
#define FLASH_ACR_DCRST_POS   12

/* Single-bit Action Masks (Used to SET the bits) */
#define FLASH_ACR_PRFTEN_SET  (1U << FLASH_ACR_PRFTEN_POS)
#define FLASH_ACR_ICEN_SET    (1U << FLASH_ACR_ICEN_POS)
#define FLASH_ACR_DCEN_SET    (1U << FLASH_ACR_DCEN_POS)
#define FLASH_ACR_ICRST_SET   (1U << FLASH_ACR_ICRST_POS)
#define FLASH_ACR_DCRST_SET   (1U << FLASH_ACR_DCRST_POS)

#define FLASH_ACR_PRFTEN_RESET ~(1U << FLASH_ACR_PRFTEN_POS)
#define FLASH_ACR_ICEN_RESET   ~(1U << FLASH_ACR_ICEN_POS)
#define FLASH_ACR_DCEN_RESET   ~(1U << FLASH_ACR_DCEN_POS)
#define FLASH_ACR_ICRST_RESET   ~(1U << FLASH_ACR_ICRST_POS)
#define FLASH_ACR_DCRST_RESET   ~(1U << FLASH_ACR_DCRST_POS)

/* --- FLASH_SR (Status Register) --- */
#define FLASH_SR_BSY_POS  16
/* Single-bit Read Mask (Used to check the status flag) */
#define FLASH_SR_BSY  ((FLASH_SR >> FLASH_SR_BSY_POS)&(1U<<0))

/* --- FLASH_CR (Control Register) --- */
#define FLASH_CR_PG_POS     0
#define FLASH_CR_SER_POS    1
#define FLASH_CR_MER_POS    2
#define FLASH_CR_SNB_POS    3
#define FLASH_CR_PSIZE_POS  8
#define FLASH_CR_STRT_POS   16
#define FLASH_CR_LOCK_POS   31

/* Single-bit Action Masks (Used to SET the bits) */
#define FLASH_CR_PG_SET     (1U << FLASH_CR_PG_POS)
#define FLASH_CR_SER_SET    (1U << FLASH_CR_SER_POS)
#define FLASH_CR_STRT_SET   (1U << FLASH_CR_STRT_POS)
#define FLASH_CR_LOCK_SET   (1U << FLASH_CR_LOCK_POS)

#define FLASH_CR_SER_RESET    ~(1U << FLASH_CR_SER_POS)
#define FLASH_CR_MER_RESET    ~(1U << FLASH_CR_MER_POS)
#define FLASH_CR_PG_RESET    ~(1U << FLASH_CR_PG_POS)

#define FLASH_CR_LOCK ((FLASH_CR >> FLASH_CR_LOCK_POS)&(1U<<0))

/* Sector Number (SNB) Configuration [Bits 6:3] */
#define FLASH_CR_SNB_MSK    (~(0x0FU << FLASH_CR_SNB_POS)) // Mask to clear SNB bits
#define FLASH_CR_SNB_SEC_2  (2U   << FLASH_CR_SNB_POS)     // Value to select Sector 2
#define FLASH_CR_SNB_SEC_5  (5U << FLASH_CR_SNB_POS) // Value to select Sector 5
#define FLASH_CR_SNB_SEC_6  (6U << FLASH_CR_SNB_POS) // Value to select Sector 6

/* Program Size (PSIZE) Configuration [Bits 9:8] */
#define FLASH_CR_PSIZE_MSK  (~(3U << FLASH_CR_PSIZE_POS))  // Mask to clear PSIZE bits
#define FLASH_CR_PSIZE_32   (2U   << FLASH_CR_PSIZE_POS)   // Value for x32 parallelism

// functions 
// disbaling the prefetch clearns the queue automatically
__attribute__((always_inline)) static inline void flash_prefetch_disable(void) {
    // Implementation here
    FLASH_ACR &= FLASH_ACR_PRFTEN_RESET;
}

__attribute__((always_inline)) static inline void flash_I_cache_flush(void) {
    // Implementation here
    FLASH_ACR &= FLASH_ACR_ICEN_RESET; 
    FLASH_ACR |= FLASH_ACR_ICRST_SET;
    FLASH_ACR &= FLASH_ACR_ICRST_RESET;
}

__attribute__((always_inline)) static inline void flash_D_cache_flush(void) {
    // Implementation here
    FLASH_ACR &= FLASH_ACR_DCEN_RESET;
    FLASH_ACR |= FLASH_ACR_DCRST_SET;
    FLASH_ACR &= FLASH_ACR_DCRST_RESET;
}

__attribute__((always_inline)) static inline void flash_lock(void){
    FLASH_CR |= FLASH_CR_LOCK_SET;
}
__attribute__((always_inline)) static inline void flash_unlock(void){
    if(FLASH_CR_LOCK){
        FLASH_KEYR = FLASH_KEY1;
        FLASH_KEYR = FLASH_KEY2;
    }
}
__attribute__((always_inline)) static inline void flash_set_psize_x32(void){
    FLASH_CR &= FLASH_CR_PSIZE_MSK;
    FLASH_CR |= FLASH_CR_PSIZE_32;
}

void flash_flush(void);
void flash_write(uint32_t address, uint32_t data);
void flash_erase_sector(uint8_t sector_num);

#endif // FLASH_DRIVER_H