/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "gpio.h"
#include "systemConfig.h"
#include "exti.h"


// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace-impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

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
