#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdio.h"
#include "string.h"

// Function prototypes
void ITM_Init(void);
void ITM_SendString(const char* str);

// void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings);
// void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings);
// void usb_timestamp(char* message, uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif /* INC_PRINT_H_ */
