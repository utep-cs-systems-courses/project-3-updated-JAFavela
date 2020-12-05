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

void wdt_c_handler()
{
  static int secCount = 0;
  static int drawCnt = 0;

 
  switch(bState){
  case 2:
    if(drawCnt == 225){
      redrawScreen = 1;
      drawCnt=0;
    }
    drawCnt++;
    break;
  default:
    if(secCount == 1) {
      secCount = 0;
      state_advance();
    }
    secCount++;
  }
}

int main(void) {
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  buzzer_init();
  enableWDTInterrupts();/* enable periodic interrupt */
  p2sw_init(15);
  or_sr(0x8);
  lcd_init();
  clearScreen(COLOR_WHITE);
  while (1) {           /* forever */
    if(bState==2){
      if(redrawScreen){
	redrawScreen=0;
	state_advance();
      }
      P1OUT &= ~LED_RED;/* red off */
      or_sr(0x10);/**< CPU OFF */
      P1OUT |= LED_RED;/* red on */
    }
  }
}
