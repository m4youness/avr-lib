#ifndef AL_H_
#define AL_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#define F_CPU 16000000
#include <util/delay.h>

enum PIN_DIR {
  LOW = 0,
  HIGH = 1,
};

void pin_mode(uint8_t pin, enum PIN_DIR dir);
void digital_write(uint8_t pin, enum PIN_DIR dir);
void serial_begin(size_t baud);
void serial_print(unsigned char *data);

#ifndef AL_IMPLEMENTATION
#define AL_IMPLEMENTATION
#endif

#ifdef AL_IMPLEMENTATION
#define MAX_PINS_PORTD 8
#define MAX_PINS_PORTB 6
#define UBRR(baud) F_CPU / 16 / baud - 1
#define DELAY_MS(ms) _delay_ms(ms)
#define SET_PIN_STATE(dir, pin, reg)                                           \
  do {                                                                         \
    if ((dir) == 0) {                                                          \
      (reg) &= ~(1 << (pin));                                                  \
    } else {                                                                   \
      (reg) |= (1 << (pin));                                                   \
    }                                                                          \
  } while (0)

void pin_mode(uint8_t pin, enum PIN_DIR dir) {
  if (pin < MAX_PINS_PORTD) {
    SET_PIN_STATE(dir, pin, DDRD);
    return;
  }

  pin -= MAX_PINS_PORTD;
  if (pin < MAX_PINS_PORTB) {
    SET_PIN_STATE(dir, pin, DDRB);
    return;
  }

  pin -= MAX_PINS_PORTB;

  SET_PIN_STATE(dir, pin, DDRC);
}

void digital_write(uint8_t pin, enum PIN_DIR dir) {
  if (pin < MAX_PINS_PORTD) {
    SET_PIN_STATE(dir, pin, PORTD);
    return;
  }

  pin -= MAX_PINS_PORTD;
  if (pin < MAX_PINS_PORTB) {
    SET_PIN_STATE(dir, pin, PORTB);
    return;
  }

  pin -= MAX_PINS_PORTB;

  SET_PIN_STATE(dir, pin, PORTC);
}

void serial_begin(size_t baud) {
  size_t ubrr = UBRR(baud);
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void serial_print(unsigned char *data) {
  while (*data) {
    while (!(UCSR0A & (1 << UDRE0))) {
    }
    UDR0 = *data;
    data++;
  }
}

#endif // AL_IMPLEMENTATION
#endif // AL_H_
