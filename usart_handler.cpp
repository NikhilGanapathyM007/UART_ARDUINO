#include "usart_handler.h"

// Define constants for USART
#define BAUD 2400
#define UBRR_VALUE ((F_CPU / (BAUD * 16UL)) - 1)

// Initializes the USART with specified baud rate for serial communication
void usart_init() {
    // Set baud rate in the USART Baud Rate Registers (UBRR)
    UBRR0H = (UBRR_VALUE >> 8); // Set high byte of UBRR
    UBRR0L = UBRR_VALUE;        // Set low byte of UBRR

    // Enable USART transmitter and receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

// Sends a single byte over USART
void usart_transmit(uint8_t data) {
  // Wait until data is available in the receive buffer
    while (!(UCSR0A & (1 << UDRE0))) {
        // Wait until the buffer is empty
    }
    // Return received data from the USART Data Register (UDR)
    UDR0 = data;
}

// Receives a single byte over USART
uint8_t usart_receive() {
    while (!(UCSR0A & (1 << RXC0))) {
        // Wait until data is received
    }
    return UDR0;
}
