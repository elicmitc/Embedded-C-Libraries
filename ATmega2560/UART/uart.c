#include "uart.h"

/* Initialize the UART with baud rate */
void uart_init(uint32_t baud_rate){
	/* ubrr: USART Baud Rate Register Value as a 16-bit uint
	 * F_CPU: The system clock frequency (16 MHz for ATmega2560)
	 * baud_rate: Desired communication speed (9600, 115200, ...)
	 * UBRR0H: UART Baud Rate Register 0 High
	 * UBRR0L: UART Baud Rate Register 0 Low
	 * UCSR0B: USART Control and Status Register 0 B (controls transmit/receive)
	 * UCSR0C: USART Control and Status Register 0 C (controls data frame format)
	 * UCSZ00/01/02: USART Control and Data Frame Size Bits
	 * TXEN0: Transmit enable bit 
	 * RXEN0: Receive enable bit 
	 * 
	 * Forumula calculates desired values to set UBRR0H and UBRR0L.
	 */ 
/* Calculate the UBRR */
	uint16_t ubrr = (F_CPU / 16 / baud_rate - 1);
/* Set the Baud Rate */
	/* Capture the high byte of ubrr into UBRR0H */
	UBRR0H = (unsigned char) (ubrr >> 8);
	/* Capture the low byte of ubrr into UBRR0L */
	UBRR0L = (unsigned char) ubrr;
/* Enable transmitter and receiver */
	/* Enable the trasmiter and receiver */
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
/* Set frame format: 8 data bits, 1 stop bit)
	/* Set frame format (data size, stop bits, parity)  to 8 bits */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

/* Transmit each character (byte) in string over TX line */
void uart_transmit(unsigned char data){
	/* When the USART Data Register 0 is empty, write the data (byte)
	 * to the UDR0.
	 */
/* Wait for the trasmit buffer to be empty */
	while(!(UCSR0A & (1 << UDRE0))); // UCSR0A: USART Control and Status Register 0A
					 // UDRE0: USART Data Register 0 Empty bit index
	/* UDR0, when filled with data, moves the data to the transmit shift register and 
	 * the UDREO index in UCSR0A is set to busy (0) indicating data is being sent.
	 * After transmition and the shift register is empty, the UDREO flag is set to accept
	 * new data (1).
	 */
/* Put data into the buffer, sends data */
	UDR0 = data; // USART Data Register

/* Send each character in string to transmit */
void uart_print(const char* str){
	while(*str) {
		uart_transmit(*str++);
	}
}
