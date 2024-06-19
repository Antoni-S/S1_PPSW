#include "string.h"
#include "konwersje.h"
#include "dekodowanie.h"
#define NULL '\0'

typedef struct Keyword {
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
	{CL, "callib"},
	{GT, "goto"},
	{SH, "shift"}
};

unsigned char ucTokenNr;
struct Token asToken[MAX_TOKEN_NR];

enum State {TOKEN, DELIMITER};

//Funkcje

unsigned char ucFindTokensInString (char *pcString) {
	
	unsigned char ucCharCounter;
	unsigned char ucCurrentChar;
	enum State eState = DELIMITER;
	ucTokenNr = 0;
	
	for(ucCharCounter = 0;;ucCharCounter++) {
		
		ucCurrentChar = pcString[ucCharCounter];
		switch(eState) {
			case DELIMITER:
				if(ucCurrentChar == NULL) {
					return ucTokenNr;
				} else if(ucCurrentChar != ' ') {
					eState = TOKEN;
					asToken[ucTokenNr].uValue.pcString = pcString + ucCharCounter;
					ucTokenNr++;
				} else {
					eState = DELIMITER;
				}
				break;
			case TOKEN:
				if(ucTokenNr == MAX_TOKEN_NR) {
					return ucTokenNr;
				}	else if(ucCurrentChar == NULL) {
					return ucTokenNr;
				} else if(ucCurrentChar == ' ') {
					eState = DELIMITER;
				} else {
					eState = TOKEN;
				}
				break;
		}
	}
}

enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode) {
	
	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter = 0;ucKeywordCounter < MAX_KEYWORD_NR;ucKeywordCounter++) {
		if(eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString) == EQUAL) {
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void) {
	
	unsigned char ucTokenCounter;
	//unsigned int uiTokenValue;
	//enum KeywordCode eTokenCode;
	
	for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++) {

		if(eStringToKeyword(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.eKeyword) == OK) {
			asToken[ucTokenCounter].eType = KEYWORD;
			//asToken[ucTokenCounter].uValue.eKeyword = eTokenCode;
		} else if(eHexStringToUInt(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.uiNumber) == OK) {
			asToken[ucTokenCounter].eType = NUMBER;
			//asToken[ucTokenCounter].uValue.uiNumber = uiTokenValue;
		} else {
			asToken[ucTokenCounter].eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString) {
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
}
