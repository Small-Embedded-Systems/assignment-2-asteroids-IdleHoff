/* Controller */

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"

/* Joystick 5-way switch
*/
typedef enum { left,down,right,up,centre } joystick_t;
DigitalIn joystick[] = {P5_0, P5_1, P5_4, P5_2, P5_3}; //left, down, right, up, center
static bool buttonPressedAndReleased(joystick_t button);


void controls(void)
{
		if(!paused){
			if (buttonPressedAndReleased(left)){
				rotateRight();
			}
			else if (buttonPressedAndReleased(down)){
				shipBack();
			}
			else if (buttonPressedAndReleased(right)){
				rotateLeft();
			}
			else if (buttonPressedAndReleased(up)){
				shipFwd();
			}
			else if (buttonPressedAndReleased(centre)){
				fire();
			}
		}
}

/*
 * @brief buttonPressedAndReleased(button) tests to see if the button has
 *        been pressed then released.
 *        
 * @param button - the name of the button
 * @result - true if button pressed then released, otherwise false
 *
 * If the value of the button's pin is 0 then the button is being pressed,
 * just remember this in savedState.
 * If the value of the button's pin is 1 then the button is released, so
 * if the savedState of the button is 0, then the result is true, otherwise
 * the result is false.
 */
bool buttonPressedAndReleased(joystick_t button) {
  bool result = false;
  uint32_t state;
  static uint32_t savedState[5] = {1,1,1,1,1};
  
  state = joystick[button].read();
    if ((savedState[button] == 0) && (state == 1)) {
    result = true;
  }
  savedState[button] = state;
  return result;
}
