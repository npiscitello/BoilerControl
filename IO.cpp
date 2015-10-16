/* This class serves as a one-stop-shop for all things world-related. Whether it be
 * reading a sensor or displaying some numbers, here's your guy!
 */

#include "Encoder.h"
#include "LedControl.h"

	// constant definitions
#define NUMVARS 4			// number of LEDs in display (also how many index locations)
#define NUMDIGS 3			// number of digits in display
#define ARRAY_SIZE 4		// takes the greater of NUMVARS or NUMDIGS to setup the display arrays
#define NUMSAMPLES 16		// number of samples used in thermistor averaging
#define BAUD 57600			// baud rate for serial debugging

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
#define BUTTON 11			// encoder button pin
#define RELAY 6				// relay pin
#define THERM A0			// thermistor pin

	// define an LED driver chip
LedControl disp = LedControl(LED_DAT, LED_CLK, LED_SEL, 1);

	// define an encoder
Encoder enc = Encoder(ENC1, ENC2);

class IO {

	private:
		// define variables
	int enc_value, old_enc_value, button_presses;
	unsigned long last_event;		// holds time of last input event (for timeout calculations)
	unsigned long last_circ_action;	// holds time of last circulator on/off call
	char display_vars[ARRAY_SIZE];  bool index_vars[ARRAY_SIZE];
	bool circ_state;	// holds on(true)/off(false) state of circulator

    	// return the relative encoder value since last read
	int readEncoderRelative() {
    	// this library registers 2 counts per "click", so adjust down to
    	// one count per "click" for intuitiveness
		old_enc_value = enc_value;
		enc_value = (enc.read())/2;
		if(enc_value - old_enc_value != 0) {
			last_event = millis();
		}
		return enc_value - old_enc_value;
	}

	void buttonHandler() {
		button_presses++;
		last_event = millis();
	}

	public:
		// initialize IO values
	void init() {

			// initialize relay port
		pinMode(RELAY, OUTPUT);

			// wake up display driver, set brightness, and clear
		disp.shutdown(0, false); disp.setIntensity(0, 8); disp.clearDisplay(0);

			// initialize the encoder
		enc.write(0);

			// initialize button
		pinMode(BUTTON, INPUT_PULLUP);
		attachInterrupt(BUTTON - 2, buttonHandler, FALLING);

		for(int i = 0; i < ARRAY_SIZE; i++) {
			display_vars[i] = ' ';
			index_vars[i] = false;
		}
	}

		// returns the encoder value
	int getEncoder() {
		return readEncoderRelative();
	}

		// returns the number of button presses since last call, clears button press variable
	int getButtonPresses() {
		int button_press_holder = button_presses;
		button_presses = 0;
		return button_press_holder;
	}

		// returns the thermistor reading in *F
	int getTherm() {
		float F = analogRead(THERM);
		F = (RC * F) / (1023 - F);
		F = log(F / R0);
		F = 1 / (F / B + T0);
		return round(F * 1.8 - 459.67);
	}

	unsigned long getLastEvent() {
		return last_event;
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

		// toggle relay to turn circulators on
	void circOn() {
		circ_state = true;
		last_circ_action = millis();
		digitalWrite(RELAY, HIGH);
	}

		// toggle relay to turn circulators off
	void circOff() {
		circ_state = false;
		last_circ_action = millis();
		digitalWrite(RELAY, LOW);
	}

	bool getCircState() {
		return circ_state;
	}

	unsigned long getLastCircAction() {
		return last_circ_action;
	}

		// enable serial comms for debugging
	void serialEnable() {
		Serial.begin(BAUD);
	}

		// make sure to call serialEnable first...
	void serialWrite(String data) {
		Serial.println(data);
	}

};
