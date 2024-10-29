#include <avr/io.h>
#include <avr/interrupt.h>
#include "eeprom_handler.h"
#include "usart_handler.h"

// Define constants
#define EEPROM_SIZE 1024  // Maximum size of the EEPROM
#define DATA_SIZE 1000  // Target number of bytes to receive before sending

// Global variables for write/read indexes and flags
volatile uint16_t writeIndex = 0; // Index for writing to EEPROM
volatile uint16_t readIndex = 0;  // Index for reading from EEPROM
volatile bool dataReceived = false; // Flag indicating if data reception is complete

// Receives data via USART and stores it in EEPROM
void receive_data() {
    if (!dataReceived) {
        uint8_t incomingByte = usart_receive(); // Receive a byte from USART

        // Store the received byte in EEPROM if there's space
        if (writeIndex < EEPROM_SIZE) {
            eeprom_write(writeIndex++, incomingByte);
        }

        // Check if we have received the target number of bytes (1000)
        if (writeIndex >= DATA_SIZE) {
            dataReceived = true;
        }
    }
}

// Sends data from EEPROM to serial once reception is complete
void send_data() {
    if (dataReceived) {
      // Loop through EEPROM data and send it via USART
        while (readIndex < writeIndex) {
            uint8_t outByte = eeprom_read(readIndex++); // Read a byte from EEPROM
            usart_transmit(outByte);                    // Transmit the byte over USART

            // Small delay loop for smoother transmission, replace with proper delay if needed
            for (volatile int i = 0; i < 1000; i++) {
                asm("");
            }
        }

        // Reset indexes and dataReceived flag after transmission
        writeIndex = 0;     // Reset write index
        readIndex = 0;      // Reset read index
        dataReceived = false; // Reset data reception flag
    }
}

// Main function for continuous data reception and transmission
int main() {
    usart_init(); // Initialize USART for communication

    while (1) {
        receive_data(); // Continuously check and receive data
        send_data();    // Send data back once 1000 bytes are received
    }
}
