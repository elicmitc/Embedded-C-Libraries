#ifndef LED_H
#define LED_H

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

// FUNCTION: transmit_data(r, g, b)
void transmit_data(u_int32_t data, u_int8_t pin, u_int16_t led_count)
// turn on PB5 as output 
// read through data to transmit
    // send representative signal for 1 and 0 with correct timing

// FUNCTION: (leds, r, g, b, pin) use digital pin 11 (pwm) PB5 
void leds(u_int16_t led_count, u_int8_t g, u_int8_t r, u_int8_t b, u_int8_t pin);
// convert Green to 8 bit array
// convert Red to 8 bit array
// convert Blue to 8 bit array
// transmit data



#endif