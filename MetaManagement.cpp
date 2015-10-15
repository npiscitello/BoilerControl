#include "EEPROM.h"
#include "IO.h"



class MetaManagement {

	private:
			// define variables
		int relative_encoder;
		unsigned int vars[NUMVARS];
		long last_event, thresh_cross;
		bool above_thresh, prev_thresh, cross;

	public:
			// initialize
		void init() {
				// initialize working variables
			index = 0;  thresh_cross = 0;
				// eventually, retrieve variables from memory - for now, just default
			vars[THRESH_VAR] = 50;
			vars[ON_VAR] = 1; vars[OFF_VAR] = 2;
				// initial timing assignment
			circulator.setTiming(vars[ON_VAR], vars[OFF_VAR]);
			circulator.applyTiming();
		}

			// use variables to decide what to do with the circulator
		void execute() {
				// check threshold and enable or disable circulator as appropriate -
				// Only sends the command if the reading stays on the correct side of the threshold
				// for a certain amount of time
			if(interface.getTherm() > vars[THRESH_VAR]) {
				above_thresh = true;
			} else {
				above_thresh = false;
			}
			if(above_thresh != prev_thresh) {
				thresh_cross = millis();
				cross = true;
			}
			if(millis() - thresh_cross > THRESH_PAD && cross) {
				if(above_thresh) {
					circulator.enable();
					cross = false;
				} else {
					circulator.disable();
					cross = false;
				}
			}
			prev_thresh = above_thresh;

				// update variables in circulator object if either circulator variable was changed
			if(vars[ON_VAR] != circulator.getOnVar() || vars[OFF_VAR] != circulator.getOffVar()) {
				circulator.setTiming(vars[ON_VAR], vars[OFF_VAR]);
				circulator.applyTiming();
			}
		}

			// calculate and send output data to IO class
		void output() {
				// manage index value
			if(button_pressed) {
				index ++;
				if(index > NUMVARS - 1) {
					index -= NUMVARS;
				}
				last_event = millis();
				button_pressed = false;
			}
				// must read relative encoder value every iteration, otherwise the relative value
				// will store up when displaying temperature and adjust the next variable
				// when the user presses the button.
			relative_encoder = interface.getEncoder();
			if(relative_encoder != 0) {
				last_event = millis();
			}
			if(index == THERM_VAR) {
				vars[THERM_VAR] = interface.getTherm();
			} else {
				vars[index] += relative_encoder;
			}
				// handle limits - in base MAXDIG + 1
			if(vars[index] > (pow(MAXDIG + 1, NUMDIGS) - 1)) {
				vars[index] = (pow(MAXDIG + 1, NUMDIGS) - 1);
			} else if(vars[index] < 0) {
				vars[index] = 0;
			}
				// return to temperature display if nothing has happened in TIMEOUT ms
			if(millis() - last_event > TIMEOUT) {
				index = THERM_VAR;
			}
			interface.output(vars[index], index);
		}

};
