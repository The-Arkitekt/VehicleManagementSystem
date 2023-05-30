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
	clearPendingExtiLineInterruptRequest(EXTI_LINESELECT_13);

  GPIO_TypeDef* const gpioPtr = getGpioPort(GPIO_PORTSELECT_B);
  BYTE_TYPE pin = 7U;

  Boolean pinState = FALSE;
	Boolean success = readGpioPinValue(gpioPtr, pin, &pinState);
  if (success == TRUE)
  {
    if (pinState == FALSE)
    {
      setGpioPinValue(gpioPtr, pin, TRUE);
    }
    else
    {
      setGpioPinValue(gpioPtr, pin, FALSE);
    }
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

  gpioEnable(ledPort);
  setGpioConfig(ledPortStructPtr, ledPin, GPIO_MODE, 1U); // Set pin as output
  setGpioPinValue(ledPortStructPtr, ledPin, FALSE);
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  /**
   * EXTI Interrupt
   */
  // Enable Exti for Port C, Pin 13
  GpioPortSelect      buttonPort          = GPIO_PORT_SELECT_C;
  BYTE_TYPE           buttonPin           = 13U;
  GPIO_TypeDef* const buttonPortStructPtr = getGpioPort(buttonPort);

  gpioEnable(buttonPort);
  setGpioConfig(buttonPortStructPtr, buttonPin, GPIO_PULL_UP_DOWN, 2U); // Set pull-down resistor

  systemConfigEnable();
  setSystemExternalInterruptSource(buttonPort, buttonPin);

  // Initialize Exti
  extiEnable();
  setExtiLineTrigger(buttonPin, EXTI_RISING_TRIGGER);
  setExtiLineInterruptMask(buttonPin, TRUE);

  // Enable IRQ
  enableExtiIrq(EXTI_IRQSELECT_15_10);
//////////////////////////////////////////////////////////////////////

  while (1)
  {}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
