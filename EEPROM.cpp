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
};
