#include "HiddenFunctions.h"


//////////////////////////////////////////////////////////////////////////
//functions

//#pragma code_seg(SECTION_NAME_HIDDEN_INSTRUCTIONS)
//NTSTATUS HiddenFunctionA(PHIDDEN_PAGE_RECORD pHiddenPageRecord)
//{
//	NTSTATUS Status = STATUS_UNSUCCESSFUL;
//
//	Status = ApiTransfer_SimulateApi(pHiddenPageRecord, 0xFAFAFAFAFAFAFAFA);
//
//	return Status;
//}
//#pragma code_seg()

#pragma code_seg(SECTION_NAME_HIDDEN_INSTRUCTIONS)
BOOL HiddenFunction(PCHAR checkStr)
{
	if (!checkStr)
	{
		return FALSE;
	}
	CHAR validStr[64] = "strongPassword";
	return strcmp(validStr, checkStr) == 0;//we are going to modify the equal operator
}
#pragma code_seg()
BOOL UnsafeFunction(PCHAR checkStr)
{
	if (!checkStr)
	{
		return FALSE;
	}
	CHAR validStr[64] = "strongPassword";
	return strcmp(validStr, checkStr) == 0;
}

#pragma data_seg(SECTION_NAME_HIDDEN_DATA)  
char HiddenData[4096] = "normal data";//we are going to hack the data
#pragma data_seg() 

char UnsafeData[4096] = "normal data";

