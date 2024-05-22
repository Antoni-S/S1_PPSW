#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"


void Automat() {
	enum LedState{WAITING, LEFT, RIGHT};
	static enum LedState eLedState = WAITING;

	switch(eLedState) {
		case WAITING:
			if(eKeyboardRead() == BUTTON_0) {
				eLedState = LEFT;
			} else if(eKeyboardRead() == BUTTON_2) {
				eLedState = RIGHT;
			} else {
				eLedState = WAITING;
			}
			break;
		case LEFT:
			if(eKeyboardRead() == BUTTON_1) {
					eLedState = WAITING;
			} else {
				eLedState = LEFT;
			}
			LedStepLeft();
			break;
		case RIGHT:
			if(eKeyboardRead() == BUTTON_1) {
					eLedState = WAITING;
			} else {
				eLedState = RIGHT;
			}
			LedStepRight();
			break;
	}
}// gittest

int main (){
	unsigned int iMainLoopCtr;
	Timer0Interrupts_Init(250000, &Automat);
	KeyboardInit();
	LedInit();

	while(1){
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
