#include "print.h"
#include "stdint.h"
#include "time.h"

void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings) {
    size_t buffer_index = 0;

    // Add the header for voltages
    int written = snprintf(usb_transmit_buffer + buffer_index,
                           sizeof(usb_transmit_buffer) - buffer_index,
                           "Voltages:\n");
    if (written < 0 || buffer_index + written >= sizeof(usb_transmit_buffer)) {
        return; // Prevent buffer overflow
    }
    buffer_index += written;

    // Iterate through each voltage reading
    for (uint8_t i = 0; i < volt_count; i++) {
        uint16_t voltage_mV = volt_readings[i] / 1000; // Compute voltage in millivolts

        // Format the voltage reading with indentation
        written = snprintf(usb_transmit_buffer + buffer_index,
                           sizeof(usb_transmit_buffer) - buffer_index,
                           "\tV%u: %u mV\n", i + 1, voltage_mV);

        // Prevent buffer overflow
        if (written < 0 || buffer_index + written >= sizeof(usb_transmit_buffer)) {
            break;
        }
        buffer_index += written;
    }

    // Transmit the complete buffer and clear it
    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer));
    clear_buffer();
}

void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings) {
    size_t buffer_index = 0;

    // Add the header for temperatures
    int written = snprintf(usb_transmit_buffer + buffer_index,
                           sizeof(usb_transmit_buffer) - buffer_index,
                           "Temperatures:\n");
    if (written < 0 || buffer_index + written >= sizeof(usb_transmit_buffer)) {
        return; // Prevent buffer overflow
    }
    buffer_index += written;

    // Iterate through each temperature reading
    for (uint8_t i = 0; i < therm_count; i++) {
        // Format the temperature reading with indentation
        written = snprintf(usb_transmit_buffer + buffer_index,
                           sizeof(usb_transmit_buffer) - buffer_index,
                           "\tT%u: %u °C\n", i + 1, temp_readings[i]);

        // Prevent buffer overflow
        if (written < 0 || buffer_index + written >= sizeof(usb_transmit_buffer)) {
            break;
        }
        buffer_index += written;
    }

    // Transmit the complete buffer and clear it
    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer));
    clear_buffer();
}

void usb_timestamp(char* message, uint32_t timestamp) {

    snprintf(usb_transmit_buffer, USB_BUFFER_SIZE, 
        "-------- TIME : %lu  -------- [%s] -------- \r\n", 
        timestamp, message
    ); 

    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer)); 

    clear_buffer(); 
}

void clear_buffer() {
    memset(usb_transmit_buffer, 0, USB_BUFFER_SIZE); 
}
