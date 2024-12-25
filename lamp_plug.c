#include "lamp_plug.h"
#include "tm4c123gh6pm.h"
#include "utils.h"
#include "uart.h"
#include "dio.h"




uint8_t app_lamp_switch_state = SWITCH_OFF;
uint8_t app_plug_switch_state = SWITCH_OFF;


// lamp
void lamp_init(uint8_t port, uint8_t pin) {
    dio_init(port, pin, OUT, DIGITAL);
    dio_writepin(port, pin, 0);
    return; 
}

uint8_t lamp_get(uint8_t port, uint8_t pin) {
    return dio_readpin(port, pin);
}

void lamp_set(uint8_t port, uint8_t pin, uint8_t state) {
    dio_writepin(port, pin, state);
     
}

void lamp_update_state(uint8_t port, uint8_t pin, uint8_t switch_state) { 
    uint8_t lamp_state = switch_state ^ app_lamp_switch_state;  
    lamp_set(port, pin, lamp_state);   
}



// plug
void plug_init(uint8_t port, uint8_t pin) {
    dio_init(port, pin, OUT, DIGITAL);
    dio_writepin(port, pin, 0);
    return;
}

uint8_t plug_get(uint8_t port, uint8_t pin) {
    return dio_readpin(port, pin);
}

void plug_set(uint8_t port, uint8_t pin, uint8_t state) {
    dio_writepin(port, pin, state);
}

void plug_update_state(uint8_t port, uint8_t pin, uint8_t switch_state) {
  uint8_t t = app_plug_switch_state;
    uint8_t plug_state = switch_state ^ app_plug_switch_state; 
    plug_set(port, pin, plug_state);
}

// switch  
void switch_init(uint8_t port, uint8_t pin) {
    dio_init(port, pin, IN, DIGITAL);
    dio_pull(port, pin, UP); 
    //dio_writepin(port, pin, SWITCH_OFF);//?
}

uint8_t switch_get(uint8_t port, uint8_t pin) {
    return dio_readpin(port, pin);
}


void set_app_lamp_switch_state(uint8_t value){
    app_lamp_switch_state = value;
}

void set_app_plug_switch_state(uint8_t value){
    app_plug_switch_state = value;
}