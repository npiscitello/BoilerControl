// LED chip driver. Comments written for use with cldoc (https://jessevdk.github.io/cldoc/)
// This lib also includes SPI functions because the MAX72XX is the only SPI device

#ifndef LED_H
#define LED_H

#include <stdint.h>

/*  Prints a three-digit number
 *  @num number to print, with leading zeroes, range-checked */
void led_disp(uint16_t num);

/*  Setup hardware SPI and MAX72XX*/
void led_setup(void);

/*  Write a MAX72XX reg
 *  @reg which register on the MAX to write
 *  @val the value to write to the register */
void led_transmit(const uint8_t reg, const uint8_t val);

#endif
