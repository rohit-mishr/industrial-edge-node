#include <stdint.h>
#include "led.h"

void delay(volatile uint32_t count) {
    while(count--) {}
}


int main(void){
    led_init();
    while(1){
        led_toggle();
        delay(1000000);
    }
}
