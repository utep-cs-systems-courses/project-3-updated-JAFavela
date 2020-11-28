//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "stateMachines.h"
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 1) { /* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    state_advance();
  }
}


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();	/* enable periodic interrupt */

  or_sr(0x8);		/* CPU off, GIE on */

  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;

  clearScreen(COLOR_BLUE);
  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
    }
    P1OUT &= ~LED_GREEN;/* green off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED_GREEN;/* green on */
  }
}
