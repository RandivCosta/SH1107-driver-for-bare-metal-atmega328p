#include "sh1107_driver.h"
#include <avr/io.h>
#include <util/delay.h>

// Function prototypes
void display_item_0(void);
void display_item_1(void);
void display_item_2(void);

// Menu items
const char* items[] = {
    "Item 0",
    "Item 1",
    "Item 2"
};
#define NUM_ITEMS (sizeof(items) / sizeof(items[0]))

// Draw full list once
void display_full_list(uint8_t current_index) {
    oled_clear();
    for (uint8_t i = 0; i < NUM_ITEMS; i++) {
        oled_print_at(items[i], i, (i == current_index));
    }
}

// Update only changed items (no flicker)
void update_highlight(uint8_t old_index, uint8_t new_index) {
    oled_print_at(items[old_index], old_index, 0); // redraw old item normal
    oled_print_at(items[new_index], new_index, 1); // redraw new item inverted
}

int main(void) {
    uint8_t current_index = 0;
    uint8_t previous_index = 0;

    i2c_init();
    oled_init();
    oled_clear();

    // Configure PD2, PD3 as inputs (external pull-ups wired)
    DDRD &= ~((1 << DDD2) | (1 << DDD3));
    PORTD &= ~((1 << PORTD2) | (1 << PORTD3)); // no internal pull-ups

    // Show initial menu
    display_full_list(current_index);

    while (1) {
        // --- Navigation button (PD2) ---
        if (!(PIND & (1 << PIND2))) {
            _delay_ms(50);
            if (!(PIND & (1 << PIND2))) {
                previous_index = current_index;
                current_index = (current_index + 1) % NUM_ITEMS;
                update_highlight(previous_index, current_index); // only update 2 rows
                while (!(PIND & (1 << PIND2))); // wait release
            }
        }

        // --- Select button (PD3) ---
        if (!(PIND & (1 << PIND3))) {
            _delay_ms(50);
            if (!(PIND & (1 << PIND3))) {
                oled_clear();
                switch (current_index) {
                    case 0: display_item_0(); break;
                    case 1: display_item_1(); break;
                    case 2: display_item_2(); break;
                }
                while (!(PIND & (1 << PIND3)));
                _delay_ms(2000);
                display_full_list(current_index); // redraw menu
            }
        }
    }
}

// --- Item functions ---
void display_item_0(void) {
    oled_print_at("Current Index: 0", 0, 0);
    // Set PD1 and PD4 as output pins
    DDRD |= (1 << PD1) | (1 << PD4);
    // Set PD1 to HIGH and PD4 to LOW
    PORTD |= (1 << PD1);
    PORTD &= ~(1 << PD4);
    
}
void display_item_1(void) {
    oled_print_at("Current Index: 1", 0, 0);
}
void display_item_2(void) {
    oled_print_at("Current Index: 2", 0, 0);
}
