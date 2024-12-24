#ifndef LAMP_PLUG_H
#define LAMP_PLUG_H

#include <stdint.h>



#define SWITCH_ON 0
#define SWITCH_OFF 1



// Lamp functions
void lamp_init(uint8_t port, uint8_t pin);
uint8_t lamp_get(uint8_t port, uint8_t pin);
void lamp_set(uint8_t port, uint8_t pin, uint8_t state);
void lamp_update_state(uint8_t port, uint8_t pin, uint8_t switch_state);
void set_app_lamp_switch_state(uint8_t value);


// Plug functions
void plug_init(uint8_t port, uint8_t pin);
uint8_t plug_get(uint8_t port, uint8_t pin);
void plug_set(uint8_t port, uint8_t pin, uint8_t state);
void plug_update_state(uint8_t port, uint8_t pin, uint8_t switch_state);
void set_app_plug_switch_state(uint8_t value);

// Switch functions
void switch_init(uint8_t port, uint8_t pin);
uint8_t switch_get(uint8_t port, uint8_t pin);

#endif // LAMP_PLUG_H
