#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "print.h"
#include "usb_device.h"
#include "string.h"

void PrintReadings(const char *value_label, uint8_t len, uint16_t *read_values);
void TimeCheckpointLog(const char *label);

#ifdef __cplusplus
}
#endif

#endif /* __PRINT_H__ */

