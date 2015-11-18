#include <iostream>
#include <fstream>
using namespace std;

#define EEPROM_BYTES 32
#define NUMVARS 4

int passid_addr = 0;
unsigned char passid = 1;
unsigned char data[32];

// writes the number to the specified address
void write(unsigned char circ_on, unsigned char circ_off, unsigned char thresh) {
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
	data[passid_addr] = passid;   data[passid_addr + 1] = circ_on;
	data[passid_addr + 2] = circ_off;   data[passid_addr + 3] = thresh;
}

void findIndexes() {
	passid = data[0];
		// handle the special case that the last write was to the last 4 bytes...
	if(data[EEPROM_BYTES - 4] == passid) {
		passid_addr = EEPROM_BYTES - 4;
	} else {
			// find the last place to which the data was written
		for(int i = NUMVARS; i < EEPROM_BYTES; i += NUMVARS) {
			if(data[i] != passid) {
				passid_addr = i-NUMVARS;
				break;
			}
		}
	}
}

int main() {
	ofstream file;
	file.open("output.txt");
	for(int j = 0; j < EEPROM_BYTES*256; j++) {
		findIndexes();
		file << "\npassid = " << (int) passid << "     passid_addr = " << passid_addr << "\n\n";
		write(0,0,0);
		for(int i = 0; i < 32; i++) {
			file << (int) data[i] << ", ";
		}
		file << "\n\n\n";
	}
	file.close();
	return 0;
}
