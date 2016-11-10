#include "switch.h"
void EnableInterrupts(void);

void Switch_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x00000008; // (a) activate clock for port D
	while ((SYSCTL_RCGCGPIO_R & 0x08) != 0x08){ 		// do nothing
	}
  GPIO_PORTD_DIR_R &= ~0x03;    // (c) make PF4 in (built-in button)
  GPIO_PORTD_AFSEL_R &= ~0x03;  //     disable alt funct on PD4
  GPIO_PORTD_DEN_R |= 0x03;     //     enable digital I/O on PD4   
  GPIO_PORTD_AMSEL_R &= ~0x03;       //     disable analog functionality on PF
  GPIO_PORTD_PDR_R |= 0x03;     //     enable weak pull-up on PF4
  GPIO_PORTD_IS_R &= ~0x03;     // (d) PF4 is edge-sensitive
  GPIO_PORTD_IBE_R &= ~0x03;    //     PF4 is not both edges
  GPIO_PORTD_IEV_R &= 0x03;    //     PF4 falling edge event
  GPIO_PORTD_ICR_R = 0x03;      // (e) clear flag4
  GPIO_PORTD_IM_R |= 0x03;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI0_R = (NVIC_PRI7_R&0x1FFFFFFF)|0x40000000; // (g) priority 
  NVIC_EN0_R |= 0x03;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}

void GPIOPortD_Handler(void){
	if (GPIO_PORTD_RIS_R&0x01){
		GPIO_PORTD_ICR_R = 0x01;
	}
	else if (GPIO_PORTD_RIS_R&0x2) {
		GPIO_PORTD_ICR_R = 0x02;
	}
}
