#include "boolean.h"
#include "gpio.h"
#include "systemConfig.h"
#include "exti.h"

Boolean buttonFlag = FALSE;

/**
 * IRQ must b C
 */

#ifdef __cplusplus
	extern "C" {
#endif

void EXTI15_10_IRQHandler()
{
	clearPendingExtiLineInterruptRequest(13U);

  GpioPinState pinState = GPIO_get_pin_state(GPIO_PORT_B, GPIO_PIN_7);

  if (pinState == GPIO_PINSTATE_RESET)
  {
    GPIO_set_pin_state(GPIO_PORT_B, GPIO_PIN_7, GPIO_PINSTATE_SET);
  }
  else
  {
    GPIO_set_pin_state(GPIO_PORT_B, GPIO_PIN_7, GPIO_PINSTATE_RESET);
  } 
}

#ifdef __cplusplus
}
#endif

int main()
{
////////////////////////////////////////////////////////////////
  /**
   * Basic GPIO
   */
  GpioPortSelect      ledPort          = GPIO_PORTSELECT_B;
  BYTE_TYPE           ledPin           = 7U;
  GPIO_TypeDef* const ledPortStructPtr = getGpioPort(ledPort);

  GpioConfigStruct led = GpioConfigStruct_default;
  led.port = GPIO_PORT_B;
  led.pin  = GPIO_PIN_7;
  led.mode = GPIO_MODE_OUTPUT;

  GPIO_enable(led.port);
  GPIO_set_config(led);
  GPIO_set_pin_state(led.port, led.pin, GPIO_PINSTATE_RESET);
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  /**
   * EXTI Interrupt
   */
  // Enable Exti for Port C, Pin 13
  GpioPortSelect      buttonPort          = GPIO_PORTSELECT_C;
  BYTE_TYPE           buttonPin           = 13U;
  GPIO_TypeDef* const buttonPortStructPtr = getGpioPort(buttonPort);

  gpioEnable(buttonPort);
  setGpioConfig(buttonPortStructPtr, buttonPin, GPIO_PULL_UP_DOWN, 2U); // Set pull-down resistor

  systemConfigEnable();
  setSystemExternalInterruptSource(buttonPort, buttonPin);

  // Initialize Exti
  setExtiLineTrigger(buttonPin, EXTI_RISING_TRIGGER, TRUE);
  setExtiLineInterruptMask(buttonPin, TRUE);

  // Enable IRQ
  enableExtiIrq(EXTI_IRQSELECT_15_10);
//////////////////////////////////////////////////////////////////////

  while (1)
  {}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
