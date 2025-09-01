#include "sh1107_driver.h"
#include <avr/io.h>
#include <util/delay.h>



int main(void) {
  oled_print_at("Normal Text", 0, 0); // row 0, not inverted
  oled_print_at("Selected Item", 1, 1); // row 1, inverted
}

