//#include "Time.h"
#include "Keypad.h"

int main(void) {
		
	Init_Keypad_Rows();
	Init_Keypad_Columns();
	//Init_PORT_F();
	//Init_PLL(4);
	//Init_SysTick();
	Init_Green_LED();
	

	
	while(1) {

		Button_Test();
		//Toggle_Green(4);
		
  }
	
}