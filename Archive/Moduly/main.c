#include "led.h"
#include "keyboard.h"

//Funkcje
void Delay(int iDelayTime) {
	int iLoopCount = 12000;
	for(iLoopCount *= iDelayTime; iLoopCount > 0; iLoopCount--) {}
}

int main() {
	LedInit();
	KeyboardInit();

	while(1) {
		enum KeyboardState eKeyPressed = eKeyboardRead();
		switch(eKeyPressed) {
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
		Delay(50);
	}
}
