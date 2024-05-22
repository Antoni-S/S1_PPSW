#include "led.h"
#include "keyboard.h"

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

int main() {
	enum LedState{WAITING, LEFT, RIGHT};

	enum LedState eLedState = WAITING;

	LedInit();
	KeyboardInit();

	while(1) {
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
		Delay(100);
	}
}
