#ifndef USART_HANDLER_H
#define USART_HANDLER_H

#include <avr/io.h>

// USART operations
void usart_init();      // Initializes USART for serial communication
void usart_transmit(uint8_t data);  // Sends a single byte over USART
uint8_t usart_receive();    // Receives a single byte over USART

#endif // USART_HANDLER_H
