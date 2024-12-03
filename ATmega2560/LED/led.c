#include "led.h"

void transmit_data(u_int32_t data, u_int8_t pin, u_int16_t led_count){
    DDRB |= (1 << pin); // Data Direction Register B - Sets pin to input(0)/output(1)


}
