#include "eeprom_handler.h"

void eeprom_write(uint16_t address, uint8_t data) {
    // Wait for completion of any previous write operation
    while (EECR & (1 << EEPE));

    // Disable global interrupts to ensure atomic write operation
    uint8_t sreg = SREG; // Store SREG value
    cli();               // Disable interrupts

    // Set up address and data
    EEARH = (address >> 8);    // High byte
    EEARL = (address & 0xFF);  // Low byte
    EEDR = data;

    // Start EEPROM write by setting EEMPE and then EEPE
    EECR |= (1 << EEMPE);  // Enable EEPROM master write
    EECR |= (1 << EEPE);   // Start EEPROM write

    SREG = sreg; // Restore SREG value to re-enable interrupts
}

uint8_t eeprom_read(uint16_t address) {
    // Wait for completion of any previous write operation
    while (EECR & (1 << EEPE));

    // Set up address in EEAR register
    EEARH = (address >> 8);    // High byte
    EEARL = (address & 0xFF);  // Low byte

    // Start EEPROM read by setting EERE
    EECR |= (1 << EERE);

    // Return data from Data Register
    return EEDR;
}
