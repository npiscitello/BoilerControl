#ifndef __E_h
#define __E_h

#define EEPROM_BYTES 1024	// number of bytes in the EEPROM
#define NUMVARS 4			// number of variables to store

class STORAGE {
	private:
		byte passid;							// value of current passid
		int passid_addr;						// memory address of passid value
		void findIndexes();						// find the index of the next 3 empty bytes

	public:
		void init();										// initialize EEPROM memory
		void write(byte circon, byte circoff, byte thresh);	// writes to EEPROM, with wear leveling
		int readCircOn();									// read data from EEPROM memory
		int readCircOff();									// read data from EEPROM memory
		int readThresh();									// read data from EEPROM memory
};

#endif

// Wear leveling script reads each 4 byte set sequentially until it finds a non-current passid.
// It records the index to the current data (the previous 3 bytes) and the current passid.  A
// write operation writes the passid and data to to the next 4 bytes (using update function)
// and updates the index value.

//						|	   |	  |		   |		|		 |		  |		 |		|
// EEPROM mem layout:  	| junk | junk | passid | circon | circoff| thresh | junk | junk |
//						|	   |	  |		   |		|		 |		  |		 |		|

// passid - a unique identifier used to determine which memory pass the wear leveling
// algorithm is on.  1st pass is 1, 2nd is 2, etc. to 255. When pass 255 loops back to zero,
// it resets the current passid to 1.  When the wear leveling function starts looking for the
// valid data, it gets the current pass id from the very first byte in memory, then finds
// the farthest set of 4 bytes with the current pass id. Passid starts at 1 so that the algorithm
// won't get confused about the initial zero state of the memory.
