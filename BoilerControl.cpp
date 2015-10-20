/*    __________________________________________________________________    *
 *   /                                                                  \   *
 *  /          Boiler control code - Nick + Joe Piscitello 2015          \  *
 * (                                                                      ) *
 *  )   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   (  *
 * (                                                                      ) *
 *  )   Dependencies:                                                    (  *
 * (      - LedControl library: https://github.com/wayoda/LedControl      ) *
 *  )	  - Encoder library:                                             (  *
 * (             http://www.pjrc.com/teensy/td_libs_Encoder.html          ) *
 *  )     - TaskScheduler library:                                       (  *
 * (             http://playground.arduino.cc/Code/TaskScheduler          ) *
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

	// pin definition
#define BUTTON 11			// encoder button pin

	// constant definitions
#define MAXDIG 9			// largest number for one displayed digit
#define NUMDIGS 3			// number of digits in display
#define NUMVARS 4			// number of LEDs in display (also how many index locations)
#define TEMP_DELAY 125		// in ms - delay between thermistor readings
#define OUTPUT_DELAY 50		// in ms - delay between display updates
#define THRESH_DELAY 60000	// in ms - delay between threshold checks
#define TIMEOUT 10000		// in ms - delay before display returns to temperature

	// index values for various variables
#define THERM_VAR 0			// thermistor variable index location
#define ON_VAR 1			// circulator on duration variable index location
#define OFF_VAR 2			// circulator off duration variable index location
#define THRESH_VAR 3		// temperature threshold variable index location

	// variable declarations
unsigned int variables[4];		// holds current temperature, on and off times, threshold
unsigned int index;				// holds current selection in variable array
unsigned int temperature;		// holds current temperature in *F
bool above_thresh;				// stores the state of stove temperature comparison
int encoder_value;				// stores relative encoder value

	// instantiate classes
EEPROM memory;
IO inout;



// for button ISR
void buttonISR() {
	inout.buttonHandler();
}

void setup() {

		// initialize IO and EEPROM objects
	memory.init();
	inout.init();

		// initialize button - here because interrupt requires it
	pinMode(BUTTON, INPUT_PULLUP);
	attachInterrupt(BUTTON - 2, buttonISR, FALLING);

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
	encoder_value = inout.getEncoder();
	if(index == THERM_VAR) {
		variables[THERM_VAR] = temperature;
	} else {
		variables[index] += encoder_value;
	}

		// handle limits - in base MAXDIG + 1
	if(variables[index] > (pow(MAXDIG + 1, NUMDIGS) - 1)) {
		variables[index] = (pow(MAXDIG + 1, NUMDIGS) - 1);
	} else if(variables[index] < 0) {
		variables[index] = 0;
	}

		// return to temperature display if nothing has happened in TIMEOUT ms
	if(millis() - inout.getLastEvent() > TIMEOUT) {
		index = THERM_VAR;
	}

		// turn the circulators on/off if threshold is met
	if(above_thresh) {
			// if the circulators are on and they've been on for long enough...
		if(inout.getCircState() && (millis() - inout.getLastCircAction()) >= (variables[ON_VAR] * (unsigned int)60000)) {
			inout.circOff();
		} else if(!inout.getCircState() && (millis() - inout.getLastCircAction()) >= (variables[OFF_VAR] * (unsigned int)60000)) {
			inout.circOn();
		}
	}

		// check threshold every so often - compare delay prevents bouncing
	if(millis() % THRESH_DELAY == 0) {
		if(temperature > variables[THRESH_VAR]) {
			above_thresh = true;
		} else {
			above_thresh = false;
		}
	}

		// update display every so often - later, only update display if something changes (if possible)
	if(millis() % OUTPUT_DELAY == 0) {
		inout.output(variables[index], index);
	}

		// update thermistor value every so often - implement averaging if the value is very unstable...
	if(millis() % TEMP_DELAY == 0) {
		temperature = inout.getTherm();
	}
}
