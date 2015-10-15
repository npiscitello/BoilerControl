#ifndef __I_h
#define __I_h

class IO {
	public:
		void init();
		int getEncoder();
		int getTherm();
		void updateTherm();
		void output();
		void enable();
		void disable();
};

#endif
