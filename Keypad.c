#include "keypad.h"

void Init_Keypad_Rows(void) {

	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008;     	//	unlock clock for PORTD
  delay = SYSCTL_RCGC2_R;           	//	delay
  GPIO_PORTD_LOCK_R = 0x4C4F434B;   	//	unlock PORTD7
  GPIO_PORTD_CR_R |= 0x0F;           	//	allow changes to port PORTD0-3
  GPIO_PORTD_AMSEL_R &= ~0x0F;        //	disable analog function
  GPIO_PORTD_PCTL_R &= ~0x0000FFFF;   //	GPIO clear bit PCTL
  GPIO_PORTD_DIR_R &= ~0x0F;          //	PORTD0-3 inputs
  GPIO_PORTD_AFSEL_R &= ~0x0F;        //	no alternate function
  GPIO_PORTD_PUR_R |= 0x0F;          	//	enable pullup resistors on PORTD0-3
	GPIO_PORTD_PDR_R &= ~0x0F;					//	disable pulldown resistor on PORTD0
  GPIO_PORTD_DEN_R |= 0x0F;          	//	disable digital pins PD3-PD0
	
	
  GPIO_PORTD_IS_R &= ~0x1E;     											// PF1-4 are edge triggered
  GPIO_PORTD_IBE_R &= ~0x1E;   												//     PF1-4 triggered by either fall or rising edge
  GPIO_PORTD_IEV_R &= ~0x1E;    											//     PE1-4 triggered by falling edge
  GPIO_PORTD_ICR_R = 0x1E;      											// 		 clear flag PF1-4
  GPIO_PORTD_IM_R |= 0x1E;      											// 		 set interrupt for PE1-4
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000020; 	// 		 set priority (2)
  NVIC_EN0_R = 0x00000010;      											// 		 enable interrupt 4 in NVIC for portF see p104 table 2-9 interrupts - TM4C... data sheet
	
  //EnableInterrupts();           // (i) Enable global Interrupt flag (I)

}

void Init_Keypad_Columns(void) {

	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;     	//	unlock clock for PORTE
  delay = SYSCTL_RCGC2_R;           	//	delay
	GPIO_PORTE_LOCK_R = 0x4C4F434B;   	//	unlock PORTe
  GPIO_PORTE_CR_R |= 0x1E;           	//	allow changes to port PORTE1-4
  GPIO_PORTE_AMSEL_R &= ~0x1E;        //	disable analog function
  GPIO_PORTE_PCTL_R &= ~0x000FFFF0;   //	GPIO clear bit PCTL
  GPIO_PORTE_DIR_R |= 0x1E;          	//	PORTE1-4 outputs
  GPIO_PORTE_AFSEL_R &= ~0x1E;        //	no alternate function
	//GPIO_PORTE_PUR_R |= 0x1E;						//	enable pullup resistors on PORTE1-4
	//GPIO_PORTE_PDR_R &= ~0x1E;					//	disable pulldown resistor on PORTD0
  GPIO_PORTE_DEN_R |= 0x1E;          	//	enable digital pins PE4-PE1

}
/**
Test software
*/


void Init_Green_LED(void) {

	Init_PLL(4);
	Init_SysTick();
	
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     //	unlock clock for PORTD
  delay = SYSCTL_RCGC2_R;           //	delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   //	unlock PORTD
  GPIO_PORTF_CR_R |= 0x08;          //	allow changes to port PD3
  GPIO_PORTF_AMSEL_R &= ~0x08;      //	disable analog function PD3
  GPIO_PORTF_PCTL_R &= ~0x00000F00; //	GPIO clear bit PCTL
  GPIO_PORTF_DIR_R |= 0x08;         //	PD3 output
  GPIO_PORTF_AFSEL_R &= ~0x08;      //	no alternate function PD3
  GPIO_PORTF_PUR_R &= 0x08;        	//	disable pullup resistors on PD3
	GPIO_PORTF_PDR_R &= ~0x08;				//	disable pulldown resistor on PD3
  GPIO_PORTF_DEN_R |= 0x08;         //	enable digital pins PD3
	
}


void Toggle_Green(unsigned short n_flashes) {
	unsigned short i;
	if(i<n_flashes) {
	for(i = 0; i < n_flashes; i++) {
		
		Led_On();
		SysTick_Wait(0.5);
		Led_Off();
		SysTick_Wait(0.5);
		
	}
	
}
	
}

void Led_On(void) {
	
	GREEN_LED |= G_LED;
	
} 

void Led_Off(void) {
	
	GREEN_LED &= ~G_LED;
	
}

/**

pseudo code
PortD rows - inputs 
PortE columns - outputs

send LOW to COL pins one at a time
check for LOW signal on ROW pins one at a time
the ROW pin which is internally set to HIGH is connected to 
the COL pin which is LOW when the button is pressed, the ROW pin 
will then read a LOW if the button is pressed

*/
void Button_Test(void) {
	
	COLS |= COLS_HIGH; // set rows high
	COLS &= ~C1; // set row 1 low
	//COLS &= ~C2;
	//COLS &= ~C3;
	//COLS &= ~C4;
	
	if(ROW1 == 0) {
		
		Toggle_Green(1); // if low detected on col1 flash once
		
	}
	if(ROW2 == 0) {
		
		Toggle_Green(2);
		
	}
	if(ROW3 == 0) {
		
		Toggle_Green(3);
		
	}
	if(ROW4 == 0) {
		
		Toggle_Green(4);
		
	}
	
	else { 
		
		Led_Off();
		
	}
	
}
