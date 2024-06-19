enum Result {OK, ERROR};

void UIntToHexStr(unsigned int uiValue, char pcStr[]);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);
