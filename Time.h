#include "math.h"

/** 
*@file Time.h 
*@brief this header file will contain all required 
*definitions and basic utilities functions for the Time class.
*@author J Marshall
*@date 
*/

// ----- Pre-processor -----

// PORTF 

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// Systick

#define NVIC_ST_CTRL_R			(*((volatile unsigned long *)0xE000E010)) 
#define NVIC_ST_RELOAD_R		(*((volatile unsigned long *)0xE000E014)) 
#define NVIC_ST_CURRENT_R		(*((volatile unsigned long *)0xE000E018))

// PLL

#define SYSCTL_RCC_R				(*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RIS_R				(*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RCC2_R				(*((volatile unsigned long *)0x400FE070))
	

//	Constant for generalised systick wait function 

#define TIME_CONST_US 1E6 
#define TIME_CONST_MS 1E3
	

// ----- Functions -----

/**
*This method initialises PORTF0-3 to engage on board LEDs and switches for testing purposes
*@author J Marshall
*@date October 31, 2018
*/

void Init_PORT_F(void);

/**
*This method initialises SYSTICK 16.0  MHz
*@author Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
*@date  November 10, 2013
*/

void Init_SysTick(void);

/**
*This method initialises PLL 80MHz
*@author J Marshall
* Modified from Embedded Systems - Shape The World, Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
* Chapter 10 online at http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C10_FiniteStateMachines.htm
*@param n A value between 4(80MHz) and 127(3.175MHz) to set frequency(f) where f = 400/(n-1)
*@date	October 31, 2018
*/

void Init_PLL(int n);

/**
*This is a function to set wait times based on a 80MHz clock and takes 1ms to execute
*@author J Marshall - Based on Embedded Systems - Shape The World Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
*Chapter 10 online at http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C10_FiniteStateMachines.htm
*@date	October 31, 2018
*/

void SysTick_Wait1ms(void);

/**
*This is a function to set wait times based on a 80MHz clock and takes 1us to execute
*@author J Marshall - Based on Embedded Systems - Shape The World Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi
*Chapter 10 online at http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C10_FiniteStateMachines.htm
*@date October 31, 2018
*/

void SysTick_Wait1us(void);

/**
*A function to allow the user to stipulate a wait
*@author J Marshall
*@date	October 31, 2018
*@param time any value between 1us 
*/

void SysTick_Wait(double time);



