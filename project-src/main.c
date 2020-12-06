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
#define LED_GREEN BIT6

short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  static int drawCnt = 0;


  switch(bState){
  case 2:
    if(drawCnt == 250){
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
  configureClocks();
  led_init();
  lcd_init();
  buzzer_init();
  p2sw_init(15);
  enableWDTInterrupts();/* enable periodic interrupt */
  or_sr(0x8);
  clearScreen(COLOR_WHITE);
  while (1) {           /* forever */
    if(redrawScreen){
      redrawScreen=0;
      if(bState==2){
	state_advance();
      }
      P1OUT &= ~LED_GREEN;/* green off */
      or_sr(0x10);/**< CPU OFF */
      P1OUT |= LED_GREEN;/* green on */
    }
  }
}
