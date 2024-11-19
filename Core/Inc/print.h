#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "print.h"
#include "usb_device.h"
#include "string.h"

#define USB_BUFFER_SIZE         2048

void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings); 
void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings); 

void usb_timestamp(char* message, uint32_t timestamp); 
void clear_buffer(); 

#ifdef __cplusplus
}
#endif

#endif /* __PRINT_H__ */

