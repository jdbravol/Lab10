#include "switch.h"
#include "motor.h"
#include "ScreenOut.h"
#include "tach.h"
#include "PLL.h"
#include "tm4c123gh6pm.h"


void EnableInterrupts(void);
void WaitForInterrupt(void);

//debug code

int main(void){           
  PLL_Init(Bus80MHz);              // 80 MHz clock
  PeriodMeasure_Init();            // initialize 24-bit timer0A in capture mode
	PWM0A_Init();
  while(1){
  }
}
