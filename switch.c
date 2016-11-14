// Switch.c
// Runs on TM4C123
// (Description goes Here)
// Juan david Bravo , Justin
// September 14, 2016
#include "Switch.h"
#define D_RIS (*((volatile uint32_t*)0x40007414))
#define PE2 (*((volatile uint32_t*)0x40008010))

//mode defines the current functionality:
// 0 is Clock
// 1 is set alarm
// 2 is stopwatch

void EnableInterrupts(void);


void Switch_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x00000004; // (a) activate clock for port F
	while ((SYSCTL_RCGCGPIO_R & 0x04) != 0x04){ 		// do nothing
	}
  GPIO_PORTC_DIR_R &= ~0x0C;    // (c) make PF4 in (built-in button)
  GPIO_PORTC_AFSEL_R &= ~0x0C;  //     disable alt funct on PF4
  GPIO_PORTC_DEN_R |= 0x0C;     //     enable digital I/O on PF4   
  GPIO_PORTC_PCTL_R &= ~0x0F00FFF0; // configure PF4 as GPIO
  GPIO_PORTC_AMSEL_R = 0xC;       //     disable analog functionality on PF
  GPIO_PORTC_PUR_R |= 0x0C;     //     enable weak pull-up on PF4
  GPIO_PORTC_IS_R &= ~0x0C;     // (d) PF4 is edge-sensitive
  GPIO_PORTC_IBE_R &= ~0x0C;    //     PF4 is not both edges
  GPIO_PORTC_IEV_R &= ~0x0C;    //     PF4 falling edge event
  GPIO_PORTC_ICR_R = 0x0C;      // (e) clear flag4
  GPIO_PORTC_IM_R |= 0x0C;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI0_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 
  NVIC_EN0_R = 0x04;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPORTC_Handler(void) {
	//A0 turns off timer
	Debounce();
	
	if ((GPIO_PORTC_RIS_R& 0x40) == 0x40) {
		GPIO_PORTC_ICR_R = 0x40;

		PD0Press();
	}
	// set hours
	else if ((GPIO_PORTC_RIS_R& 0x02) == 0x02) {
		GPIO_PORTC_ICR_R = 0x02;
		PD1Press();
	}
	// set minutes
	else if ((GPIO_PORTC_RIS_R& 0x04) == 0x04) {
		GPIO_PORTC_ICR_R = 0x04;
		PD2Press();
	}
	else if ((GPIO_PORTC_RIS_R& 0x08) == 0x08) {
		GPIO_PORTC_ICR_R = 0x08;
		PD3Press();
	}
}

void PD0Press(void) {

}

void PD1Press(void) {
}

void PD2Press(void) {
	
}

void PD3Press(void) {
	
}

void Debounce(void) {
	uint32_t time, in, old;
	old = GPIO_PORTC_DATA_R;
  time = 40000; // 10 ms
	NVIC_EN0_R &= ~0x08;      // (h) enable interrupt 30 in NVIC
  while(time){
		in = GPIO_PORTC_RIS_R;
		if (old == in) {
			time--;
		}
		else {
			time = 40000;
			old = in;
		}
  }
	NVIC_EN0_R |= 0x08;
}
