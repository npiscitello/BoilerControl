#include <Arduino.h>
#include "EEPROM.h"

	// initialize EEPROM memory
void EEPROM::init() {
	// probably initialize locations,etc.
}

	// write data to EEPROM memory - wear-leveling enabled
void EEPROM::write() {
	// eventually take data and perform an update function -
	// use update method and wear leveling
}

	// read data from EEPROM memory
void EEPROM::read() {
	// eventually return data to be used in variable initializaton
}
