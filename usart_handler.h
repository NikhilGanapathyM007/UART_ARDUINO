#ifndef USART_HANDLER_H
#define USART_HANDLER_H

#include <avr/io.h>

// USART operations
void usart_init();
void usart_transmit(uint8_t data);
uint8_t usart_receive();

#endif // USART_HANDLER_H
