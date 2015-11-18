#include <Arduino.h>
#include "STORAGE.h"
#include <EEPROM.h>

	// initialize EEPROM memory
void STORAGE::init() {
		// find the last written set of data
	findIndexes();
}

	// finds the index of the data using passid, etc.  See EEPROM.h
void STORAGE::findIndexes() {
	passid = EEPROM.read(0);
		// handle the special case that the last write was to the last 4 bytes...
	if(EEPROM.read(EEPROM_BYTES - 4) == passid) {
		passid_addr = EEPROM_BYTES - 4;
	} else {
			// find the last place to which the data was written
		for(int i = NUMVARS; i < EEPROM_BYTES; i += NUMVARS) {
			if(EEPROM.read(i) != passid) {
				passid_addr = i-NUMVARS;
				break;
			}
		}
	}
}

	// writes the number to the specified address
void STORAGE::write(byte circ_on, byte circ_off, byte thresh) {
		// if advancing NUMVARS bytes overflows the EEPROM...
	if(passid_addr + NUMVARS == EEPROM_BYTES) {
			// ...reset to the beginning and increment passid
		passid_addr -=  EEPROM_BYTES - NUMVARS;
			// if passid overflows a byte...
		passid ++;
		if(passid == 0) {
			passid = 1;
		}
	} else {
		passid_addr += NUMVARS;
	}
	EEPROM.update(passid_addr, passid);   EEPROM.update(passid_addr + 1, circ_on);
	EEPROM.update(passid_addr + 2, circ_off);   EEPROM.update(passid_addr + 3, thresh);
}

	// read data from EEPROM memory
int STORAGE::readCircOn() {
	return EEPROM.read(passid_addr + 1);
}

	// read data from EEPROM memory
int STORAGE::readCircOff() {
	return EEPROM.read(passid_addr + 2);
}

	// read data from EEPROM memory
int STORAGE::readThresh() {
	return EEPROM.read(passid_addr + 3);
}
