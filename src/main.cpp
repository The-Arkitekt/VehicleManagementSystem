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

#include "STM32CommonLibrary_conf.h"
#include "Gpio.h"
#include "SystemConfig.h"
#include "Exti.h"


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

void ErrorTrap(){
	while(1){
		;
	}
}

/**
 * IRQ must b C
 */

#ifdef __cplusplus
	extern "C" {
#endif

void EXTI15_10_IRQHandler(){
	ExtiResetInterrupt(EXTI_LINESELECT_13);
	GpioPinState pinState = GPIO_PINSTATE_UNKNOWN;
	GpioRead(GPIO_PORTSELECT_B, GPIO_PINSELECT_7, &pinState);
	if (pinState == GPIO_PINSTATE_RESET){
		GpioWrite(GPIO_PORTSELECT_B, GPIO_PINSELECT_7, GPIO_PINSTATE_SET);
	}
	else{
		GpioWrite(GPIO_PORTSELECT_B, GPIO_PINSELECT_7, GPIO_PINSTATE_RESET);
	}
}

#ifdef __cplusplus
}
#endif



int main()
{
  ReturnCode ret = RETURNCODE_UNKNOWN;

////////////////////////////////////////////////////////////////
  /**
   * Basic GPIO
   */
  GpioConfigStruct ledPin;
  ledPin.port  = GPIO_PORTSELECT_B;
  ledPin.pin   = GPIO_PINSELECT_7;
  ledPin.mode  = GPIO_MODESELECT_OUTPUT;
  ledPin.oType = GPIO_OTYPESELECT_PP;
  ledPin.speed = GPIO_SPEEDSELECT_FREQ_LOW;
  ret = GpioInit(ledPin);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  ret = GpioWrite(ledPin.port, ledPin.pin, GPIO_PINSTATE_RESET);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  /**
   * EXTI Interrupt
   */
  // Enable Exti for Port C, Pin 13
  SysCfgEnableExti(GPIO_PORTSELECT_C, GPIO_PINSELECT_13);

  // Initialize Exti
  ExtiConfigStruct portCExti;
  portCExti.line           = EXTI_LINESELECT_13;
  portCExti.risingTrigger  = TRUE;
  portCExti.fallingTrigger = FALSE;
  ExtiInterruptInit(portCExti);

  GpioConfigStruct buttonPin;
  buttonPin.port    = GPIO_PORTSELECT_C;
  buttonPin.pin     = GPIO_PINSELECT_13;
  buttonPin.mode    = GPIO_MODESELECT_INPUT;			// Event Out Mode
  buttonPin.pull    = GPIO_PULLSELECT_PULL_DOWN;
  ret = GpioInit(buttonPin);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  // Enable IRQ
  enableExtiIrq(EXTI_IRQSELECT_15_10);
//////////////////////////////////////////////////////////////////////

  while (1)
  {}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
