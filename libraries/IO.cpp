/* This is the content for IO.h - see that file for a description of the class. */

#include <Arduino.h>
#include "IO.h"
#include "Encoder.h"
#include "LedControl.h"

	// define an LED driver chip
LedControl disp = LedControl(LED_DAT, LED_CLK, LED_SEL, 1);

	// define an encoder
Encoder enc = Encoder(ENC1, ENC2);

	// initialize IO values
void IO::init() {
		// initialize relay port
	pinMode(RELAY, OUTPUT);

		// wake up display driver, set brightness, and clear
	disp.shutdown(0, false); disp.setIntensity(0, INTENSITY); disp.clearDisplay(0);

		// initialize the encoder
	enc.write(0);
}

	// returns the encoder value
int IO::getEncoder() {
   		// this library registers 2 counts per "click", so adjust down to
   		// one count per "click" for intuitiveness
	enc_value = (enc.read())/2;
	if(enc_value != 0) {
		last_input_event = millis();
		enc.write(0);
	}
	return enc_value;
}

	// function for ISR - crudely debounced
void IO::buttonHandler() {
	if(millis() - last_input_event >= DEBOUNCE_TIME) {
		button_presses++;
	}
	last_input_event = millis();
}

	// returns the number of button presses since last call, clears button press variable
int IO::getButtonPresses() {
	int button_press_temp= button_presses;
	button_presses = 0;
	return button_press_temp;
}

	// returns the thermistor reading in *F
unsigned int IO::getTherm() {
	float F = analogRead(THERM);
	F = (RC * F) / (1023 - F);
	F = log(F / R0);
	F = 1 / (F / B + T0);
	return round(F * 1.8 - 459.67);
}

	// returns millis() output of last input for timeout calculations
unsigned long IO::getLastInputEvent() {
	return last_input_event;
}

	// display values - receives the number to be displayed and the index
void IO::output(int number_display, int index_display) {
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
void IO::circOn() {
	circ_state = true;
	last_circ_event = millis();
	digitalWrite(RELAY, HIGH);
}

	// toggle relay to turn circulators off
void IO::circOff() {
	circ_state = false;
	last_circ_event = millis();
	digitalWrite(RELAY, LOW);
}

	// returns circulator state
bool IO::getCircState() {
	return circ_state;
}

	// returns millis() output of last circulator on/off call
unsigned long IO::getLastCircAction() {
	return last_circ_event;
}

	// enable serial comms for debugging
void IO::serialEnable() {
	Serial.begin(BAUD);
}
