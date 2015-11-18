#include <Arduino.h>
#include "STORAGE.h"
#include <EEPROM.h>

	// initialize EEPROM memory
void STORAGE::init() {
	// probably initialize locations,etc.
}

	// finds the index of the data using passid, etc.  See EEPROM.h
int STORAGE::findNextIndex() {
	passid = EEPROM.read(0);
	return 0;
}

	// write data to EEPROM memory - wear leveling enabled
void STORAGE::writeCircOn(int circ_on) {

}

	// write data to EEPROM memory - wear leveling enabled
void STORAGE::writeCircOff(int circ_off) {

}

	// write data to EEPROM memory - wear leveling enabled
void STORAGE::writeThresh(int thresh) {

}

	// read data from EEPROM memory
int STORAGE::readCircOn() {
	return 1;
}

	// read data from EEPROM memory
int STORAGE::readCircOff() {
	return 2;
}

	// read data from EEPROM memory
int STORAGE::readThresh() {
	return 50;
}
