#ifndef stateMachine_included
#define stateMachine_included

void StateAdvanceCop();
void state_advance();
void siren();
void dim_rg_led();
void led_switch(char note);
void alternate_led();
void drawCorners();
void litCop();

static char state = 0;

#endif // included
