/*    __________________________________________________________________    *
 *   /                                                                  \   *
 *  /          Boiler control code - Nick + Joe Piscitello 2015          \  *
 * (                                                                      ) *
 *  )   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   (  *
 * (                                                                      ) *
 *  )   Dependencies (included in repository):                           (  *
 * (      - LedControl library: https://github.com/wayoda/LedControl      ) *
 *  )	  - Encoder library:                                             (  *
 * (             http://www.pjrc.com/teensy/td_libs_Encoder.html          ) *
 *  )     - IO library - custom written for application                  (
 * (      - EEPROM library - custom written for application               )
 *  )                                                                    (  *
 * (    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    ) *
 *  )                                                                    (  *
 * (    Functions:                                                        ) *
 *  )     - Sense when the coal stove is hot                             (  *
 * (        - when hot, circulate the heating loops every so often        ) *
 *  )         to prevent freezing pipes                                  (  *
 * (                                                                      ) *
 *  )     - Display and take input                                       (  *
 * (        - coal stove temperature                                      ) *
 *  )       - rest time between circulation                              (  *
 * (        - duration of circulation                                     ) *
 *  )       - temperature threshold                                      (  *
 * (                                                                      ) *
 *  )     - turn off when inactive                                       (  *
 * (        - save settings to EEPROM (if changed) to be recovered        ) *
 *  )         at next boot                                               (  *
 * (                                                                      ) *
 *  )   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   (  *
 * (                                                                      ) *
 *  \    Is it ironic that this has a boilerplate comment at the top?    /  *
 *   \__________________________________________________________________/   *
 *   																		*/

#include "Arduino.h"
#include "EEPROM.h"
#include "IO.h"

	// pin definitions
#define BUTTON 3					// encoder button pin

	// constant definitions
#define MAXNUM 999					// largest displayable number
#define TEMP_DELAY 125				// in ms - delay between thermistor readings
#define OUTPUT_DELAY 50				// in ms - delay between display updates
#define THRESH_DELAY 60000			// in ms - delay between threshold checks
#define TIMEOUT 10000				// in ms - delay before display returns to temperature
#define HOLD_DELAY 3000				// in ms - how long the button must be held down to save values to EEPROM
#define FLASH_DELAY 250				// in ms - time between on/off in LED flash
#define TIME_THRESH 1				// in ms - fudge value to make periodic tasks more regular
#define ON_OFF_CONV 60000			// conversion factor for ON and OFF variables to use in circulator
									// timing - converts display units to ms (currently minutes -> ms)
#define ALPHA 0.1					// alpha value for averaging function - decrease for smoother operation
#define ONE_MIN_ALPHA 0.9			// 1 - alpha value for averaging function

	// index values for data variables
#define TEMP_VAR 0					// thermistor variable index location
#define ON_VAR 1					// circulator on duration variable index location
#define OFF_VAR 2					// circulator off duration variable index location
#define THRESH_VAR 3				// temperature threshold variable index location

	// variable declarations
unsigned int variables[NUMVARS];	// holds current temperature, on and off times, threshold
unsigned int index;					// holds current selection in variable array
bool above_thresh;					// holds the state of stove temperature comparison
int button_var;						// tells the code about the button state
int encoder;						// holds current encoder reading

	// instantiate classes
EEPROM memory;
IO inout;

void buttonPressISR() {
	if(digitalRead(BUTTON) == HIGH) {
		button_var = 'r';
	} else {
		button_var = 'p';
		inout.buttonHandler();
	}
}

void setup() {
		// initialize IO and EEPROM objects
	memory.init();
	inout.init();

		// initialize button - not in IO because interrupt requires it to be in main loop
	pinMode(BUTTON, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressISR, CHANGE);

		// get variables from EEPROM
	//variables = memory.read();	// make sure to update read function so it returns this type

		// eventually, retrieve variables from memory - for now, just default
	variables[THRESH_VAR] = 50;
	variables[ON_VAR] = 1; variables[OFF_VAR] = 2;

		// initialize variables
	index = 0;
	button_var = 'n';
}

void loop() {
		// deal with button stuff
	if(button_var == 'p') {
		if(millis() - inout.getLastButtonEvent() >= HOLD_DELAY) {
			if(millis() % FLASH_DELAY <= TIME_THRESH) {
				inout.setLEDState(!inout.getLEDState());
			}
		}
	} else if(button_var == 'r') {
		button_var = 'n';
		if(millis() - inout.getLastButtonEvent() >= HOLD_DELAY) {
			// save values
			inout.setLEDState(true);
		} else {
			index ++;
			if(index > NUMVARS - 1) {
				index -= NUMVARS;
			}
		}
	}

		// manage encoder input - read every loop to prevent accumulation during temperature display
		// and test limits (0-255, to fit in one byte to facilitate EEPROM storage)
	encoder = inout.getEncoder();
	if(index != TEMP_VAR && ((variables[index] > 0 && variables[index] < 255) ||\
			(variables[index] == 0 && encoder >= 0) || (variables[index] == 255 && encoder <= 0))) {
		variables[index] += encoder;
	}

		// return to temperature display if nothing has happened in TIMEOUT ms
	if(millis() - inout.getLastInputEvent() > TIMEOUT) {
		index = TEMP_VAR;
	}

		// update temperature value every so often - using an exponential moving average to smooth the output
		// don't need to check for rolling over the variable because the board won't be active if the temperature is negative
		// adjust for upper display limit
	if(millis() % TEMP_DELAY <= TIME_THRESH) {
		variables[TEMP_VAR] = (ALPHA * inout.getTherm()) + ONE_MIN_ALPHA * variables[TEMP_VAR];
		if(variables[TEMP_VAR] > MAXNUM) {
			variables[TEMP_VAR] = MAXNUM;
		}
	}

		// check threshold every so often - compare delay prevents bouncing
	if(millis() % THRESH_DELAY <= TIME_THRESH) {
		if(variables[TEMP_VAR] > variables[THRESH_VAR]) {
			above_thresh = true;
		} else {
			above_thresh = false;
		}
	}

		// turn the circulators on/off if threshold is met
	if(above_thresh) {
			// if the circulators are on and they've been on for long enough...
		if(inout.getCircState() && (millis() - inout.getLastCircAction()) >= (variables[ON_VAR] * (unsigned long)ON_OFF_CONV)) {
			inout.circOff();
			// if the circulators are off and they've been off for long enough...
		} else if(!inout.getCircState() && (millis() - inout.getLastCircAction()) >= (variables[OFF_VAR] * (unsigned long)ON_OFF_CONV)) {
			inout.circOn();
		}
	} else {
		inout.circOff();
	}

		// update display every so often
	if(millis() % OUTPUT_DELAY <= TIME_THRESH) {
		inout.output(variables[index], index);
	}
}
