#include <msp430.h>
#include "stateMachines.h"
#include "led.h"

void led_switch(char note){
  if(note==0){
    red_on=1;
  }
  else{
    red_on=0;
  }
  led_changed=1;
  led_update();
}
