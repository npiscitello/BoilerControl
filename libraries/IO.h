/* This class serves as a one-stop-shop for all things world-related. Whether it be
 * reading a sensor or displaying some numbers, this class is what you need!
 */

#ifndef __I_h
#define __I_h

	// constant definitions - if NUMVARS or NUMDIGS change, be sure to update ARRAY_SIZE in IO.h as well
#define NUMVARS 4			// number of LEDs in display (also how many index locations)
#define NUMDIGS 3			// number of digits in display
#define ARRAY_SIZE 4		// takes the greater of NUMVARS or NUMDIGS to setup the display arrays
#define BAUD 57600			// baud rate for serial debugging
#define INTENSITY 14		// intensity for LED driver - 0 to 16

	// thermistor calculation definitions
#define RC 3900
#define T0 0.00335401643	// 1 / 298.15
#define B 4500
#define R0 50000

	// pin definitions
#define LED_DAT 8			// data to the LED driver chip
#define LED_CLK 7			// clock to the LED driver chip
#define LED_SEL 9			// selector lead to the LED driver chip
#define ENC1 2				// first encoder pin
#define ENC2 4				// second encoder pin
#define RELAY 6				// relay pin
#define THERM A0			// thermistor pin

class IO {
	private:
			// define variables
		int enc_value;						// current encoder value
		unsigned long last_input_event;		// holds time of last input event (for timeout calculations)
		unsigned long last_button_event;	// holds time of last button event
		unsigned long last_circ_event;		// holds time of last circulator on/off call
		bool circ_state;					// holds on(true)/off(false) state of circulator
		char display_vars[ARRAY_SIZE];  	// display digits
		bool index_vars[ARRAY_SIZE];		// variable indicator display values
		bool led_state;						// store on/off state of LED driver

	public:
		void init();										// initializes functions
		int getEncoder();									// returns the relative encoder read since last call
		void buttonHandler();								// responds to button ISR
		unsigned long getLastButtonEvent();					// returns last button event
		unsigned int getTherm();							// returns thermistor reading in *F
		unsigned long getLastInputEvent();					// returns millis() output of last input for timeout calculations
		void output(int number_display, int index_display);	// outputs to LEDs and display
		void circOn();										// turns circulators on
		void circOff();										// turns circulators off
		bool getCircState();								// returns circulator state
		unsigned long getLastCircAction();					// returns millis() output of last circulator on/off call
		void serialEnable();								// enables serial comms
		bool getLEDState();									// get the on/off state of LED chip
		void setLEDState(bool enabled);						// set the on/off state of LED chip
};

#endif
