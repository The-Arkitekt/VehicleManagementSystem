/*
 * Gpio.cpp
 *
 *  Created on: Mar 19, 2023
 *      Author: architect
 */
#include "Gpio.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

namespace VMS{

namespace GPIO{

/**
 * Initialize member variables
 */
Gpio::Gpio(const PORT::PortSelect& port, const PIN::PinSelect& pin, const PIN_MODE::ModeSelect& mode,
		   const PIN_SPEED::SpeedSelect& speed, const PIN_PULL::PullSelect& pull) :
		   m_initialized{false}
{
	setPort (port);
	setPin  (pin);
	setMode (mode);
	setSpeed(speed);
	setPull (pull);
}

void Gpio::setPort(const PORT::PortSelect& port){

	if(m_initialized)
		deInit();

	m_port = port;
}

void Gpio::setPin(const PIN::PinSelect& pin){

	if(m_initialized)
		deInit();

	m_pin = pin;
}

void Gpio::setMode(const PIN_MODE::ModeSelect& mode){

	if(m_initialized)
		deInit();

	m_mode = mode;
}

void Gpio::setSpeed(const PIN_SPEED::SpeedSelect& speed){

	if(m_initialized)
		deInit();

	m_speed = speed;
}

void Gpio::setPull(const PIN_PULL::PullSelect& pull){

	if(m_initialized)
		deInit();

	m_pull = pull;
}

void Gpio::gpioWrite(const PIN::PinState value) const{
	GPIO_PinState pinOut;
	if (value == PIN::PinState::SET)
		pinOut = GPIO_PinState::GPIO_PIN_SET;
	else
		pinOut = GPIO_PinState::GPIO_PIN_RESET;

	HAL_GPIO_WritePin(PORT::PORTS[m_port], PIN::PINS[m_pin], pinOut);
}

PIN::PinState Gpio::gpioRead() const{
	GPIO_PinState pinOut = HAL_GPIO_ReadPin(PORT::PORTS[m_port], PIN::PINS[m_pin]);
	return (pinOut == GPIO_PinState::GPIO_PIN_SET) ? PIN::PinState::SET : PIN::PinState::RESET;
}

void Gpio::init(){
	// Dont initialize if invalid or already initialized
	if(m_initialized){;
		return;
	}

	// Enable GPIO Peripheral clock
	RCC->AHB1ENR |= PORT::CLK_ENABLE_MASKS[m_port];

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.Pin   = PIN::PINS[m_pin];
	GPIO_InitStructure.Mode  = PIN_MODE::MODES[m_mode];
	GPIO_InitStructure.Speed = PIN_SPEED::SPEEDS[m_speed];
	GPIO_InitStructure.Pull  = PIN_PULL::PULLS[m_pull];

	HAL_GPIO_Init(PORT::PORTS[m_port], &GPIO_InitStructure);

	m_initialized = true;
}

void Gpio::deInit(){
	// dont deinitialize if not already initialized
	if(!m_initialized)
		return;

	HAL_GPIO_DeInit(PORT::PORTS[m_port], PIN::PINS[m_pin]);

	m_initialized = false;
}

}

}

