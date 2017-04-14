// Comments written for use with cldoc (https://jessevdk.github.io/cldoc/)
// Encoder/button driver - sets up interrupts and defines ISRs

#ifndef ENC_H
#define ENC_H

#include <stdint.h>

void enc_setup(void);

int8_t enc_read(void);

uint8_t enc_index(void);

#endif
