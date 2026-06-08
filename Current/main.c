#include "uart.h"
#include "string.h"
#include "konwersje.h"

int main() {
	unsigned int uiCounter;
	char cText[TRANSMITER_SIZE];

	UART_InitWithInt(9600);

	while(1) {
		if(Transmiter_GetStatus() == FREE) {
			CopyString("licznik 0x", cText);
			UIntToHexStr(uiCounter, cText + 10);
			Transmiter_SendString(cText);
			uiCounter++;
		}
	}
}
