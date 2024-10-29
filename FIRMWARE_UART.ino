#include <avr/io.h>
#include <avr/interrupt.h>
#include "eeprom_handler.h"
#include "usart_handler.h"

// Define constants
#define EEPROM_SIZE 1024
#define DATA_SIZE 1000

// Global variables for write/read indexes and flags
volatile uint16_t writeIndex = 0;
volatile uint16_t readIndex = 0;
volatile bool dataReceived = false;

// Function to receive data and store in EEPROM
void receive_data() {
    if (!dataReceived) {
        uint8_t incomingByte = usart_receive();

        // Store the received byte in EEPROM if there's space
        if (writeIndex < EEPROM_SIZE) {
            eeprom_write(writeIndex++, incomingByte);
        }

        // Check if 1000 bytes have been received
        if (writeIndex >= DATA_SIZE) {
            dataReceived = true;
        }
    }
}

// Function to send data from EEPROM to serial
void send_data() {
    if (dataReceived) {
        while (readIndex < writeIndex) {
            uint8_t outByte = eeprom_read(readIndex++);
            usart_transmit(outByte);

            // Small delay to ensure smooth transmission, replace with proper delay
            for (volatile int i = 0; i < 1000; i++) {
                asm("");
            }
        }

        // Reset indexes and dataReceived flag after transmission
        writeIndex = 0;
        readIndex = 0;
        dataReceived = false;
    }
}

int main() {
    usart_init(); // Initialize USART

    while (1) {
        receive_data(); // Continuously check and receive data
        send_data();    // Send data back once 1000 bytes are received
    }
}
