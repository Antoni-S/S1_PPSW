#include "konwersje.h"
#define NULL '\0'

void UIntToHexStr (unsigned int uiValue, char pcStr[]){
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;
	
	pcStr[0] ='0';
	pcStr[1] ='x';
	pcStr[6] = NULL;
	
	for(ucNibbleCounter=0; ucNibbleCounter<4; ucNibbleCounter++) {
		ucCurrentNibble=(uiValue >> (ucNibbleCounter*4))&0xF;
		if(ucCurrentNibble<10){
			pcStr[5-ucNibbleCounter] = '0'+ucCurrentNibble;
		}
		else{
			pcStr[5-ucNibbleCounter] = 'A'+(ucCurrentNibble-10);
		}
	}
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]) {
	
	unsigned char ucCharCounter;
	
	for(ucCharCounter = 0; pcDestinationStr[ucCharCounter] != NULL; ucCharCounter++) {}
	UIntToHexStr(uiValue, pcDestinationStr + ucCharCounter);
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue) {
	
	unsigned char ucCharCounter;
	unsigned char ucCurrentChar;
	
	*puiValue = 0;
	
	if(pcStr[0] != '0' || pcStr[1] != 'x' || pcStr[2] == NULL) {
		return ERROR;
	}
	for(ucCharCounter = 2; ucCharCounter <= 6; ucCharCounter++) {
		ucCurrentChar = pcStr[ucCharCounter];
		
		if(ucCurrentChar == NULL) {
			return OK;
		} else if(ucCharCounter == 6) {
			return ERROR;
		}
		
		*puiValue = *puiValue << 4;
		
		if((ucCurrentChar <= '9') && (ucCurrentChar >= '0')) {
			ucCurrentChar = ucCurrentChar - '0';
		} else if(ucCurrentChar <= 'F' && ucCurrentChar >= 'A') {
			ucCurrentChar = ucCurrentChar - 'A' + 10;
		} else {
			return ERROR;
		}
		*puiValue = *puiValue | ucCurrentChar;
	}
	return OK;
}
