#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"


char bState;
char first=0;


void siren()
{
  static int cyc = 4000;    /* 500Hz = 4000 cycles */
  static char state = 0;
  switch(state){            /* Switch with only 2 states */
  case 0:                   /* Going up with red led */
    buzzer_set_period(cyc); /* Set buzzer with current cycle value */
    cyc=cyc-180;             /* Decrement cycle by 180 = 1/20 steps towards 400(5000Hz) */
    if(cyc==220){           /* When limit is reached we set cycle to 400 and move to next state */
      cyc=400;
      state++;
    }
    break;
   case 1:                  /* Going down with green led */
     buzzer_set_period(cyc);
     cyc=cyc+360;            /* In this state we increment cycle by 360 = 1/10 steps back to 4000 */
     if(cyc==4360){         /* When limit is reached reset cycle to 4000 and loop back to state 0*/
      cyc=4000;
      state=0;
     }
  }
}

void dim_rg_led()
{
  static char ledState=0;
  switch(ledState){
  case 0:         /* leds are both off from 0-2 */
    red_on=0;
    ledState++;
    break;
  case 5:         /* leds are on at 3 */
    red_on=1;
    ledState=0;
    break;
  default:
    ledState++;
  }
  led_changed=1;
  led_update();
}

void litCop()
{
  static char lightState=0;
  switch(lightState){
  case 0:
    fillRectangle(0,85,65,20,COLOR_BLUE);
    fillRectangle(65,85,65,20,COLOR_WHITE);
    lightState++;
    break;
  case 20:
    fillRectangle(65,85,65,20,COLOR_RED);
    fillRectangle(0,85,65,20,COLOR_WHITE);
    lightState++;
    break;
  case 40:
    lightState=0;
    break;
  default:
    lightState++;
  }
}

void off()
{
  red_on=0;
  buzzer_set_period(0);
  led_changed=1;
  led_update();
  clearScreen(COLOR_WHITE);
  or_sr(~0x10);
  
}

void cop(){
  char i = 0;
  fillRectangle(0,105,128,10,COLOR_BLACK);
  for( ; i<6; i++){
    fillRectangle(123+i,115+i,5-i,1,COLOR_BLACK);
    fillRectangle(0,115+i,5-i,1,COLOR_BLACK);
  }
  fillRectangle(0,135,128,25,COLOR_BLACK);
  drawString8x12(5,145,"  ARCH. P.D.",COLOR_WHITE,COLOR_BLACK);
}

void state_advance()		
{
  static char copSt=0;
  static char sState=0;
  if(bState==0){
    if(copSt==0){
      cop();
      copSt=1;
    }
    dim_rg_led();
  }
  
  else if (bState == 1){
    static char space = 0;
    if (copSt == 1) {
      buzzer_set_period(0);
      copSt=2;
    }
    if(space<129){
      drawCar(space,20,COLOR_BLACK);
      space++;
    }
    else{
      sState=0;
      bState=2;
    }
    if(sState==0){
      led_switch(1);
      sState=1;
    }
    else{
      led_switch(0);
      sState=0;
    }
  }
  else if(bState==2){
    if(sState==5){
      siren();
      sState=0;
    }
    if(sState % 2){
      litCop();
    }
    sState++;
  }
  
  else if(bState==3){
    off();
  }
}
