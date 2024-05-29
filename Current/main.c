#include "uart.h"
#include "keyboard.h"
#include "servo.h"

int main() {
	extern char cOdebranyZnak;
	unsigned int uiPosition = 12;
	enum KeyboardState eKeyboardState;
	KeyboardInit();
	ServoInit(8);
	UART_InitWithInt(9600);
	while (1) {
		switch(cOdebranyZnak) {
			case '1':
				ServoGoTo(uiPosition);
				uiPosition += 12;
				break;
			case 'c':
				ServoCallib();
				uiPosition = 12;
				break;
			default:
				break;
		}
		cOdebranyZnak = 0;
		eKeyboardState = eKeyboardRead();
		switch(eKeyboardState) {
				case BUTTON_0:
					ServoCallib();
					break;
				case BUTTON_1:
					ServoGoTo(12);
					break;
				case BUTTON_2:
					ServoGoTo(24);
					break;
				case BUTTON_3:
					ServoGoTo(36);
					break;
				default:
					break;
		}
	}
}
