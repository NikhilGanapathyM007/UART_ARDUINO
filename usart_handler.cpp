#include "usart_handler.h"

// Define constants for USART
#define BAUD 2400
#define UBRR_VALUE ((F_CPU / (BAUD * 16UL)) - 1)

void usart_init() {
    // Set baud rate
    UBRR0H = (UBRR_VALUE >> 8);
    UBRR0L = UBRR_VALUE;

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void usart_transmit(uint8_t data) {
    while (!(UCSR0A & (1 << UDRE0))) {
        // Wait until the buffer is empty
    }
    UDR0 = data;
}

uint8_t usart_receive() {
    while (!(UCSR0A & (1 << RXC0))) {
        // Wait until data is received
    }
    return UDR0;
}
