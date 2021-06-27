#include <XInput.h>

// Check if PIN is LOW (PRESSED)
#define BT_START (!(PINB&(1<<3)))
#define BT_A (!(PIND&(1<<0)))
#define BT_B (!(PIND&(1<<1)))
#define BT_X (!(PIND&(1<<2)))
#define BT_Y (!(PIND&(1<<3)))
#define BT_LB (!(PIND&(1<<4)))
#define BT_RB (!(PINB&(1<<1)))
#define BT_LT (!(PIND&(1<<7)))
#define BT_RT (!(PINB&(1<<6)))
#define BT_BACK (!(PINB&(1<<2)))
#define BT_L3 (!(PINB&(1<<4)))
#define BT_R3 (!(PINB&(1<<5)))
#define BT_UP (!(PINF&(1<<7)))
#define BT_DOWN (!(PINF&(1<<6)))
#define BT_LEFT (!(PINF&(1<<5)))
#define BT_RIGHT (!(PINF&(1<<4)))
#define DP ((PINC&(1<<6)))

void setup() {
  // Axes
  DDRF  &= ~B11110000; // Set A0-A3 as inputs
  PORTF |=  B11110000; // Enable internal pull-up resistors

  // Buttons
  DDRD  &= ~B10011111; // Set PD0-PD4 and PD7 as inputs
  PORTD |=  B10011111; // Enable internal pull-up resistors
  DDRB  &= ~B01111110; // Set PB1-PB6 as inputs
  PORTB |=  B01111110; // Enable internal pull-up resistors

  // Slider for Ddpad or Lstick
  DDRC  &= ~B01000000; // Set Pin 5 as input
  PORTC |=  B01000000; // Enable internal pull-up resistor

  XInput.setAutoSend(false);

  XInput.begin();

}

void loop() {
  // Set buttons
  XInput.setButton( BUTTON_A, BT_A );
  XInput.setButton( BUTTON_B, BT_B );
  XInput.setButton( BUTTON_X, BT_X );
  XInput.setButton( BUTTON_Y, BT_Y );
  XInput.setButton( BUTTON_LB, BT_LB );
  XInput.setButton( BUTTON_RB, BT_RB );
  XInput.setButton( BUTTON_BACK, BT_BACK );
  XInput.setButton( BUTTON_START, BT_START );
  XInput.setButton( BUTTON_L3, BT_L3 );
  XInput.setButton( BUTTON_R3, BT_R3 );
  XInput.setButton( TRIGGER_LEFT, BT_LT );
  XInput.setButton( TRIGGER_RIGHT, BT_RT );

  if(DP) { // if set to D-pad
    XInput.setDpad(BT_UP, BT_DOWN, BT_LEFT, BT_RIGHT);
    XInput.setJoystick(JOY_LEFT, 0, 0);
  }
  else {
    XInput.setJoystick(JOY_LEFT, BT_UP, BT_DOWN, BT_LEFT, BT_RIGHT);
    XInput.setDpad(0, 0, 0, 0);
  }

  // Send out
  XInput.send();
}
