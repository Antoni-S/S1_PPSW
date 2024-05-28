#include "uart.h"
#include "timer.h"

int main() {
	extern char cOdebranyZnak;
	UART_InitWithInt(9600);
	InitTimer0Match0(250000);
	while (1) {
	}
}
