#ifndef GPIO_DEF_H
#define GPIO_DEF_H

/**
 * All definitions are coming for HAL for now
 *
 * If HAL is no longer used, this file will have it's own definitions
 */

#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"
#include "stdint.h"

namespace VMS{

namespace GPIO{

// custom types for type safety
typedef GPIO_TypeDef * PORT_TYPE;
typedef uint32_t CLK_ENABLE_MASK_TYPE;
typedef uint16_t PIN_TYPE;
typedef uint32_t MODE_TYPE;
typedef uint32_t SPEED_TYPE;
typedef uint32_t PULL_TYPE;

// constants
const uint8_t NUM_PORTS  = 11U;
const uint8_t NUM_PINS   = 16U;
const uint8_t NUM_MODES  = 12U;
const uint8_t NUM_SPEEDS = 4U;
const uint8_t NUM_PULLS  = 3U;

// Port Address constants
namespace PORT{

typedef enum{
	PORT_A = 0U,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_G,
	PORT_H,
	PORT_I,
	PORT_J,
	PORT_K
}PortSelect;

const PORT_TYPE PORTS[NUM_PORTS] = {
		GPIOA,
		GPIOB,
		GPIOC,
		GPIOD,
		GPIOE,
		GPIOF,
		GPIOG,
		GPIOH,
		GPIOI,
		GPIOJ,
		GPIOK
};

const CLK_ENABLE_MASK_TYPE CLK_ENABLE_MASKS[NUM_PORTS] = {
		RCC_AHB1ENR_GPIOAEN,
		RCC_AHB1ENR_GPIOBEN,
		RCC_AHB1ENR_GPIOCEN,
		RCC_AHB1ENR_GPIODEN,
		RCC_AHB1ENR_GPIOEEN,
		RCC_AHB1ENR_GPIOFEN,
		RCC_AHB1ENR_GPIOGEN,
		RCC_AHB1ENR_GPIOHEN,
		RCC_AHB1ENR_GPIOIEN,
		RCC_AHB1ENR_GPIOJEN,
		RCC_AHB1ENR_GPIOKEN
};

}

// Pin address constants
namespace PIN{

typedef enum{
	PIN_0 = 0U,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
	PIN_ALL,
}PinSelect;

const PIN_TYPE PINS[NUM_PINS+1] = {
		GPIO_PIN_0,		/* Select Pin 0    */
		GPIO_PIN_1,		/* Select Pin 1    */
		GPIO_PIN_2,		/* Select Pin 2    */
		GPIO_PIN_3,		/* Select Pin 3    */
		GPIO_PIN_4,		/* Select Pin 4    */
		GPIO_PIN_5,		/* Select Pin 5    */
		GPIO_PIN_6,		/* Select Pin 6    */
		GPIO_PIN_7,		/* Select Pin 7    */
		GPIO_PIN_8,		/* Select Pin 8    */
		GPIO_PIN_9,		/* Select Pin 9    */
		GPIO_PIN_10,	/* Select Pin 10   */
		GPIO_PIN_11,	/* Select Pin 11   */
		GPIO_PIN_12,	/* Select Pin 12   */
		GPIO_PIN_13,	/* Select Pin 13   */
		GPIO_PIN_14,	/* Select Pin 14   */
		GPIO_PIN_15,	/* Select Pin 15   */
		GPIO_PIN_All	/* Select All Pins */
};

// Pin State values
typedef enum
{
  RESET = GPIO_PinState::GPIO_PIN_RESET,
  SET   = GPIO_PinState::GPIO_PIN_SET
}PinState;

}

// Pin Mode Constants
namespace PIN_MODE{

typedef enum{
	INPUT = 0U,
	OUTPUT_PP,
	OUTPUT_OD,
	AF_PP,
	AF_OD,
	ANALOG,
	IT_RISING,
	IT_FALLING,
	IT_RISING_FALLING,
	EVT_RISING,
	EVT_FALLING,
	EVT_RISING_FALLING
}ModeSelect;

const MODE_TYPE MODES[NUM_MODES] = {
		GPIO_MODE_INPUT,             /*!< Input Floating Mode                */
		GPIO_MODE_OUTPUT_PP,         /*!< Output Push Pull Mode              */
		GPIO_MODE_OUTPUT_OD,         /*!< Output Open Drain Mode             */
		GPIO_MODE_AF_PP,             /*!< Alternate Function Push Pull Mode  */
		GPIO_MODE_AF_OD,             /*!< Alternate Function Open Drain Mode */
		GPIO_MODE_ANALOG,            /*!< Analog Mode */
		GPIO_MODE_IT_RISING,         /*!< External Interrupt Mode with Rising edge trigger detection         */
		GPIO_MODE_IT_FALLING,        /*!< External Interrupt Mode with Falling edge trigger detection        */
		GPIO_MODE_IT_RISING_FALLING, /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
		GPIO_MODE_EVT_RISING,        /*!< External Event Mode with Rising edge trigger detection         */
		GPIO_MODE_EVT_FALLING,       /*!< External Event Mode with Falling edge trigger detection        */
		GPIO_MODE_EVT_RISING_FALLING /*!< External Event Mode with Rising/Falling edge trigger detection */
};

}

// Pin Speed Constants
namespace PIN_SPEED{

typedef enum{
	FREQ_LOW = 0U,
	FREG_MED,
	FREQ_HIGH,
	FREQ_VERY_HIGH
}SpeedSelect;

const SPEED_TYPE SPEEDS[NUM_SPEEDS] = {
		GPIO_SPEED_FREQ_LOW,      /*!< IO works at 2 MHz, please refer to the product datasheet */
		GPIO_SPEED_FREQ_MEDIUM,    /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
		GPIO_SPEED_FREQ_HIGH,      /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
		GPIO_SPEED_FREQ_VERY_HIGH /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */
};

}

namespace PIN_PULL{

typedef enum{
	NO_PULL = 0U,
	PULL_UP,
	PULL_DOWN,
}PullSelect;

const PULL_TYPE
 PULLS[NUM_PULLS] = {
		GPIO_NOPULL,  /*!< No Pull-up or Pull-down activation  */
		GPIO_PULLUP,  /*!< Pull-up activation                  */
		GPIO_PULLDOWN /*!< Pull-down activation                */
};

}

}

}

#endif //GPIO_DEF_H
