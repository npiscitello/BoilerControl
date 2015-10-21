#ifndef __I_h
#define __I_h

#define ARRAY_SIZE 4		// takes the greater of NUMVARS or NUMDIGS to setup the display arrays

class IO {
	private:
			// define variables
		int enc_value;					// current encoder value
		int old_enc_value;				// previous encoder value
		volatile int button_presses;	// how many button presses since last call
		unsigned long last_input_event;	// holds time of last input event (for timeout calculations)
		unsigned long last_circ_action;	// holds time of last circulator on/off call
		char display_vars[ARRAY_SIZE];  // display digits
		bool index_vars[ARRAY_SIZE];	// variable indicator display values
		bool circ_state;				// holds on(true)/off(false) state of circulator

	public:
		void init();										// initializes functions
		int getEncoder();									// returns the relative encoder read since last call
		void buttonHandler();								// responds to button ISR
		int getButtonPresses();								// returns number of button presses since last read
		unsigned int getTherm();							// returns thermistor reading in *F
		unsigned long getLastInputEvent();					// returns millis() output of last input for timeout calculations
		void output(int number_display, int index_display);	// outputs to LEDs and display
		void circOn();										// turns circulators on
		void circOff();										// turns circulators off
		bool getCircState();								// returns circulator state
		unsigned long getLastCircAction();					// returns millis() output of last circulator on/off call
		void serialEnable();								// enables serial comms
		void serialWrite(String data);						// prints to the serial terminal
};

#endif
