#ifndef __E_h
#define __E_h

class EEPROM {
	public:
		void init();
		bool getEnabled();
		void enable();
		void disable();
};

#endif
