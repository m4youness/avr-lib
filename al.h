#ifndef AL_H_
#define AL_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#define F_CPU 16000000
#include <util/delay.h>

enum Mode {
  LOW = 0,
  HIGH = 1,
};

void pin_mode(uint8_t pin, uint8_t mode);
void digital_write(uint8_t pin, uint8_t mode);

#ifndef AL_IMPLEMENTATION
#define AL_IMPLEMENTATION
#endif

#ifdef AL_IMPLEMENTATION

#define MAX_PINS_PORTD 8
#define MAX_PINS_PORTB 6
#define DELAY_MS(ms) _delay_ms(ms)
#define SET_PIN_STATE(mode, pin, reg)                                          \
  do {                                                                         \
    if ((mode) == 0) {                                                         \
      (reg) &= ~(1 << (pin));                                                  \
    } else {                                                                   \
      (reg) |= (1 << (pin));                                                   \
    }                                                                          \
  } while (0)

void pin_mode(uint8_t pin, uint8_t mode) {
  if (pin < MAX_PINS_PORTD) {
    SET_PIN_STATE(mode, pin, DDRD);
    return;
  }

  pin -= MAX_PINS_PORTD;
  if (pin < MAX_PINS_PORTB) {
    SET_PIN_STATE(mode, pin, DDRB);
    return;
  }

  pin -= MAX_PINS_PORTB;

  SET_PIN_STATE(mode, pin, DDRC);
}

void digital_write(uint8_t pin, uint8_t mode) {
  if (pin < MAX_PINS_PORTD) {
    SET_PIN_STATE(mode, pin, PORTD);
    return;
  }

  pin -= MAX_PINS_PORTD;
  if (pin < MAX_PINS_PORTB) {
    SET_PIN_STATE(mode, pin, PORTB);
    return;
  }

  pin -= MAX_PINS_PORTB;

  SET_PIN_STATE(mode, pin, PORTC);
}

#endif // AL_IMPLEMENTATION
#endif // AL_H_
