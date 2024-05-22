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

	LedInit();
	KeyboardInit();

	while(1) {
		switch(eLedState) {
			case LED_LEFT:
				LedStepLeft();
				eLedState = LED_RIGHT;
				break;
			case LED_RIGHT:
				LedStepRight();
				eLedState = LED_LEFT;
				break;
		}
		Delay(250);
	}
}
