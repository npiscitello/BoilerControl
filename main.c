// main boiler control file. Boilerhead to come?
// fuses: default (l: 0x62, h: 0xD9, e: 0x07)
// system clock: 8MHz / 8 = 1MHz */

#include "include/led.h"
#include "include/enc.h"

int main(void) {
  // setup
  led_setup();
  enc_setup();

  // run loop
  while(1==1) {
    // do stuff in here
  }

  // if it gets here, something very bad happened
  return 0;
}
