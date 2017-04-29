// main boiler control file. Boilerhead to come?
// fuses: default (l: 0x62, h: 0xD9, e: 0x07)
// system clock: 8MHz / 8 = 1MHz */

#include "include/led.h"
#include "include/enc.h"

#include <avr/io.h>

int main(void) {
  /*
    ; divide 8 MHz internal crystal by 64
    ; the clock is already divided by 8 due to fuse settings
    ; set prescaler to divide that signal by 8 additionally
    ; this gives a system clock speed of 1 MHz / 8 = 125 kHz
    ; According to the datasheet, the ADC needs a system clock above 100 kHz,
    ; so this is as low as we can go.
    ldi TEMP,0x00 | _BV(CLKPCE)
    sts CLKPR,TEMP
    ldi TEMP, 0x00 | _BV(CLKPS1) | _BV(CLKPS0)
    sts CLKPR,TEMP
  */
  CLKPR = 0x00 | _BV(CLKPCE);
  CLKPR = 0x00 | _BV(CLKPS1) | _BV(CLKPS0);

  // sets SPI master clock as system clock divided by 2
  led_setup();
  enc_setup();

  // run loop
  while(1==1) {
    // do stuff in here
  }

  // if it gets here, something very bad happened
  return 0;
}
