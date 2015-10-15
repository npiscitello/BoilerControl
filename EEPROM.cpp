class EEPROM {

	private:
		// define variables
	bool enabled;

	public:
		void init() {
			enabled = false;
		}

		bool getEnabled() {
			return enabled;
		}

		void enable() {
			enabled = true;
		}

		void disable() {
			enabled = false;
		}

		void write() {
			// eventually take data and perform an update function -
			// use update method and wear leveling
		}

		void read() {
			// eventually return data to be used in variable initializaton
		}
};
