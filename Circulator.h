#ifndef __C_h
#define __C_h

class Circulator {
	public:
		void init();
		int getOnVar();
		int getOffVar();
		void setTiming(int, int);
		void applyTiming();
		void turnOn();
		void turnOff();
		void enable();
		void disable();
};

#endif
