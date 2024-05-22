#include "led.h"
#include "keyboard.h"

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

int main() {
	enum LedState{WAITING, RUNNING};

	enum LedState eLedState = WAITING;
	unsigned char ucStepCounter = 0;

	LedInit();
	KeyboardInit();

	while(1) {
		switch(eLedState) {
			case RUNNING:
				LedStepRight();
				ucStepCounter = ucStepCounter + 1;
				if(ucStepCounter == 2) {
					eLedState = WAITING;
					ucStepCounter = 0;
				} else {
					eLedState = RUNNING;
				}
				break;
			case WAITING:
				if(eKeyboardRead() == BUTTON_0) {
					eLedState = RUNNING;
				} else {
					eLedState = WAITING;
				}
				break;
		}
		Delay(250);
	}
}
