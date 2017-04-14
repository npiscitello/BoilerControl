// see led.h for any relevant header info
#include "led.h"

// register defs, etc
#include <avr/io.h>
#define CS_PORT PORTB
#define CS_PIN PORTB2

// MAX72XX regs
#define MAX_NOP           0x00
#define MAX_D0            0x01
#define MAX_D1            0x02
#define MAX_D2            0x03
#define MAX_D3            0x04
#define MAX_D4            0x05
#define MAX_D5            0x06
#define MAX_D6            0x07
#define MAX_D7            0x08
#define MAX_DECODE_MODE   0x09
#define MAX_INTENSITY     0x0A
#define MAX_SCAN_LIMIT    0x0B
#define MAX_SHUTDOWN      0x0C
#define MAX_DISPLAY_TEST  0x0F
// offset to the first digit reg, to take advantage of contiguousness
#define MAX_DIG_OFFSET    MAX_D0
// Most significant digit
#define MAX_DIG_FIRST     0
// Least significant digit (ones place)
#define MAX_DIG_LAST      2

// MAX72XX convenient values
#define MAX_SLEEP   0x00
#define MAX_AWAKE   0x01
#define MAX_RAW     0x00
#define MAX_CODEB   0xFF
#define MAX_SCAN3   0x02
#define MAX_BIGNUM  999

// write out a three-digit integer. We'll never need decimal points.
// This prints the hundereds place in index 0 and the ones place in index 2.
// leading zeroes are preserved
// In the actual transmit function, the four LSBs define the character to print (in order: 0-9,
// <dash>, E, H, L, P, <blank>) and the MSB controls the decimal point.
void led_disp(uint16_t num) {
  if( num <= MAX_BIGNUM ) {
    for( uint8_t i = MAX_DIG_LAST; i >= MAX_DIG_FIRST; i-- ) {
      led_transmit(MAX_DIG_OFFSET + i, num % 10);
      num /= 10;
    }
  }
  return;
}

// setup hardware SPI and run MAX72XX bootup init
void led_setup(void) {
  // power up SPI peripheral
  PRR &= !_BV(PRSPI);

  // set up SPI: master, CLK = system clock / 2
  // pins: SS = PB2, MOSI = PB3, SCK = PB5
  DDRB = _BV(DDB2) | _BV(DDB3) | _BV(DDB5);
  SPCR = _BV(SPE) | _BV(MSTR);
  SPSR = _BV(SPI2X);

  // set up MAX7219
  led_transmit(MAX_DECODE_MODE, MAX_CODEB);
  // intensity values range from 0x00 to 0x0F
  led_transmit(MAX_INTENSITY, 0x0F);
  // see datasheet - this setting may impact your selection for the RSET resistor
  led_transmit(MAX_SCAN_LIMIT, MAX_SCAN3);
  led_transmit(MAX_SHUTDOWN, MAX_AWAKE);
  return;
}

// write a word to a MAX72XX reg
void led_transmit(const uint8_t reg, const uint8_t val) {
  // set CS low
  CS_PORT &= 0xFF & !_BV(CS_PIN);
  // what register to write on the MAX7221
  SPDR = reg;
  // wait for the transmission to finish
  while( !(SPSR & _BV(SPIF)) ) {}
  // what to write into the register on the MAX7221
  SPDR = val;
  // wait for the transmission to finish
  while( !(SPSR & _BV(SPIF)) ) {}
  // bring CS high
  CS_PORT |= 0x00 | _BV(CS_PIN);
  return;
}
