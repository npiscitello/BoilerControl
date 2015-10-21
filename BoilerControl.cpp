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
#define MAXDIG 9					// largest number for one displayed digit
#define NUMDIGS 3					// number of digits in display
#define NUMVARS 4					// number of LEDs in display (also how many index locations)
#define TEMP_DELAY 125				// in ms - delay between thermistor readings
#define OUTPUT_DELAY 50				// in ms - delay between display updates
#define THRESH_DELAY 60000			// in ms - delay between threshold checks
#define TIMEOUT 10000				// in ms - delay before display returns to temperature
#define ON_OFF_CONV 60000			// conversion factor for ON and OFF variables to use in circulator
									// timing - converts display units to ms (currently minutes -> ms)
#define ALPHA 0.1					// alpha value for averaging function
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
int encoder;						// holds current encoder reading

	// instantiate classes
EEPROM memory;
IO inout;

// button ISR
void buttonISR() {
inout.buttonHandler();
}

void setup() {
		// initialize IO and EEPROM objects
	memory.init();
	inout.init();

		// initialize button - not in IO because interrupt requires it to be in main loop
	pinMode(BUTTON, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, FALLING);

		// get variables from EEPROM
	//variables = memory.read();	// make sure to update read function so it returns this type

		// eventually, retrieve variables from memory - for now, just default
	variables[THRESH_VAR] = 50;
	variables[ON_VAR] = 1; variables[OFF_VAR] = 2;
}

void loop() {
		// manage index value
	index += inout.getButtonPresses();
	if(index > NUMVARS - 1) {
		index -= NUMVARS;
	}

		// manage encoder input - read every loop to prevent accumulation during temperature display
		// test lower limit to ensure that the unsigned int doesn't roll over
	encoder = inout.getEncoder();
	if(index != TEMP_VAR && (variables[index] > 0 || (variables[index] == 0 && encoder >= 0))) {
		variables[index] += encoder;
	}

		// handle upper limit - in base MAXDIG + 1
	if(variables[index] > (pow(MAXDIG + 1, NUMDIGS) - 1)) {
		variables[index] = (pow(MAXDIG + 1, NUMDIGS) - 1);
	}

		// return to temperature display if nothing has happened in TIMEOUT ms
	if(millis() - inout.getLastInputEvent() > TIMEOUT) {
		index = TEMP_VAR;
	}

		// update temperature value every so often - using an exponential moving average to smooth the output
		// don't need to check for rolling over the variable because the board won't be active if the temperature is negative
	if(millis() % TEMP_DELAY == 0) {
		variables[TEMP_VAR] = (ALPHA * inout.getTherm()) + ONE_MIN_ALPHA * variables[TEMP_VAR];
	}

		// check threshold every so often - compare delay prevents bouncing
	if(millis() % THRESH_DELAY == 0) {
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
	}

		// update display every so often
	if(millis() % OUTPUT_DELAY == 0) {
		inout.output(variables[index], index);
	}
}
