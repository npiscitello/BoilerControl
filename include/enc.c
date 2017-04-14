// see enc.h for any relevant header info
#include "enc.h"

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/io.h>

// holds the number of encoder clicks since last read
volatile uint8_t enc_val;

void enc_setup(void) {
  sei();
  return;
}

uint8_t enc_read(void) {
  uint8_t retval;
  // make sure the encoder value doesn't change when we're RMWing
  // (YCM, if you have it, will probably complain about an unused var. Ignore it.)
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    retval = enc_val;
    enc_val = 0;
  }
  return retval;
}

ISR(INT0_vect) {
  // stuff
}

ISR(INT1_vect) {
  enc_val++;
}
