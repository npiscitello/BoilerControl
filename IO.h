#ifndef __I_h
#define __I_h

class IO {
	public:
		void init();
		bool getEnabled();
		int getEncoder();
		int getTherm();
		void output();
		void circOn();
		void circOff();
		void enable();
		void disable();
};

#endif
