#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Purpose: Blink build in LED on Mega 2560 
int main() {
  // Set PIN-13 (PB7) to output (1)
  DDRB |= (1 << PB7); // Data Direction Register B - Sets pin to input(0)/output(1)
  while(1){
    // Set PIN-13 to HIGH (1)
    PORTB |= (1 << PB7); // Port B Data Register - Sets pin output low(0)/high(1) 
    // Delay 1 second
    _delay_ms(250);
    // Set PIN-13 to LOW (0)
    PORTB &= ~(1 << PB7); // Port B Data Register - Sets pin output low(0)/high(1) 
    _delay_ms(1000);
  }
  return 0;
}
