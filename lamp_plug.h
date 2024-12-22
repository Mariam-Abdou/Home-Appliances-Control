#ifndef LAMP_PLUG_H
#define LAMP_PLUG_H

#include <stdint.h>

// Lamp functions
void lamp_init(uint8_t port, uint8_t pin);
uint8_t lamp_get(uint8_t port, uint8_t pin);
void lamp_set(uint8_t port, uint8_t pin, uint8_t state);
void lamp_update_state(uint8_t port, uint8_t pin, uint8_t switch_state, uint8_t app_signal);

// Plug functions
void plug_init(uint8_t port, uint8_t pin);
uint8_t plug_get(uint8_t port, uint8_t pin);
void plug_set(uint8_t port, uint8_t pin, uint8_t state);
void plug_update_state_signal(uint8_t port, uint8_t pin, uint8_t switch_state, uint8_t app_signal);

// Switch functions
void switch_init(uint8_t port, uint8_t pin);
uint8_t switch_get(uint8_t port, uint8_t pin);

#endif // LAMP_PLUG_H
