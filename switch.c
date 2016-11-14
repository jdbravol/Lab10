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
	SYSCTL_RCGCGPIO_R |= 0x00000002; // (a) activate clock for port F
	while ((SYSCTL_RCGCGPIO_R & 0x02) != 0x02){ 		// do nothing
	}
  GPIO_PORTB_DIR_R &= ~0x18;    // (c) make PF4 in (built-in button)
  GPIO_PORTB_AFSEL_R &= ~0x18;  //     disable alt funct on PF4
  GPIO_PORTB_DEN_R |= 0x18;     //     enable digital I/O on PF4   
  GPIO_PORTB_PCTL_R &= ~0x0F00FFF0; // configure PF4 as GPIO
  GPIO_PORTB_AMSEL_R = 0xC;       //     disable analog functionality on PF
  GPIO_PORTB_PDR_R |= 0x18;     //     enable weak pull-up on PF4
  GPIO_PORTB_IS_R &= ~0x18;     // (d) PF4 is edge-sensitive
  GPIO_PORTB_IBE_R &= ~0x18;    //     PF4 is not both edges
  GPIO_PORTB_IEV_R &= ~0x18;    //     PF4 falling edge event
  GPIO_PORTB_ICR_R = 0x18;      // (e) clear flag4
  GPIO_PORTB_IM_R |= 0x18;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI0_R = (NVIC_PRI7_R&0xFFFF00FF)|0x0000A000; // (g) priority 
  NVIC_EN0_R = 0x02;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPORTB_Handler(void) {
	//A0 turns off timer
	Debounce();
	
	if ((GPIO_PORTB_RIS_R& 0x40) == 0x40) {
		GPIO_PORTB_ICR_R = 0x40;

		PD0Press();
	}
	// set hours
	else if ((GPIO_PORTB_RIS_R& 0x08) == 0x08) {
		GPIO_PORTB_ICR_R = 0x08;
		PD1Press();
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
	old = GPIO_PORTB_DATA_R;
  time = 40000; // 10 ms
	NVIC_EN0_R &= ~0x08;      // (h) enable interrupt 30 in NVIC
  while(time){
		in = GPIO_PORTB_RIS_R;
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
