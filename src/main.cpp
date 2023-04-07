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
  //initHardware();
  // At this stage the system clock should have already been configured
  // at high speed.

  ReturnCode ret = RETURNCODE_UNKNOWN;

  GpioStruct ledPin;
  ledPin.port  = PORTSELECT_B;
  ledPin.pin   = PINSELECT_7;
  ledPin.mode  = MODESELECT_OUTPUT;
  ledPin.oType = OTYPESELECT_PP;
  ledPin.speed = SPEEDSELECT_FREQ_LOW;
  ret = GpioInit(ledPin);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  ret = GpioWrite(ledPin, PINSTATE_RESET);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  GpioStruct buttonPin;
  buttonPin.port  = PORTSELECT_C;
  buttonPin.pin   = PINSELECT_13;
  buttonPin.mode  = MODESELECT_INPUT;
  buttonPin.pull  = PULLSELECT_PULL_DOWN;
  ret = GpioInit(buttonPin);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }

  PinState pinState = PINSTATE_UNKNOWN;
  ret = GpioWrite(ledPin, PINSTATE_SET);
  if (ret != RETURNCODE_SUCCESS){
	  ErrorTrap();
  }
  while (1)
    {


	  // Send a greeting to the trace device (skipped on Release).
	  //trace_puts("Hello Arm World!");
	  //trace_puts("Turning on LED");
	  ret = GpioRead(buttonPin, &pinState);
	  if (ret != RETURNCODE_SUCCESS){
		  // TODO: handle error
	  }

	  if (pinState == PINSTATE_SET) {
		  GpioWrite(ledPin, PINSTATE_SET);
	  }
	  else{
		  GpioWrite(ledPin, PINSTATE_RESET);
	  }

    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
