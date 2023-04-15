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

void ErrorTrap(){
	while(1){
		;
	}
}

int main()
{
  ReturnCode ret = RETURNCODE_UNKNOWN;

  GpioStruct ledPin;
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

  GpioStruct buttonPin;
  buttonPin.port  = GPIO_PORTSELECT_C;
  buttonPin.pin   = GPIO_PINSELECT_13;
  buttonPin.mode  = GPIO_MODESELECT_INPUT;
  buttonPin.pull  = GPIO_PULLSELECT_PULL_DOWN;
  ret = GpioInit(buttonPin);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  GpioPinState pinState = GPIO_PINSTATE_UNKNOWN;
  while (1)
    {

	  // enable port b pin 7 interrupt
	  ret = SysCfgEnableExti(SYSCFG_EXTI_CR2, GPIO_PORTSELECT_B, GPIO_PINSELECT_7);
	  if (ret != RETURNCODE_SUCCESS){
		  ErrorTrap();
	  }
	  // Send a greeting to the trace device (skipped on Release).
	  //trace_puts("Hello Arm World!");
	  //trace_puts("Turning on LED");
	  ret = GpioRead(buttonPin.port, buttonPin.pin, &pinState);
	  if (ret != RETURNCODE_SUCCESS){
		  // TODO: handle error
	  }

	  if (pinState == GPIO_PINSTATE_SET) {
		  GpioWrite(ledPin.port, ledPin.pin, GPIO_PINSTATE_RESET);
	  }
	  else{
		  GpioWrite(ledPin.port, ledPin.pin, GPIO_PINSTATE_SET);
	  }

    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
