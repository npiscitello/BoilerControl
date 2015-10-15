#ifndef __I_h
#define __I_h

class IO {
	public:
		void init();
		bool getEnabled();
		int getEncoder();
		int getTherm();				// returns thermistor reading in *F
		void output(int,int);
		void circOn();
		void circOff();
		void enable();
		void disable();
		void serialEnable();
		void serialWrite(String);	// make sure to call serialEnable first...
};

#endif
