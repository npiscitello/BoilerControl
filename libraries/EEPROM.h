#ifndef __E_h
#define __E_h

class EEPROM {
	public:
		void init();	// initialize EEPROM memory
		void write(int circ_on, int circ_off, int thresh);	// write data to EEPROM memory - wear leveling enabled
		void read();	// read data to EEPROM memory
};

#endif
