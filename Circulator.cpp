class Circulator {

	private:
			// define variables
		unsigned int on_duration, off_duration;

	public:
			// initialize
		void init() {
			// durations will be retrieved from memory and set by MetaManagement
		}

			//return on or off duration variable values
		int getOnVar() {
			return on_duration;
		}

		int getOffVar() {
			return off_duration;
		}

			// update circulator timing when asked
		void setTiming(int on, int off) {
			on_duration = on;
			off_duration = off;
		}

			// apply timing variable updates
		void applyTiming() {
			circOffTask.setInterval(on_duration*60000);
			circTask.setInterval((off_duration*60000) + (on_duration*60000));
		}

			// toggle relay to turn circulators on
		void turnOn() {
			digitalWrite(RELAY, HIGH);
		}

			// toggle relay to turn circulators off
		void turnOff() {
			digitalWrite(RELAY, LOW);
		}

			// start timing and powering circulators - also, apply timing changes
		void enable() {
			circTask.enable();
		}

			// stop the timing code, turn off circulators
		void disable() {
			circTask.disable();
			turnOff();
		}
};
