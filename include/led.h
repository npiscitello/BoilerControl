// LED chip driver. Comments written for use with cldoc (https://jessevdk.github.io/cldoc/)
// This lib also includes SPI functions because the MAX72XX is the only SPI device

#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stdbool.h>

/*  Prints a three-digit number
 *  @num number to print, with leading zeroes, range-checked */
void led_disp(uint16_t num);

/*  Prints a number onto the specified SSD
 *  @digit the digit to be displayed
 *  @index the SSD to print onto, range-checked (0-7)
 *  There is no range checking. The four LSBs define the character to print (in order: 0-9,
 *  <dash>, E, H, L, P, <blank>) and the MSB controls the decimal point. */
void led_print(uint8_t digit, uint8_t index);

//- bool takes a full byte - turn into a global bitfield if the space is critical
/*  Toggle MAX72XX sleep mode
 *  @sleep send the sleep (true) or wake (false) command */
void led_sleep(bool sleep);

/*  Setup hardware SPI and MAX72XX*/
void led_setup();

/*  Write a MAX72XX reg
 *  @reg which register on the MAX to write
 *  @val the value to write to the register */
void led_transmit(uint8_t reg, uint8_t val);

#endif
