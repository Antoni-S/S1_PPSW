#include "led.h"
#include "keyboard.h"

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

int main() {
	enum LedState{WAITING, RUNNING};

	enum LedState eLedState = RUNNING;

	LedInit();
	KeyboardInit();

	while(1) {
		switch(eLedState) {
			case RUNNING:
				if(eKeyboardRead() == BUTTON_0) {
					eLedState = WAITING;
				} else {
					eLedState = RUNNING;
				}
				LedStepRight();
				break;
			case WAITING:
				if(eKeyboardRead() == BUTTON_1) {
					eLedState = RUNNING;
				} else {
					eLedState = WAITING;
				}
				break;
		}
		Delay(250);
	}
}
