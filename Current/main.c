#include "uart.h"
#include "string.h"
#include "konwersje.h"
#include "timer_interrupts.h"
#include "command_decoder.h"

extern unsigned char ucTokenNr;
extern struct Token asToken[MAX_TOKEN_NR];

struct Watch {
	unsigned char ucMinutes;
	unsigned char ucSeconds;
	unsigned char fSecondsValueChanged;
	unsigned char fMinutesValueChanged;
};

struct Watch sWatch;

void WatchUpdate(void) {
	sWatch.ucSeconds++;
	sWatch.fSecondsValueChanged = 1;
	
	if(sWatch.ucSeconds == 60) {
		sWatch.ucSeconds = 0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged = 1;
		
		if(sWatch.ucMinutes == 60) {
			sWatch.ucMinutes = 0;
		}
	}
};

int main() {
	char cTextTX[TRANSMITER_SIZE];
	char cTextRX[RECEIVER_SIZE];
	unsigned int uiMult;
	unsigned char ucIsCalc = 0;
	
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, WatchUpdate);

	while(1) {
		if(eReceiver_GetStatus() == READY) {
			Receiver_GetStringCopy(cTextRX);
			DecodeMsg(cTextRX);
			
			if(ucTokenNr == 2 && asToken[0].eType == KEYWORD && asToken[1].eType == NUMBER) {
				if(asToken[0].uValue.eKeyword == CALC) {
					uiMult = 2 * asToken[1].uValue.uiNumber;
					ucIsCalc = 1;
				}
			}
		};
		
		if(Transmiter_GetStatus() == FREE) {
			if(ucIsCalc) {
				CopyString("calc ", cTextTX);
				UIntToHexStr(uiMult, cTextTX + 5);
				Transmiter_SendString(cTextTX);
				ucIsCalc = 0;
			} else if(sWatch.fMinutesValueChanged) {
				CopyString("min ", cTextTX);
				UIntToHexStr(sWatch.ucMinutes, cTextTX + 4);
				Transmiter_SendString(cTextTX);
				sWatch.fMinutesValueChanged = 0;
			} else if(sWatch.fSecondsValueChanged) {
				CopyString("sec ", cTextTX);
				UIntToHexStr(sWatch.ucSeconds, cTextTX + 4);
				Transmiter_SendString(cTextTX);
				sWatch.fSecondsValueChanged = 0;
			}
		}
	}
}
