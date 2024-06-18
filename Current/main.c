#include "uart.h"
#include "keyboard.h"
#include "servo.h"
#include "string.h"
#include "led.h"

int main() {
	extern char cOdebranyZnak;
	char cDestination[RECIEVER_SIZE];
	ServoInit(8);
	LedInit();
	UART_InitWithInt(9600);
	while(1) {
		if(eReciever_GetStatus() == READY) {
			Reciever_GetStringCopy(cDestination);
			if(eCompareString(cDestination, "callib") == EQUAL) {
				ServoCallib();
			} else if(eCompareString(cDestination, "left") == EQUAL) {
				ServoGoTo(12);
			} else if(eCompareString(cDestination, "right") == EQUAL) {
				ServoGoTo(36);
			}
		}
	}
}
