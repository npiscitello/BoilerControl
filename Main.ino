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
 *   \__________________________________________________________________/   */

#include "EEPROM.h"
#include "IO.h"

	// constant definitions
#define BAUD 57600			// serial comms baud rate (used for debugging)
#define MAXDIG 9			// largest number for one displayed digit
#define TEMP_DELAY 125		// in ms - delay between thermistor readings
#define OUTPUT_DELAY 50		// in ms - delay between display updates
#define TIMEOUT 10000		// in ms - delay before display returns to temperature
#define THRESH_PAD 10000	// in ms - time thermistor must stay on one side of threshold to trigger

	// define objects for each class
EEPROM memory;
IO inout;

// index values for various variables
#define THERM_VAR 0			// thermistor variable index location
#define ON_VAR 1			// circulator on duration variable index location
#define OFF_VAR 2			// circulator off duration variable index location
#define THRESH_VAR 3		// temperature threshold variable index location

	// variable declarations
unsigned int variables[4];	// holds current temperature, on and off times, threshold
unsigned int index;			// holds current selection in variable array
unsigned int temperature;	// holds current temperature in *F

void setup() {
		// initialize and enable IO and EEPROM objects
	memory.init();
	memory.enable();
	inout.init();
	inout.enable();

		// get variables from EEPROM
	variables = memory.read();	// make sure to update read function so it returns this type
}

void loop() {

		// update display every so often - later, only update display if something changes (if possible)
	if(millis%OUTPUT_DELAY == 0) {
		inout.output(variables[index], index);
	}

		// update thermistor value every so often - implement averaging if the value is very unstable...
	if(millis%TEMP_DELAY == 0) {
		temperature = inout.getTherm();
	}
}
