#include <stdint.h>
#include "flash.h"

void flash_flush(void){
    flash_prefetch_disable();
    flash_I_cache_flush();
    flash_D_cache_flush();
}

void flash_write(uint32_t address, uint32_t data){
    while(FLASH_SR_BSY);
    FLASH_CR |= FLASH_CR_PG_SET;
    *((volatile uint32_t*)(address)) = data;
    while(FLASH_SR_BSY);
    FLASH_CR &= FLASH_CR_PG_RESET;
}

void flash_erase_sector(uint8_t sector_num){
    while(FLASH_SR_BSY);
    FLASH_CR |= FLASH_CR_SER_SET;
    FLASH_CR &= FLASH_CR_MER_RESET;
    FLASH_CR &= FLASH_CR_SNB_MSK;
    FLASH_CR |= (sector_num << FLASH_CR_SNB_POS);
    FLASH_CR |= FLASH_CR_STRT_SET;
    while(FLASH_SR_BSY);
    FLASH_CR &= FLASH_CR_SER_RESET;
}