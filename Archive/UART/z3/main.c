#include "uart.h"
#include "keyboard.h"
#include "servo.h"

int main() {
	extern char cOdebranyZnak;
	enum KeyboardState eKeyboardState;
	KeyboardInit();
	ServoInit(8);
	UART_InitWithInt(9600);
	while (1) {
		switch(cOdebranyZnak) {
			case '1':
				ServoGoTo(12);
				break;
			case '2':
				ServoGoTo(24);
				break;
			case '3':
				ServoGoTo(36);
				break;
			case '4':
				break;
			case 'c':
				ServoCallib();
				break;
		}
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
