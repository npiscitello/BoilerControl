#ifndef __I_h
#define __I_h

class IO {
	public:
		void init();										// initializes functions
		int getEncoder();									// returns the relative encoder read since last call
		void buttonHandler();								// responds to button ISR
		int getButtonPresses();								// returns number of button presses since last read
		int getTherm();										// returns thermistor reading in *F
		unsigned long getLastEvent();						// returns millis() output of last input for timeout calculations
		void output(int number_display, int index_display);	// outputs to LEDs and display
		void circOn();										// turns circulators on
		void circOff();										// turns circulators off
		bool getCircState();								// returns circulator state
		unsigned long getLastCircAction();					// returns millis() output of last circulator on/off call
		void serialEnable();								// enables serial comms
		void serialWrite(String data);						// prints to the serial terminal
};

#endif
