#include "print.h"

void AppendLine(char *out_buffer, uint8_t line_size, const char *format_str,
                ...);
void TransmitMessage(char *out_buffer);

/*
 * Log readings from a value list
 */
void PrintReadings(const char *value_label, uint8_t len,
                   uint16_t *read_values) {
    char out_buffer[2048];
    snprintf(out_buffer, strlen(value_label) + 12, "%s Readings:\n\0",
             value_label);

    for (uint8_t i = 0; i < len; i++) {
        AppendLine(out_buffer, 20, "C%u: %u", i + 1, read_values[i]);
    }

    TransmitMessage(out_buffer);
}

/*
 * Log current time stamp with event label
 */
void TimeCheckpointLog(const char *label) {
    char out_buffer[2048];
    snprintf(out_buffer, strlen(label) + 20, "Checkpoint time for %s: %ds\0\n",
             label, (double)clock() / CLOCKS_PER_SEC);
    TransmitMessage(out_buffer);
}

/*
 * Append message line to buffer
 */
void AppendLine(char *out_buffer, uint8_t line_size, const char *format_str,
                ...) {
    va_list args;
    va_start(args, format_str);
    char buffer[line_size];

    vnsprintf(buffer, line_size, format_str, args);
    strncat(out_buffer, buffer, line_size);
    strncat(out_buffer, "\n\0", 2);

    va_end(args);
}

/*
 * Transmit provide message over USB
 */
void TransmitMessage(char *out_buffer) {
    strncat(out_buffer, "\n\0", 2);
    USB_Transmit(out_buffer, strlen(out_buffer);
}
