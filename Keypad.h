#include "Time.h"
/** 
*@file Keypad.h 
*@brief this header file will contain all required 
*definitions and basic utilities functions for the keypad class.
*
*@author J Marshall
*
*@date 
*/

//	-----	Pre-processor	-----

//	PORTD Rows

#define GPIO_PORTD_DATA_R 	(*((volatile unsigned long *)0x400073FC))	//	data register
#define ROWS								(*((volatile unsigned long *)0x4000703C))
#define ROW4								(*((volatile unsigned long *)0x40007004))	//	activate PD0
#define ROW3								(*((volatile unsigned long *)0x40007008))	//	activate PD1	
#define ROW2								(*((volatile unsigned long *)0x40007010)) //	activate PD2
#define ROW1								(*((volatile unsigned long *)0x40007020))	//	activate PD3
#define GPIO_PORTD_DIR_R 		(*((volatile unsigned long *)0x40007400))	//	direction register input/output
#define GPIO_PORTD_AFSEL_R 	(*((volatile unsigned long *)0x40007420))	//	alternate function select
#define GPIO_PORTD_PUR_R 		(*((volatile unsigned long *)0x40007510))	//	pull up resistor
#define GPIO_PORTD_PDR_R		(*((volatile unsigned long *)0x40007514))	//	pull down resistor
#define GPIO_PORTD_DEN_R 		(*((volatile unsigned long *)0x4000751C))	//	digital enable
#define GPIO_PORTD_LOCK_R		(*((volatile unsigned long *)0x40007520))	//	lock register for PROTE0
#define GPIO_PORTD_CR_R 		(*((volatile unsigned long *)0x40007524))	//	control register
#define GPIO_PORTD_AMSEL_R 	(*((volatile unsigned long *)0x40007528))	//	analog mode select
#define GPIO_PORTD_PCTL_R		(*((volatile unsigned long *)0x4000752C))	//	port control
	
//	PORTE Columns

#define GPIO_PORTE_DATA_R 	(*((volatile unsigned long *)0x400243FC))
#define COLS								(*((volatile unsigned long *)0x40024078))
#define COL4								(*((volatile unsigned long *)0x40024008))	//	activate PE1
#define COL3								(*((volatile unsigned long *)0x40024010))	//	activate PE2	
#define COL2								(*((volatile unsigned long *)0x40024020)) //	activate PE3
#define COL1								(*((volatile unsigned long *)0x40024040))	//	activate PE4
#define GPIO_PORTE_DIR_R 		(*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R 	(*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R 		(*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_PDR_R		(*((volatile unsigned long *)0x40024514))	//	pull down resistor
#define GPIO_PORTE_DEN_R 		(*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R		(*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R 		(*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R 	(*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R		(*((volatile unsigned long *)0x4002452C))

// PORTE interrupts

#define GPIO_PORTD_IS_R 		(*((volatile unsigned long *)0x40007404)) // interrupt sense (1) detect levels (0) detect edges
#define GPIO_PORTD_IBE_R		(*((volatile unsigned long *)0x40007408)) //`interrupt both edges (1) allows both rising and falling edges to trigger 
																																			// (0) allows IEV register to control rising or falling edges
#define GPIO_PORTD_IEV_R		(*((volatile unsigned long *)0x4000740C))	// interrupt event (1) trigger on rising (0) trigger on falling
#define GPIO_PORTD_ICR_R		(*((volatile unsigned long *)0x4000741C))	// interrupt clear 
#define GPIO_PORTD_IM_R			(*((volatile unsigned long *)0x40007410))	// interrupt mask (1) allows interrupts to be sent to combined interrupt controller
#define NVIC_PRI1_R					(*((volatile unsigned long *)0xE000E404)) // pirority 7bit bit 1 most bit 7 least
#define NVIC_EN0_R					(*((volatile unsigned long *)0xE000E100)) // enable interrupts

//	PORTF
	
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))	//	direction register input/output
#define GREEN_LED								(*((volatile unsigned long *)0x40025020))	//	activate PF3
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))	//	alternate function select
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))	//	pull up resistor
#define GPIO_PORTF_PDR_R				(*((volatile unsigned long *)0x40025514))	//	pull down resistor
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))	//	digital enable
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))	//	lock register for PORTF
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))	//	control register
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))	//	analog mode select
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))	//	port control
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108)) //	clock register
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

//	Clock Register

#define SYSCTL_RCGC2_R      (*((volatile unsigned long *)0x400FE108))
	
// Masks

#define ROWS_HIGH 0x0F
#define R1 0x08
#define R2 0x04
#define R3 0x02
#define R4 0x01

#define COLS_HIGH 0x1E
#define C1 0x10
#define C2 0x08
#define C3 0x04
#define C4 0x02

#define G_LED 0x08


// ----- Functions -----

/**
*This method initialises port D
*@brief Initialises PORTD0-3 as to be inputs connected to the rows of the 4x4 keypad
*@author J Marshall
*@date Octobber 31, 2018
*/

void Init_Keypad_Rows(void);

/**
*This method initialises port E
*@brief Initialises PORTE0-3 as outputs HIGH (pull up) to be connected to the columns of the 4x4 keypad
*@author J Marshall
*@date October 31, 2018
*/

void Init_Keypad_Columns(void);

void Init_Green_LED(void);

/** This method flashes the green onboard led a specified number of times
*@author J Marshall
*@param number of required flashes
*@date November 3, 2018
*/

void Toggle_Green(unsigned short n_flashes);

/** Switches the green led on
*@author J Marshall
*@date November 3, 2018 
*/

void Led_On(void);

/** Switches the green led off
*@author J Marshall
*@date November 3, 2018
*/

void Led_Off(void);

/** Tests buttons if pressed green led turns on for 0.5 seconds
*@author J Marshall
*@date November 4, 2018
*/

void Button_Test(void);


