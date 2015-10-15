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
#define TEMP_READ 125		// in ms - delay between thermistor readings
#define OUTPUT_DELAY 50		// in ms - delay between display updates
#define TIMEOUT 10000		// in ms - delay before display returns to temperature
#define THRESH_PAD 10000	// in ms - time thermistor must stay on one side of threshold to trigger

	// define objects for each class
EEPROM memory;
IO inout;

void setup() {
		// initialize and enable IO and EEPROM objects
	memory.init();
	memory.enable();
	inout.init();
	inout.enable();
}

void loop() {

}
