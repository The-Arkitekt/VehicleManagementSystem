#ifndef GPIO_H
#define GPIO_H

#include "gpioDef.h"

namespace VMS{

namespace GPIO{

class Gpio {
public:
	/**
	 * Constructor
	 * 	- Defaults mode as output
	 * 	- Defaults speed as fast
	 * 	- Defaults pull as pull up
	 */
	Gpio(const PORT::PortSelect& port, const PIN::PinSelect& bit, const PIN_MODE::ModeSelect& mode,
		 const PIN_SPEED::SpeedSelect& speed, const PIN_PULL::PullSelect& pull);

	/**
	 * Getters
	 */
	PORT::PortSelect       getPort()  const {return m_port;};
	PIN::PinSelect         getPin()   const {return m_pin;};
	PIN_MODE::ModeSelect   getMode()  const {return m_mode;};
	PIN_SPEED::SpeedSelect getSpeed() const {return m_speed;};
	PIN_PULL::PullSelect   getPull()  const {return m_pull;};

	bool isInitialized() const {return m_initialized;};
	/**
	 * Setters
	 */
	void setPort (const PORT::PortSelect& port);
	void setPin  (const PIN::PinSelect& pin);
	void setMode (const PIN_MODE::ModeSelect& mode);
	void setSpeed(const PIN_SPEED::SpeedSelect& speed);
	void setPull (const PIN_PULL::PullSelect& pull);

	void gpioWrite(const PIN::PinState) const;
	PIN::PinState gpioRead() const;

	/**
	 * Initialize the GPIO pin
	 */
	void init();

	/**
	 * deInitialize the GPIO so it is no longer useable until initialized again
	 */
	void deInit();

private:
	PORT::PortSelect       m_port;
	PIN::PinSelect         m_pin;
	PIN_MODE::ModeSelect   m_mode;
	PIN_SPEED::SpeedSelect m_speed;
	PIN_PULL::PullSelect   m_pull;
	bool                   m_initialized;
};

}

}

#endif //GPIO_H
