#include "string.h"

//enum CompResult { DIFFERENT , EQUAL };

void CopyString(char pcSource[], char pcDestination[])
{
	
	unsigned char ucCtrOfChars=0;
	
	for (ucCtrOfChars=0; '\0' != pcSource[ucCtrOfChars]; ucCtrOfChars++)
	{
		pcDestination[ucCtrOfChars] = pcSource[ucCtrOfChars];
	}
	
	pcDestination[ucCtrOfChars] = '\0';
	
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){

    unsigned char ucLetterCounter;

    for(ucLetterCounter = 0 ; pcStr1[ucLetterCounter] != '\0' ; ucLetterCounter++ ){
            if(pcStr1[ucLetterCounter] != pcStr2[ucLetterCounter]){
                return DIFFERENT;
            }
        }
        if(pcStr1[ucLetterCounter] != pcStr2[ucLetterCounter]){
            return DIFFERENT;
        }
        else{
            return EQUAL;
        }
    }
	
void AppendString(char pcSourceStr[],char pcDestinationStr[])
{
    unsigned char ucCharCtr=0;

    for (ucCharCtr=0; '\0' != pcDestinationStr[ucCharCtr]; ucCharCtr++);

    CopyString(pcSourceStr, &pcDestinationStr[ucCharCtr]);
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar)
{
    unsigned char ucCharCtr;

    for (ucCharCtr=0; '\0' != pcString[ucCharCtr]; ucCharCtr++)
    {
        if (pcString[ucCharCtr] == cOldChar)
        {
            pcString[ucCharCtr] = cNewChar;
        }
    }
}
