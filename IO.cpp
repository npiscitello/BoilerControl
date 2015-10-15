#include "Encoder.h"
#include "LedControl.h"

// pin definitions
#define LED_DAT 8			// data to the LED driver chip
#define LED_CLK 7			// clock to the LED driver chip
#define LED_SEL 9			// selector lead to the LED driver chip
#define ENC1 2				// first encoder pin
#define ENC2 4				// second encoder pin
#define BUTTON 11			// encoder button pin
#define RELAY 6				// relay pin
#define THERM A0			// thermistor pin

class IO {

	private:
		// define variables
	int enc_value, old_enc_value;
	unsigned int output_temp, therm_value;
	char display_vars[ARRAY_SIZE];  bool index_vars[ARRAY_SIZE];

    	// return the relative encoder value since last read
	int readEncoderRelative() {
		// read encoder value
		old_enc_value = enc_value;
		enc_value = (enc.read())/2;
			// calculate and return difference between this read and last read:
        	// this library registers 2 counts per "click", so adjust down to
        	// one count per "click" for intuitiveness
		return enc_value - old_enc_value;
	}

	public:
		// update the encoder value when asked
	int getEncoder() {
		return readEncoderRelative();
	}

		// returns the thermistor reading in *F
	int getTherm() {
		return therm_value;
	}

		// update the thermistor value from the averaging function
	void updateTherm(int update_value) {
		therm_value = update_value;
	}

		// set number of iterations the display for() loop goes
	void init() {
		for(int i = 0; i < ARRAY_SIZE; i++) {
			display_vars[i] = ' ';
			index_vars[i] = false;
		}
	}

		// display values when asked - receives the number to be displayed and the index
	void output(int number_display, int index_display) {
			// get display value and convert it to be compatible with setChar()
		for(int i = (NUMDIGS - 1); i >= 0; i--) {
			display_vars[i] = number_display % 10;
			number_display /= 10;
		}
			//get index value and convert it to be compatible with setChar()
		for(int i = 0; i < NUMVARS; i++) {
			if(index_display == i) {
				index_vars[i] = true;
			} else {
				index_vars[i] = false;
			}
		}
			// display numbers
		for(int i = 0; i < ARRAY_SIZE; i++) {
			disp.setChar(0, i, display_vars[i], index_vars[i]);
		}
	}

		// enable continuous thermistor averaging and display updates
	void enable() {
		readTherm.enable();
		updateDisplay.enable();
	}

		// disable continuous thermistor averaging and display updates
	void disable() {
		readTherm.disable();
		updateDisplay.disable();
	}

};
