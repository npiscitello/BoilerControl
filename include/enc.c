// see enc.h for any relevant header info
#include "enc.h"

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/io.h>
#include <avr/cpufunc.h>

// data direction regs and pins
#define ENC_DDR_REG   DDRD
#define ENC_DDR_BTN   DDD2    // pin 4
#define ENC_DDR_A     DDD4    // pin 6
#define ENC_DDR_B     DDD3    // pin 5

// input regs and pins
#define ENC_IN_REG    PIND
#define ENC_IN_BTN    PIND2
#define ENC_IN_A      PIND4
#define ENC_IN_B      PIND3

// output regs and pins
#define ENC_OUT_REG   PORTD
#define ENC_OUT_BTN   PORTD2
#define ENC_OUT_A     PORTD4
#define ENC_OUT_B     PORTD3

// holds the number of encoder clicks since last read (can be pos or neg)
// if overflows are a problem, change to 16 bit
volatile int8_t enc_val = 0;

// holds the index and bounds
#define ENC_MIN_INDEX   0
#define ENC_MAX_INDEX   3
volatile uint8_t enc_index_val = 0;

void enc_setup(void) {
  // enable input with pullups on required pins with nop for sync
  ENC_DDR_REG &= ~_BV(ENC_DDR_BTN) & ~_BV(ENC_DDR_A) & ~_BV(ENC_DDR_B);
  ENC_OUT_REG |= _BV(ENC_OUT_BTN) | _BV(ENC_OUT_A) | _BV(ENC_OUT_B);
  _NOP();
  // enable interrupts
  sei();
  return;
}

int8_t enc_read(void) {
  int8_t retval;
  // make sure the encoder value doesn't change when we're RMWing
  // (YCM, if you have it, will probably complain about an unused var. Ignore it.)
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    retval = enc_val;
    enc_val = 0;
  }
  return retval;
}

uint8_t enc_index(void) {
  uint8_t retval;
  // make sure the index doesn't change when we're reading it
  // (YCM, if you have it, will probably complain about an unused var. Ignore it.)
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    retval = enc_index_val;
  }
  return retval;
}

// button on pin 4
ISR(INT0_vect) {
  // increment index with rollover
  if( enc_index_val < ENC_MAX_INDEX ) {
    enc_index_val++;
  } else {
    enc_index_val = ENC_MIN_INDEX;
  }
}

// encoder on pins 5 (B) and 6 (A)
ISR(INT1_vect) {
  // CW:  B falls + A low or B rises and A high
  // CCW: B falls + A high or B rises and A low
  if( ENC_IN_REG & (0x00 | _BV(ENC_IN_B)) ) {
    // B rose...
    if( ENC_IN_REG & (0x00 | _BV(ENC_IN_A)) ) {
      // ...and A is high - clockwise
      enc_val++;
    } else {
      // ...and A is low - counterclockwise
      enc_val--;
    }
  } else {
    // B fell...
    if( ENC_IN_REG & (0x00 | _BV(ENC_IN_A)) ) {
      // ...and A is high - counterclockwise
      enc_val--;
    } else {
      // ...and A is low - clockwise
      enc_val++;
    }
  }
}
