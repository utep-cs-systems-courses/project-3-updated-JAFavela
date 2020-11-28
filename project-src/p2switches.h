#ifndef switches_included
#define switches_included

#include "msp430.h"
#define SW1 BIT0		/* switch1 is p2.0 */
#define SW2 BIT1                /* switch2 is p2.1 */
#define SW3 BIT2                /* switch3 is p1.2 */
#define SW4 BIT3                /* switch4 is p0.3 */

#define SWITCHES (SW1 | SW2 | SW3 | SW4)		/* 4 switches */

extern char bState;
unsigned int p2sw_read();
void p2sw_init(unsigned char mask);

#endif // included
