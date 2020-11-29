//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "stateMachines.h"
#include <libTimer.h>
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"
#include <sr.h>


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  static int drawCnt = 0;

  secCount ++;
  drawCnt++;
  if (secCount == 1) { /* once/sec */
    secCount = 0;
    state_advance();
  }
  /*if (drawCnt == 225) {
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
    }*/
}


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  buzzer_init();
  enableWDTInterrupts();	/* enable periodic interrupt */
  p2sw_init(15);
  or_sr(0x8);		/* CPU off, GIE on */
  lcd_init();
  clearScreen(COLOR_WHITE);
  /*
  green_on=1; /**< Green led on when CPU on *
  led_changed=1;
  led_update();

  clearScreen(COLOR_BLUE);
  while (1) {/* forever *
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
    }
    green_on=0; /* green off *
    led_changed=1;
    led_update();
    or_sr(0x10);/**< CPU OFF *
    green_on=1; /* green on *
    led_changed=1;
    led_update();
  }
  */
}
