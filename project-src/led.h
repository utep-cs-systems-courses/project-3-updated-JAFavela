#ifndef led_included
#define led_included

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

extern unsigned char red_on, green_on;
extern unsigned char led_changed;

//short redrawScreen = 1;
//u_int fontFgColor = COLOR_GREEN;

void led_init();
void led_update();

#endif // included
