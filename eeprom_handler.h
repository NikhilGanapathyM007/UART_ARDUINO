#ifndef EEPROM_HANDLER_H
#define EEPROM_HANDLER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// EEPROM operations
void eeprom_write(uint16_t address, uint8_t data); // Writes a byte to a specified EEPROM address
uint8_t eeprom_read(uint16_t address); // Reads a byte from a specified EEPROM address

#endif // EEPROM_HANDLER_H
