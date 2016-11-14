// Switch.h
// Runs on TM4C123
// (Description goes Here)
// Juan david Bravo , Justin
// September 14, 2016
#include <stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"


/*Switch init
*This function will enable ports D0, D1, and D2, D6 
*for input operations,
*and enable interrupts
*/
void Switch_Init(void);
/*GPIOPoratA_Handler
*This function provides functionality for button presses
*A0 will turn off the alarm
*A1 will
*A2 will
*/
void GPIOPortA_Handler(void);

void PD0Press(void);

void PD1Press(void);

void PD2Press(void);

void PD3Press(void);

void Debounce(void);
