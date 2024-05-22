#include "led.h"
#include "keyboard.h"

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

int main() {
	enum LedState{LED_LEFT, LED_RIGHT};

	enum LedState eLedState = LED_LEFT;
	unsigned char ucStepCounter = 0;

	LedInit();
	KeyboardInit();

	while(1) {
		switch(eLedState) {
			case LED_LEFT:
				LedStepLeft();
				ucStepCounter = ucStepCounter + 1;
				if(ucStepCounter == 2) {
					eLedState = LED_RIGHT;
				} else {
					eLedState = LED_LEFT;
				}
				break;
			case LED_RIGHT:
				LedStepRight();
				ucStepCounter = ucStepCounter - 1;
				if(ucStepCounter == 0) {
					eLedState = LED_LEFT;
				} else {
					eLedState = LED_RIGHT;
				}
				break;
		}
		Delay(250);
	}
}
