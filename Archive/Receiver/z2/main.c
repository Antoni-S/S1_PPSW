#include "uart.h"
#include "keyboard.h"
#include "servo.h"
#include "string.h"
#include "led.h"

int main() {
	extern char cOdebranyZnak;
	char cDestination[RECEIVER_SIZE];
	ServoInit(8);
	LedInit();
	UART_InitWithInt(9600);
	while(1) {
		if(eReceiver_GetStatus() == READY) {
			Receiver_GetStringCopy(cDestination);
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
