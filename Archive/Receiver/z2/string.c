#include "string.h"
#define NULL '\0'


void CopyString (char pcSource[], char pcDestination[]) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcSource[ucCharLocation] != NULL; ucCharLocation++) {
		pcDestination[ucCharLocation] = pcSource[ucCharLocation];
	}
	pcDestination[ucCharLocation] = NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcStr1[ucCharLocation] != NULL; ucCharLocation++) {
		if(pcStr1[ucCharLocation] != pcStr2[ucCharLocation]) {
			return DIFFERENT;
		}
	}
	if(pcStr1[ucCharLocation] == pcStr2[ucCharLocation]) {
		return EQUAL;
	} else {
		return DIFFERENT;
	}
}

void AppendString(char pcSourceStr[], char pcDestinationStr[]) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcDestinationStr[ucCharLocation] != NULL; ucCharLocation++) {}
	CopyString(pcSourceStr, pcDestinationStr + ucCharLocation);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {
	
	unsigned char ucCharLocation;
	
	for(ucCharLocation = 0; pcString[ucCharLocation] != NULL; ucCharLocation++) {
		if(pcString[ucCharLocation] == cOldChar) {
			pcString[ucCharLocation] = cNewChar;
		}
	}
}
