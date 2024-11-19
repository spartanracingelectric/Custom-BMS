#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "string.h"

// Buffer size for USB transmission
#define USB_BUFFER_SIZE 2048

// Function prototypes
void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings); 
void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings); 
void usb_timestamp(char* message, uint32_t timestamp); 
void clear_buffer(); 

// ITM debug output
int ITM_debug_write(const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif /* INC_PRINT_H_ */
