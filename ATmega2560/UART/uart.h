#ifndef UART_H // if uart.h is not defined
#define UART_H

#include <avr/io.h>
#include <stdio.h>
// Functions in uart.h
void uart_init(uint32_t baud_rate);
void uart_transmit(unsigned char data);
void uart_print(const char* str);

#endif // end definition
