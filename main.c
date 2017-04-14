// main boiler control file. Boilerhead to come?
// fuses: default (l: 0x62, h: 0xD9, e: 0x07)
// system clock: 8MHz / 8 = 1MHz */

#include "include/led.h"

int main(void) {
  // setup
  led_setup();

  // run loop
  while(true) {
    // do stuff in here
  }

  // if it gets here, something very bad happened
  return 0;
}
