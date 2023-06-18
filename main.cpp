#include "boolean.h"
#include "exti.h"
#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "syscfg.h"

Boolean buttonFlag = FALSE;

/**
 * IRQ must be written in C
 */
#ifdef __cplusplus
	extern "C" {
#endif

void EXTI15_10_IRQHandler()
{
  EXTI_clear_pending_request(EXTI_LINE_13);

  Boolean pin_state = GPIO_get_pin_data(GPIO_B, GPIO_PIN_7);

  if (pin_state == FALSE)
  {
    GPIO_set_pin_data(GPIO_B, GPIO_PIN_7, TRUE);
  }
  else
  {
    GPIO_set_pin_data(GPIO_B, GPIO_PIN_7, FALSE);
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
  GPIO_PORT_ENUM      ledPort          = GPIO_B;
  GPIO_PIN_ENUM       ledPin           = GPIO_PIN_7;

  RCC_enable_AHB1(RCC_AHB1_GPIOB);
  GPIO_set_mode(ledPort, ledPin, GPIO_MODE_OUTPUT);
  GPIO_set_pin_data(ledPort, ledPin, FALSE);
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
  /**
   * EXTI Interrupt
   */
  // Enable Exti for Port C, Pin 13
  GPIO_PORT_ENUM      buttonPort          = GPIO_C;
  GPIO_PIN_ENUM       buttonPin           = GPIO_PIN_13;

  RCC_enable_AHB1(RCC_AHB1_GPIOC);
  GPIO_set_pull(buttonPort, buttonPin, GPIO_PULL_DOWN);

  RCC_enable_APB2(RCC_APB2_SYSCFG);
  SYSCFG_set_EXTI_source(SYSCFG_EXTI_LINE_13, SYSCFG_GPIO_PORT_C);

  // Initialize Exti
  EXTI_set_rising_trigger(EXTI_LINE_13, TRUE);
  EXTI_set_interrupt_source(EXTI_LINE_13, TRUE);

  // Enable IRQ
  NVIC_enable_IRQ(EXTI15_10_INTERRUPT);
//////////////////////////////////////////////////////////////////////

  while (1)
  {}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
