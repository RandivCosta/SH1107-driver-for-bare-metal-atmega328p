#ifndef SH1107_DRIVER_H
#define SH1107_DRIVER_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// I2C address of the SH1107 OLED
#define OLED_ADDR 0x3C

// ===== Public API =====
void i2c_init(void);
void oled_init(void);
void oled_clear(void);
//void oled_print_at(const char *s, uint8_t row);
void oled_print_at(const char *s, uint8_t row, uint8_t inverted);

#endif

