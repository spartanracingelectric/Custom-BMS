#include "print.h"
#include "stm32f1xx.h" // Or the appropriate HAL header for your STM32 family

void ITM_Init(void) {
    // Enable the ITM and configure it for SWO output
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // Enable ITM and DWT
    ITM->LAR = 0xC5ACCE55;                         // Unlock ITM (key for access)
    ITM->TCR = ITM_TCR_ITMENA_Msk                  // Enable ITM
               | ITM_TCR_TSENA_Msk                 // Enable timestamps (optional)
               | ITM_TCR_SWOENA_Msk;               // Enable SWO output
    ITM->TER = 0x1;                                // Enable stimulus port 0
}

void ITM_SendString(const char* str) {
    while (*str) {
        if (ITM->PORT[0].u32 == 0) { // Check if the ITM port is ready
            ITM_SendChar(*str++);    // Send character
        }
    }
}

// void usb_transmit_voltages(uint8_t volt_count, uint16_t* volt_readings) {
//     char buffer[128];
//     snprintf(buffer, sizeof(buffer), "Voltages:\n");
//     ITM_SendString(buffer);

//     for (uint8_t i = 0; i < volt_count; i++) {
//         snprintf(buffer, sizeof(buffer), "\tV%u: %u mV\n", i + 1, volt_readings[i]);
//         ITM_SendString(buffer);
//     }
// }

// void usb_transmit_temperatures(uint8_t therm_count, uint16_t* temp_readings) {
//     char buffer[128];
//     snprintf(buffer, sizeof(buffer), "Temperatures:\n");
//     ITM_SendString(buffer);

//     for (uint8_t i = 0; i < therm_count; i++) {
//         snprintf(buffer, sizeof(buffer), "\tT%u: %u °C\n", i + 1, temp_readings[i]);
//         ITM_SendString(buffer);
//     }
// }

// void usb_timestamp(char* message, uint32_t timestamp) {
//     char buffer[128];
//     snprintf(buffer, sizeof(buffer), "TIME: %lu [%s]\n", timestamp, message);
//     ITM_SendString(buffer);
// }
