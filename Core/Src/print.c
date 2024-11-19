#include "print.h"
#include "usb_device.h"
#include "stdarg.h"
#include "stdio.h"

// Define USB transmission buffer
static char usb_transmit_buffer[USB_BUFFER_SIZE];

// USB transmit voltages
void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings) {
    size_t buffer_index = 0;

    int written = snprintf(usb_transmit_buffer + buffer_index, 
                           USB_BUFFER_SIZE - buffer_index, 
                           "Voltages:\n");
    if (written < 0 || buffer_index + written >= USB_BUFFER_SIZE) {
        return; // Prevent buffer overflow
    }
    buffer_index += written;

    for (uint8_t i = 0; i < volt_count; i++) {
        uint16_t voltage_mV = volt_readings[i] / 1000;

        written = snprintf(usb_transmit_buffer + buffer_index, 
                           USB_BUFFER_SIZE - buffer_index, 
                           "\tV%u: %u mV\n", i + 1, voltage_mV);

        if (written < 0 || buffer_index + written >= USB_BUFFER_SIZE) {
            break;
        }
        buffer_index += written;
    }

    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer));
    clear_buffer();
}

// USB transmit temperatures
void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings) {
    size_t buffer_index = 0;

    int written = snprintf(usb_transmit_buffer + buffer_index, 
                           USB_BUFFER_SIZE - buffer_index, 
                           "Temperatures:\n");
    if (written < 0 || buffer_index + written >= USB_BUFFER_SIZE) {
        return;
    }
    buffer_index += written;

    for (uint8_t i = 0; i < therm_count; i++) {
        written = snprintf(usb_transmit_buffer + buffer_index, 
                           USB_BUFFER_SIZE - buffer_index, 
                           "\tT%u: %u °C\n", i + 1, temp_readings[i]);

        if (written < 0 || buffer_index + written >= USB_BUFFER_SIZE) {
            break;
        }
        buffer_index += written;
    }

    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer));
    clear_buffer();
}

// USB timestamp
void usb_timestamp(char* message, uint32_t timestamp) {
    snprintf(usb_transmit_buffer, USB_BUFFER_SIZE, 
             "-------- TIME : %lu -------- [%s] -------- \r\n", 
             timestamp, message);

    USB_Transmit(usb_transmit_buffer, strlen(usb_transmit_buffer));
    clear_buffer();
}

// Clear the transmission buffer
void clear_buffer() {
    memset(usb_transmit_buffer, 0, USB_BUFFER_SIZE);
}

// ITM debug function
int ITM_debug_write(const char* format, ...) {
    char debug_buffer[128]; // Temporary buffer for debug output
    va_list args;
    va_start(args, format);
    int written = vsnprintf(debug_buffer, sizeof(debug_buffer), format, args);
    va_end(args);

    if (written > 0) {
        for (int i = 0; i < written; i++) {
            ITM_SendChar(debug_buffer[i]);
        }
    }

    return written;
}
