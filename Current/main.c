#include "uart.h"
#include "led.h"
#include "keyboard.h"
#include "servo.h"
#include "string.h"
#include "dekodowanie.h"

int main() {
	extern char cOdebranyZnak;
	extern struct Token asToken[MAX_TOKEN_NR];
	extern unsigned char ucTokenNr;
	char cDestination[RECEIVER_SIZE];
	ServoInit(8);
	LedInit();
	UART_InitWithInt(9600);
	while(1) {
		if(eReceiver_GetStatus() == READY) {
			Receiver_GetStringCopy(cDestination);
			DecodeMsg(cDestination);
			if(ucTokenNr != 0 && asToken[0].eType == KEYWORD) {				
				switch(asToken[0].uValue.eKeyword) {
					case CALLIB:
						ServoCallib();
						break;
					case GOTO:
						ServoGoTo(asToken[1].uValue.uiNumber);
						break;
					case SHIFT:
						ServoShift(asToken[1].uValue.uiNumber);
						break;
				}
			}
		}
	}
}
