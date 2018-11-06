#include "Time.h"

// ----- Initialisation Functions -----

void Init_PORT_F(void) {
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;			/* F clock	*/
  delay = SYSCTL_RCGC2_R;						/* delay	*/
  GPIO_PORTF_LOCK_R = 0x4C4F434B;		/* unlock PortF PF0	*/
  GPIO_PORTF_CR_R |= 0x1F;					/* allow changes to PF4-0	*/
  GPIO_PORTF_AMSEL_R &= ~0x0F;			/* disable analog function	*/
  GPIO_PORTF_PCTL_R &= ~0x0000FFFF;	/* GPIO clear bit PCTL	*/
  GPIO_PORTF_DIR_R |= 0x0E;					/* PF4,PF0 input, PF3,PF2,PF1 output	*/   
	GPIO_PORTF_DIR_R &= ~0x11;
  GPIO_PORTF_AFSEL_R &= ~0x1F;			/* no alternate function	*/
  GPIO_PORTF_PUR_R |= 0x11;					/* enable pullup resistors on PF4,PF0	*/       
  GPIO_PORTF_DEN_R |= 0x1F;					/* enable digital pins PF4-PF0	*/
}

void Init_SysTick(void){
  NVIC_ST_CTRL_R = 0;								/* disable SysTick during setup	*/
  NVIC_ST_RELOAD_R = 0x00FFFFFF;		/* maximum reload value	*/
  NVIC_ST_CURRENT_R = 0;						/* any write to current clears it	*/             
  NVIC_ST_CTRL_R = 0x00000005;			/* enable SysTick with core clock enable bit0 on, interrupt enable bit1 off, clock selection bit2 on	*/
}

void Init_PLL(int n){
  SYSCTL_RCC2_R |=  0x80000000;									/*	USERCC2	*/
  SYSCTL_RCC2_R |=  0x00000800;									/*	BYPASS2, PLL bypass while initialising	*/
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)		/*	clear XTAL field, bits 10-6	*/
                 + 0x00000540;									/*	10101, configure for 16 MHz crystal	*/
  SYSCTL_RCC2_R &= ~0x00000070;									/*	configure for main oscillator source	*/
  SYSCTL_RCC2_R &= ~0x00002000;									/*	activate PLL by clearing PWRDN	*/
  SYSCTL_RCC2_R |= 0x40000000;									/*	set the desired system divider use 400 MHz PLL	*/
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)	/*	clear system clock divider	*/
                  + (n<<22);      	
  while((SYSCTL_RIS_R&0x00000040)==0){};				/*	wait for the PLL to lock by polling PLLLRIS	*/
  SYSCTL_RCC2_R &= ~0x00000800;									/*	enable use of PLL by clearing BYPASS	*/
}

// ----- functions -----

void SysTick_Wait1us(void) {
	
	NVIC_ST_RELOAD_R = 80-1;	/* number of counts to wait 80 1us */
  NVIC_ST_CURRENT_R = 0;	/* any value written to CURRENT clears */
  while((NVIC_ST_CTRL_R&0x00010000)==0){	/* wait for count flag */

	}
}

void SysTick_Wait1ms(void) {
	
	NVIC_ST_RELOAD_R = 80000-1;	/* number of counts to wait */
  NVIC_ST_CURRENT_R = 0;	/* any value written to CURRENT clears */
  while((NVIC_ST_CTRL_R&0x00010000)==0){	/* wait for count flag */

	}
}

void SysTick_Wait(double time) {
	
	unsigned long i;
	
	//time *= TIME_CONST_US;	/*	convert into seconds */
	time *= TIME_CONST_MS;
	
	for(i=0;i<time;i++) {
		//SysTick_Wait1us();	/* executes 1million time per second */
		SysTick_Wait1ms();
	}

}
